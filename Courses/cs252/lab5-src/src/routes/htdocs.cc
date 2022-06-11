#include "http_messages.hh"
#include "misc.hh"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

// You may find implementing this function and using it in server.cc helpful

HttpResponse handle_htdocs(const HttpRequest& request, bool cgi) {
  HttpResponse resp;
  
  // TODO: Task 1.3
  // Get the request URI, verify the file exists and serve it
  
  resp.http_version = request.http_version;
  std::string path = "./http-root-dir/htdocs";
  if (cgi) {
    path = "./http-root-dir/";
  }
  path += request.request_uri;
  if (request.request_uri == "/") {
    path += "index.html";
  }
  if (request.request_uri == "/logs") {
    path = "./myhttpd.log";
  }
  std::cout << "path is " << path << '\n';
  std::cout << "type is " << get_content_type(path) << '\n';
  std::ifstream ifstream(path.c_str());
  
  if (ifstream) {
    std::cout << "file exists" << '\n';
    resp.status_code = 200;
    resp.reason_phrase = "Authorized";
    
    std::string str = "";
    std::string message = "";
    
    while (getline(ifstream, str)) {
      message += str;
      message += "\n";
    }
    message += "\r\n";
    
    ifstream.close();
    
    resp.headers["Connection"] = "close";
    resp.headers["Content-Length"] = std::to_string(message.size());
    resp.headers["Content-Type"] = get_content_type(path);
    resp.message_body = message;
  }
  else {
    resp.status_code = 404;
    resp.reason_phrase = "Error Not Found";
  }
  

  return resp;
}
