#include "http_messages.hh"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <link.h>
#include <errno.h>
#include <cstring>
#include <string>
#include <iostream>
#include <stdio.h>
#include<stdlib.h>

typedef void (*httprunfunc)(int ssock, const char* querystring);

std::string handle_cgi_bin(const HttpRequest& request) {
  int tmpin = dup(0);
  int tmpout = dup(1);
  
  int fdin;
  int fdout;
  
  int fdpipe[2];
  pipe(fdpipe);
  fdout=fdpipe[1];
  fdin=fdpipe[0];
  

  std::string script = "./http-root-dir" + request.request_uri;
  const char *s = script.c_str();
  std::cout << "script is " << s << '\n';
  
  int ret = fork();
  if (ret == 0) {
    dup2(fdout,1);
    setenv("REQUEST_METHOD", "GET", 1);
    const char * querystring = request.query.c_str();
    setenv("QUERY_STRING", querystring, 1);
    std::cout << "query is " << querystring << '\n';
    if (request.request_uri.find(".so") != std::string::npos) {
      void * lib = dlopen(s, RTLD_LAZY);
      if (lib == NULL) {
        fprintf(stderr, ".so file not found\n");
        perror("dlopen");
        exit(1);
      }
      httprunfunc httprun = (httprunfunc) dlsym(lib, "_Z7httpruniPc");
      if (httprun == NULL ) {
        perror("dlsym: httprun not found:");
        exit(1);
      }
      httprun(fdout, querystring);
      if (dlclose(lib) != 0) {
	      perror("dlclose");
	      exit(3);
	    }
      close(fdout);
      close(fdin);
    }
    else {    
      close(fdout);
      close(fdin);
      execvp(s, NULL);
      perror("execvp");
      _exit(1);
    }
  }
  else if (ret < 0) {
    perror("fork");
    exit(1);
  }
  waitpid(ret, 0, NULL);

  dup2(tmpin, 0);
  dup2(tmpout, 1);
  close(fdout);
  close(tmpin);
  close(tmpout);
  
  std::string buf = "";
  char ch;
  while (read(fdin, &ch, 1)) {
    buf += ch;
  }
  std::cout << "buf is " << buf << '\n';
  close(fdin);
  return buf;
}
