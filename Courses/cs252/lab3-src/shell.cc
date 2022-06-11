#include <cstdio>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.hh"

int yyparse(void);

void Shell::prompt() {
  if (isatty(0)) {
    char *e = getenv("PROMPT");
    if (e == NULL) {
      setenv("PROMPT", "myshell>", 1);
      char s[9] = "myshell>";
      e = s;
    }
    printf("%s", e);
    fflush(stdout);
  }
}

extern "C" void ctrlc( int sig )
{
	fprintf( stderr, "\nsig:%d      Ouch!\n", sig);
  Shell::prompt();
}

extern "C" void zombie(int sig)
{
  int temp = sig;
  sig = temp;
	while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {
    Shell::prompt();
  }
}

int main() {
  // If ctrlc
  struct sigaction sa;
  sa.sa_handler = ctrlc;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  
  if(sigaction(SIGINT, &sa, NULL)){
      perror("sigaction");
      _exit(2);
  }
  
  // If zombie
  struct sigaction zom;
  zom.sa_handler = zombie;
  sigemptyset(&zom.sa_mask);
  zom.sa_flags = SA_RESTART | SA_NOCLDSTOP;
  
  if (sigaction(SIGCHLD, &zom, 0) == -1) {
    perror("sigaction");
    _exit(2);
  }
  
  Shell::prompt();
  yyparse();
}

Command Shell::_currentCommand;
