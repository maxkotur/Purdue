/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 * DO NOT PUT THIS PROJECT IN A PUBLIC REPOSITORY LIKE GIT. IF YOU WANT 
 * TO MAKE IT PUBLICALLY AVAILABLE YOU NEED TO REMOVE ANY SKELETON CODE 
 * AND REWRITE YOUR PROJECT SO IT IMPLEMENTS FUNCTIONALITY DIFFERENT THAN
 * WHAT IS SPECIFIED IN THE HANDOUT. WE OFTEN REUSE PART OF THE PROJECTS FROM  
 * SEMESTER TO SEMESTER AND PUTTING YOUR CODE IN A PUBLIC REPOSITORY
 * MAY FACILITATE ACADEMIC DISHONESTY.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

#include "command.hh"
#include "shell.hh"

void myunputc(int);

int status = 0;

Command::Command() {
    // Initialize a new vector of Simple Commands
    _simpleCommandsArray = std::vector<SimpleCommand *>();

    _outFileName = NULL;
    _inFileName = NULL;
    _errFileName = NULL;
    exlcam_pid = 0;
    lastcmd = "";
    _backgnd = false;
    _append = false;
}

void Command::insertSimpleCommand( SimpleCommand * simpleCommand ) {
    // add the simple command to the vector
    _simpleCommandsArray.push_back(simpleCommand);
}

void Command::clear() {
    // deallocate all the simple commands in the command vector
    for (auto simpleCommand : _simpleCommandsArray) {
        delete simpleCommand;
    }

    // remove all references to the simple commands we've deallocated
    // (basically just sets the size to 0)
    _simpleCommandsArray.clear();
  
    if ( _outFileName && _outFileName != _errFileName ) {
        delete _outFileName;
    }
    _outFileName = NULL;

    if ( _inFileName ) {
        delete _inFileName;
    }
    _inFileName = NULL;

    if ( _errFileName ) {
        delete _errFileName;
    }
    _errFileName = NULL;

    _backgnd = false;
    _append = false;
    
}

void Command::print() {
    printf("\n\n");
    printf("              COMMAND TABLE                \n");
    printf("\n");
    printf("  #   Simple Commands\n");
    printf("  --- ----------------------------------------------------------\n");

    int i = 0;
    // iterate over the simple commands and print them nicely
    for ( auto & simpleCommand : _simpleCommandsArray ) {
        printf("  %-3d ", i++ );
        simpleCommand->print();
    }

    printf( "\n\n" );
    printf( "  Output       Input        Error        Background    Append   \n" );
    printf( "  ------------ ------------ ------------ ------------ ------------\n" );
    printf( "  %-12s %-12s %-12s %-12s %-12s\n",
            _outFileName?_outFileName->c_str():"default",
            _inFileName?_inFileName->c_str():"default",
            _errFileName?_errFileName->c_str():"default",
            _backgnd?"YES":"NO",
            _append?"YES":"NO");
    printf( "\n\n" );
}

void Command::execute() {
  // Don't do anything if there are no simple commands
  if ( _simpleCommandsArray.size() == 0 ) {
      Shell::prompt();
      return;
  }
  
  // Exits out of shell if user writes "exit"
  if (!strcmp(_simpleCommandsArray[0]->_argumentsArray[0]->c_str(), "exit")) {
    printf("Good bye!!\n");
    clear();
    _exit(1);
  }

  // Print contents of Command data structure
  //print();
  
  int tmpin=dup(0);
  int tmpout=dup(1);
  int tmperr=dup(2);
    
  int fdin;
  int fdout;
  int fderr;
    

	if (_inFileName) {
		fdin = open(_inFileName->c_str(), O_RDONLY);
	}
	else {
		fdin = dup(tmpin);
	}
  int ret;
  for ( unsigned i = 0; i <  _simpleCommandsArray.size(); i++) {
    dup2(fdin,0);
    close(fdin);
    if (!strcmp(_simpleCommandsArray[i]->_argumentsArray[0]->c_str(), "setenv")) {
      if (setenv(_simpleCommandsArray[i]->_argumentsArray[1]->c_str(), _simpleCommandsArray[i]->_argumentsArray[2]->c_str(), 1)) {
        perror("setenv");
      }
      clear();
      Shell::prompt();
      return;
    }
    if (!strcmp(_simpleCommandsArray[i]->_argumentsArray[0]->c_str(), "unsetenv")) {
      if (setenv(_simpleCommandsArray[i]->_argumentsArray[1]->c_str(), _simpleCommandsArray[i]->_argumentsArray[2]->c_str(), 1)) {
        perror("unsetenv");
      }
      clear();
      Shell::prompt();
      return;
    }
    if (!strcmp(_simpleCommandsArray[i]->_argumentsArray[0]->c_str(), "cd")) {
      int errorcd;
      if (_simpleCommandsArray[i]->_argumentsArray.size() == 1) {
        errorcd = chdir(getenv("HOME"));
      }
      else {
        errorcd = chdir(_simpleCommandsArray[i]->_argumentsArray[1]->c_str());
      }
      if (errorcd < 0) {
        fprintf(stderr, "cd: can't cd to %s", _simpleCommandsArray[i]->_argumentsArray[1]->c_str());
      }
      clear();
      Shell::prompt();
      return;
    }
    if (!strcmp(_simpleCommandsArray[i]->_argumentsArray[0]->c_str(), "source")) {
      std::ifstream ifstream;
      ifstream.open(_simpleCommandsArray[i]->_argumentsArray[1]->c_str());
      
      // gets the command from the file
      std::string command;
      command.assign(std::istreambuf_iterator<char>(ifstream),std::istreambuf_iterator<char>());
      ifstream.close();
      
      std::reverse(command.begin(), command.end());
      
      myunputc('\n');
      for (unsigned i = 0; i < command.size(); i++) {
        myunputc(command[i]);
      }
      
      clear();
      Shell::prompt();
      return;
    }
    if (i ==  _simpleCommandsArray.size() - 1) {
      if (_outFileName) {
        if (_append) {
          fdout = open(_outFileName->c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
        }
        else {
          fdout = open(_outFileName->c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }
      }
      else {
       	fdout = dup(tmpout);
      }
      if (_errFileName) {
       if (_append) {
          fderr = open(_errFileName->c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
        }
        else {
          fderr = open(_errFileName->c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }
      }
      else {
        fderr = dup(tmperr);
      }
    }
    else {
      int fdpipe[2];
  		pipe(fdpipe);
  		fdout=fdpipe[1];
  		fdin=fdpipe[0];
    }
    dup2(fdout,1);
    close(fdout);
    dup2(fderr,2);
    close(fderr);
    ret = fork();
    if (ret == 0) {
      if (!strcmp(_simpleCommandsArray[i]->_argumentsArray[0]->c_str(), "printenv")) {
        char ** env = environ;
        
        while (*env++) {
          std::cout << *env << "\n";
        }
        fflush(stdout);
        _exit(1);
      }
      std::vector<char*> stl;
      stl.reserve(_simpleCommandsArray[i]->_argumentsArray.size());
      for (unsigned j = 0; j < _simpleCommandsArray[i]->_argumentsArray.size(); j++) {
        const char * arg = _simpleCommandsArray[i]->_argumentsArray[j]->c_str();
        stl.push_back(const_cast<char *>(arg));
      }
      stl.push_back(NULL);
      char* const* rem = stl.data();
      execvp( _simpleCommandsArray[i]->_argumentsArray[0]->c_str(), rem);
      perror("execvp");
      
      _exit(1);
    }
    else if (ret < 0) {
      // There was an error in fork 
      perror("fork");
      _exit(2);
    }
  }
  
  dup2(tmpin, 0);
  dup2(tmpout, 1);
  dup2(tmperr, 2);
  close(tmpin);
  close(tmpout);
  close(tmperr);
  
  int len = _simpleCommandsArray[_simpleCommandsArray.size() - 1]->_argumentsArray.size() - 1;
  lastcmd = _simpleCommandsArray[_simpleCommandsArray.size() - 1]->_argumentsArray[len]->data();
  setenv("lastarg", lastcmd.c_str(), 1);
  
  if (!_backgnd) {
    waitpid(ret, &status, 0);
    setenv("QU", std::to_string(WEXITSTATUS(status)).c_str(), 1);
  }
  else {
    exlcam_pid = ret;
  }
  // Clear to prepare for next command
  clear();

  // Print new prompt
  if (isatty(0)) {
    Shell::prompt();
  }
}

SimpleCommand * Command::_currSimpleCommand;
