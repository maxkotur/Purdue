/**
 * This file contains the primary logic for your server. It is responsible for
 * handling socket communication - parsing HTTP requests and sending HTTP responses
 * to the client. 
 */

#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <pthread.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/wait.h>
#include <ratio>
#include <chrono>
#include <ctime>
#include <climits>
#include <fstream>

#include "server.hh"
#include "http_messages.hh"
#include "errors.hh"
#include "misc.hh"
#include "routes.hh"

Server::Server(SocketAcceptor const& acceptor) : _acceptor(acceptor) { 
  auto stat = stats{};
  stat.min_time = INT_MAX;
  stat.max_time = 0;
  stat.start_time = time(NULL);
  stat.min_time_URL = "";
  stat.max_time_URL = "";
  stat.num_requests = 0;
}
pthread_mutex_t m1;
std::string login = "TWF4aW1lOktvdHVy=";

void Server::run_linear() const {
  while (1) {
    Socket_t sock = _acceptor.accept_connection();
    handle(sock);
  }
}

void Server::run_fork() const {
  while (1) {
    Socket_t sock = _acceptor.accept_connection();
    int ret = fork();
    if (ret == 0) {
      handle(sock);
      exit(0);
    }
    waitpid(-1, NULL, WNOHANG);
  } 
}

struct ThreadParams {
  const Server * server;
  Socket_t sock;
};  

void dispatchThread( ThreadParams * params) {
  printf("Dispatch Thread\n");
  // Thread dispatching this request
  params->server->handle(params->sock);
  // Delete params struct
  delete params;
}

void Server::run_thread() const {
  while (1) {
    // Accept request
    Socket_t sock = _acceptor.accept_connection();
    // Put socket in new ThreadParams struct
    ThreadParams * threadParams = new ThreadParams;
    threadParams->server = this;
    threadParams->sock = std::move(sock);
    // Create thread
    std::thread t(dispatchThread, threadParams);
    t.detach();
  }
}

void * Server::loop_thread() const {
  while (1) {
    pthread_mutex_lock(&m1);
    Socket_t sock = _acceptor.accept_connection();
    pthread_mutex_unlock(&m1);
    handle(sock);
  }
}

void Server::run_thread_pool(const int num_threads) const {
  pthread_t threads[num_threads];
  
  for (int i = 0; i < num_threads; i++) {
    pthread_create(&threads[i], NULL, (void * (*)(void *)) loop_thread(),(void *)&_acceptor);
  }
  
  loop_thread();
}

// example route map. you could loop through these routes and find the first route which
// matches the prefix and call the corresponding handler. You are free to implement
// the different routes however you please
/*
std::vector<Route_t> route_map = {
  std::make_pair("/cgi-bin", handle_cgi_bin),
  std::make_pair("/", handle_htdocs),
  std::make_pair("", handle_default)
};
*/

int Server::get_min() const {
  return statistics.min_time;
}

int Server::get_max() const {
  return statistics.max_time;
}

time_t Server::get_start() const {
  return statistics.start_time;
}

std::string Server::get_min_URL() const {
  return statistics.min_time_URL;
}

std::string Server::get_max_URL() const {
  return statistics.max_time_URL;
}

int Server::get_num_request() const {
  return statistics.num_requests;
}

void Server::set_min(int min) {
  statistics.min_time = min;
}

void Server::set_max(int max) {
  statistics.max_time = max;
}

void Server::set_min_URL(std::string url) {
  statistics.min_time_URL = url;
}

void Server::set_max_URL(std::string url) {
  statistics.max_time_URL = url;
}

void Server::set_num_requests() {
  statistics.num_requests++;
}

void update_stats(int duration, HttpRequest request) {
  SocketAcceptor* acceptor;
  Server server(*acceptor);
  if (duration < server.get_min()) {
    server.set_min(duration);
    server.set_min_URL(request.request_uri);
  }
  if (duration > server.get_max()) {
    server.set_max(duration);
    server.set_max_URL(request.request_uri);
  }
  server.set_num_requests();
}

void update_logs(HttpResponse resp, HttpRequest request) {
  std::ofstream file ("myhttpd.log", std::ios_base::app | std::ios_base::out);
  if (file.is_open()) {
    file << IP << " \n";
    file << request.request_uri << "\n";
    file << resp.http_version << " " << std::to_string(resp.status_code) <<
     " " << resp.reason_phrase  << "\n";
    file.close();
  }
  else {
    std::cout << "Unable to open file";
  } 
}

std::string handle_stats(HttpRequest request){
  std::string resp = "Maxime Kotur\n";
  SocketAcceptor* acceptor;
  Server server(*acceptor);
  int seconds = difftime(server.get_start(),time(NULL));
  resp += "Server has been running for: ";
  resp += std::to_string(seconds);
  resp += "\n";
  resp += std::to_string(server.get_num_request());
  resp += "\n";
  resp += std::to_string(server.get_max());
  resp += "\n";
  resp += server.get_max_URL();
  resp += "\n";
  resp += std::to_string(server.get_min());
  resp += "\n";
  resp += server.get_min_URL();
  resp += "\n";
}

void parse_request(const Socket_t& sock, HttpRequest* const request) {
  std::string s;
  s = sock->readline();
  std::cout << s << '\n';
  std::vector<std::string> words;
  std::string word = "";
  for (int i = 0; i < s.size() - 2; i++) {
    if (s[i] == ' ') {
      words.push_back(word);
      word = "";
      continue;
    }
    word += s[i];
    if (i == s.size() - 3) {
      words.push_back(word);
    }
  }
  if (words[1].find("/cgi") != std::string::npos) {
    std::cout << "cgi detected" << '\n';
    std::string method = words[0];
    std::string http_version = words[2];
    int qu = words[1].find('?');
    if (qu == std::string::npos) {
      std::string request_uri = words[1];
      request->request_uri = request_uri;
      request->query = "";
    }
    else {
      std::string request_uri = words[1].substr(0, qu);
      std::string query = words[1].substr(qu + 1, words[1].size() - qu);
      request->request_uri = request_uri;
      request->query = query;
    }
    request->method = method;
    request->http_version = http_version;
    request->message_body = "";
    return;
  }
  std::cout << "word is " << words[1] << '\n';
  std::string method = words[0];
  std::string request_uri = words[1];
  std::string http_version = words[2];
  request->method = method;
  request->request_uri = request_uri;
  request->http_version = http_version;
  request->query = "";
  
  
  request->message_body = "";
  
  
}

void Server::handle(const Socket_t& sock) const {
  HttpRequest request;
  auto start = std::chrono::high_resolution_clock::now();
  // TODO: implement parsing HTTP requests
  // recommendation:
  parse_request(sock, &request);
  std::cout << "parsing done" << '\n';
  
  // TODO: Make a response for the HTTP request
  HttpResponse resp;
  bool auth = false;
  bool cgi = false;
  bool stat = false;
  std::string buffercgi;
  std::string stats;
  if (request.request_uri.find("/cgi") != std::string::npos) {
    buffercgi = handle_cgi_bin(request);
    buffercgi.erase(0, buffercgi.find("\n") + 1);
    cgi = true;
  }
  else if (request.request_uri == "/stats") {
    stats = handle_stats(request);
    stat = true;
  }
  while (true) {
    
    std::string s;
    s = sock->readline();
    std::cout << "message has been read" << '\n';
    std::cout << "s is: " << s << '\n';
    if (s == "\r\n") {
      break;
    }
    
    std::string head = "";
    std::string value = "";
    for (int i = 0; i < s.size() - 2; i++) {
      if (s[i] == ':') {
        head = s.substr(0, i);
        value = s.substr(i+2, s.size()-2);
        break;
      }
    }
    
    if (head == "Authorization:") {
      
      if (value.find(login)) {
        auth = true;
      }
      else {
        std::cout << "wrong username:password" << '\n';
      }
    }
    std::cout << "head is " << head << '\n';
    std::cout << "value is " << value << '\n';
    request.headers[head] = value;
  }
  
  request.print();
  
  if (auth) {
    resp.http_version = request.http_version;
    resp.status_code = 401;
    resp.reason_phrase = "Unauthorized";
    resp.headers["WWW-Authenticate"] = "Basic realm=\"CS252_LAB_5\"";
  }
  else {
    resp = handle_htdocs(request, cgi);
  }
  std::cout << "Start of HTTP response:" << std::endl;
  if (cgi) {
    std::cout << "buffer is " << buffercgi << '\n';
    sock->write(resp.http_version);
    sock->write(std::to_string(resp.status_code));
    sock->write(resp.reason_phrase);
    sock->write(buffercgi);

  }
  else if (stat) {
    sock->write(resp.http_version);
    sock->write(std::to_string(resp.status_code));
    sock->write(resp.reason_phrase);
    sock->write(stats);
  }
  else {
    std::cout << "{" << resp.to_string() << "}" << std::endl;
    sock->write(resp.to_string());
  }
  
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
  int dur = duration.count();
  update_stats(dur, request);
  update_logs(resp, request);

}
