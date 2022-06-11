/**
 * This file contains the primary logic for your server. It is responsible for
 * handling socket communication - parsing HTTP requests and sending HTTP responses
 * to the client. 
 */

#include <map>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <thread>
#include <pthread.h>

#include "server.hh"
#include "http_messages.hh"
#include "errors.hh"
#include "misc.hh"
#include "routes.hh"

Server::Server(SocketAcceptor const& acceptor) : _acceptor(acceptor) { }
std::string userPass = "Basic cHJhdHM6cm9ja3M=";

pthread_mutex_t myMutex;

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

void Server::run_linear() const {
  while (1) {
    Socket_t sock = _acceptor.accept_connection();
    handle(sock);
  }
}

void Server::run_fork() const {
  // TODO: Task 1.4

  while (1) {

    // pthread_mutex_lock(&myMutex);
    Socket_t sock = _acceptor.accept_connection();
    // pthread_mutex_unlock(&myMutex);

    int ret = fork();

    if (ret == 0) {

      handle(sock);
      exit(0);

    }

  }

}

void Server::run_thread() const {
  // TODO: Task 1.4

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

void* Server::loopthread () const {

  while (1) {

    pthread_mutex_lock(&myMutex);
    Socket_t sock = _acceptor.accept_connection();
    pthread_mutex_unlock(&myMutex);

    handle(sock);

  }

}

void Server::run_thread_pool(const int num_threads) const {
  // TODO: Task 1.4

  // std::cout << num_threads << std ::endl;

  pthread_t myThreads[num_threads];

  for (int i = 0; i < num_threads; i++) {

    pthread_create(&myThreads[i], NULL, (void * (*)(void *))loopthread(), (void *)&_acceptor);

  }

  loopthread();

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

void Server::handle(const Socket_t& sock) const {

  using namespace boost::algorithm;

  int hasAuthHeader = 0;

  HttpRequest request;
  // TODO: implement parsing HTTP requests
  // recommendation:
  // void parse_request(const Socket_t& sock, HttpRequest* const request);

  std::string myLine = sock->readline();
  std::vector<std::string> words;

  // Splitting string into arry of words
  split(words, myLine, is_any_of(" "));

  if (words.size() != 3) {

    return;

  }

  // std::cout << myLine << std::endl;

  request.method = words.at(0);
  request.request_uri = words.at(1);
  request.http_version = words.at(2).substr(0, words.at(2).size() - 2);

  while (true) {

    std::string newLine = sock->readline();

    if (newLine.compare("\r\n") == 0) {

      break;

    }

    // std::vector<std::string> new_words;

    // // Splitting string into arry of words
    // split(new_words, newLine, is_any_of(" "));
    // std::string field = new_words.at(0).substr(0, new_words.at(0).size() - 1);
    // std::string val = new_words.at(1);

    int loc = newLine.find(" ");
    std::string field = newLine.substr(0, loc - 1);
    std::string val = newLine.substr(loc + 1);

    if (val.at(val.size() - 1) == '\n' && val.at(val.size() - 2) == '\r') {

      val = val.substr(0, val.size() - 2);

    }

    if (field.compare("Authorization") == 0) {

      // std::cout << val.size() << std::endl;

      if (userPass.compare(val) == 0) {

        hasAuthHeader = 1;

      }

    }

    request.headers.insert(std::make_pair(field, val));

  }

  request.print();

  // TODO: Make a response for the HTTP requests

  // Basic HTTP Authentication 
  if (hasAuthHeader == 0) {

    HttpResponse resp;
    resp.http_version = request.http_version;
    resp.status_code = 401;
    resp.headers["WWW-Authenticate"] = "Basic realm=\"The_Great_Realm_of_CS252\"";
    std::string myResponse = resp.to_string();
    std::cout << myResponse << std::endl;
    sock->write(myResponse);

  } else {

    HttpResponse resp = handle_htdocs(request);
    std::string myResponse = resp.to_string();
    std::cout << myResponse << std::endl;
    sock->write(myResponse);

  }

  // std::string *fileName = request.request_uri;
  // resp.type = get_content_type(request.request_uri);
  
}