
/*
 *
 * CS-252 
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 * NOTICE: This lab is property of Purdue University. You should not for any reason make this code public.
 */

%{

#include <cstring>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include "y.tab.hh"
#include "string.h"
#include "shell.hh"

extern "C" char * read_line();


int mygetc(FILE * f) {
 static char *p;
 char ch;

 if (!isatty(0)) {
 // stdin is not a tty. Call real getc
   return getc(f);
 }

 // stdin is a tty. Call our read_line.
 if (p==NULL || *p == 0) {
   char * s = read_line();
   p = s;
 }

 ch = *p;
 p++;

 return ch;
}

#undef getc
#define getc(f) mygetc(f)

static  void yyunput (int c,char *buf_ptr  );

void myunputc(int c) {
  unput(c);
}

%}

%option noyywrap

%%

\n {
  return NEWLINE;
}

[ \t] {
  /* Discard spaces and tabs */
}

">" {
  return GREAT;
}

">>" {
  return GREATGREAT;
}

[^ \\\t\n]*[\\][^ \t\n]+ {
  /* Escape Character */
  std::string temp = std::string(yytext);
  std::string escape;
  for (int i = 0; i < strlen(yytext) - 1; i++) {
    if (temp[i] == '\\') {
      if (temp[i+1] == '\\') {
        i+=2;
        escape+= '\\';
        continue;
      }
      else {
        escape+= temp[i+1];
        i++;
        continue;
      }
    }
    else {
      escape+= temp[i];
    }
  }
  yylval.cpp_string = new std::string(escape);
  return WORD;
}

["][^\n\"]*["] {
  /* Quotes Character */
  yylval.cpp_string = new std::string(yytext, 1, strlen(yytext) - 2);
  return WORD;
}

[^ \t\n\>\|]*(\$\{.*?\})[^ \t\n\>\|]* {
  yylval.cpp_string = new std::string(yytext);
  std::string temp;
  std::string final;
  for (int i = 0; i < strlen(yytext); i++) {
    if (yytext[i] == '$' && i != strlen(yytext) - 1 && yytext[i+1] == '{') {
      i+=2;
      while (yytext[i] != '}') {
        temp += yytext[i++];
      }
      if (temp == "$") {
        int pid = getpid();
        char mypid[6];
        sprintf(mypid, "%d", pid);
        final += mypid;
      }
      else if (temp == "?") {
        char *e = getenv("QU");
        final += e;
      }
      else if (temp == "!") {
        final += std::to_string(Shell::_currentCommand.exlcam_pid);
      }
      else if (temp == "_") {
        char *e = getenv("lastarg");
        final += e;
      }
      else if (temp == "SHELL") {
        char e[5000];
        realpath("../shell", e);
        final += e;
      }
      else {
        char cstr[temp.size() + 1];
        strcpy(cstr, temp.c_str());
        const char *env = cstr;
        char * e = getenv(env);
        final += e;
      }
      temp = "";
    }
    else {
      final += yytext[i];
    }
  }
  yylval.cpp_string = new std::string(final);
  return WORD;
}

\$\(.*?\) {
  /* Subshell */
  
  std::string * command = new std::string(yytext, 2, strlen(yytext) - 3);
  int tmpin = dup(0);
  int tmpout = dup(1);
  
  int pin[2];
  int pout[2];
  pipe(pin);
  pipe(pout);
  
  
  dup2(pin[0],0);
  close(pin[0]);
  dup2(pout[1],1);
  close(pout[1]);
  
  write(pin[1], command->c_str(), command->size());
  write(pin[1], "\nexit\n", 6);
  close(pin[1]);
  
  int ret = fork();
  
  if (ret == 0) {
    execvp("/proc/self/exe", NULL);
    _exit(1);
  }
  else if (ret < 0) {
    perror("fork");
    exit(1);
  }
  waitpid(ret, 0, NULL);
  dup2(tmpin, 0);
  dup2(tmpout, 1);
  close(tmpin);
  close(tmpout);
  std::string buf = "";
  char ch;
  while (read(pout[0], &ch, 1)) {
    if (ch == '\n') {
      buf += ' ';
    }
    else {
      buf += ch;
    }
  }
  close(pout[0]);
  
  std::reverse(buf.begin(), buf.end());
  myunputc('\n');
  for (unsigned i = 0; i < buf.size(); i++) {
    myunputc(buf[i]);
  }
  
} 

"2>" {
  return TWOGREAT;
}

"<" {
  return LESS;
}

"&" {
	return AND;
}

">&" {
	return GREATAND;
}

">>&" {
	return GREATGREATAND;
}

"|" {
	return PIPE;
}

[^ \t\n\&\<\>|][^ \t\n\&\<\>|]*  {
  /* Assume that file names have only alpha chars */
  yylval.cpp_string = new std::string(yytext);
  return WORD;
}
