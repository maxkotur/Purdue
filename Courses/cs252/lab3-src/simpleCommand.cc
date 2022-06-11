#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <sys/types.h>
#include <regex.h>
#include <dirent.h>
#include <iostream> 
#include <string> 

#include "string.h"

#include <iostream>

#include "simpleCommand.hh"

std::vector<std::string> allpaths;

bool compareFunction (std::string *a, std::string *b) {
  return *a<*b;
}

bool comparePrefixes (std::string a, std::string b) {
  return a<b;
}

SimpleCommand::SimpleCommand() {
  _argumentsArray = std::vector<std::string *>();
}

SimpleCommand::~SimpleCommand() {
  // iterate over all the arguments and delete them
  for (auto & arg : _argumentsArray) {
    delete arg;
  }
}

void SimpleCommand::insertArgument( std::string * argument ) {
  // simply add the argument to the vector
  unsigned int args = _argumentsArray.size();
  if ((*argument)[0] == '~') {
    std::string arg = *argument;
    *argument = tilda(arg);
  }
  else if (strchr((*argument).c_str(), '*') || strchr((*argument).c_str(), '?')) {
    std::string arg = *argument;
    wild_card(arg);
    if (args == _argumentsArray.size()) {
      _argumentsArray.push_back(argument);
    }
    return;
  }
  _argumentsArray.push_back(argument);
}

void SimpleCommand::wild_card(std::string arg) {
  std::string original = arg;
  for (unsigned int i = 0; i < arg.size(); i++) {
    if (arg[i] == '*') {
      arg.insert(i, 1, '.');
      i++;
    }
    if (arg[i] == '.') {
      arg.insert(i, 1, '\\');
      i++;
    }
    if (arg[i] == '?') {
      arg[i] = '.';
    }
  }
  arg.insert(0, 1, '^');
  arg.push_back('$');
  regex_t reg;
  std::vector<std::string *> args;
  int expbuf = regcomp( &reg, arg.c_str(), REG_EXTENDED | REG_NOSUB);
  if (expbuf < 0) {
    perror("regcomp");
    return;
  }
  
  if (original[0] == '/') {
    unsigned int i = 1;
    int index = 0;
    while (original[i] != '*') {
      if (original[i] == '/') {
        index = i;
      }
      i++;
    }
    std::string prefix = original.substr(0, index);
    i = index + 1;
    // std::cout << "first prefix is : " << prefix << '\n';
    std::vector<std::string> prefixes;
    prefixes.push_back(prefix);
    
    std::string suff = "";
    std::vector<std::string> suffixes;
    while (i < original.size()) {
      if (original[i] == '/') {
        // std::cout << "suffix is: " << suff << '\n';
        suffixes.push_back(suff);
        suff = "";
        i++;
        continue;
      }
      suff += original[i];
      i++;
    }
    suffixes.push_back(suff);
    // std::cout << "suffix is: " << suff << '\n';
    for (unsigned int i = 0; i < suffixes.size(); i++) {
      prefixes = wild_Expansions(prefixes, suffixes[i]);
    }
    std::sort(prefixes.begin(), prefixes.end(), comparePrefixes);
    for (unsigned int i = 0; i < prefixes.size(); i++) {
      std::string * addin = new std::string(prefixes[i]);
      _argumentsArray.push_back(addin);
    }
    return;
  }
  DIR *dir = opendir(".");
  if (dir == NULL) {
    perror("opendir");
    return;
  }
  struct dirent * ent;
  regmatch_t match;
  while ((ent = readdir(dir)) != NULL) {
  	if (regexec(&reg, ent->d_name, 1, &match, 0) == 0) {
      if (original[0] != '.' && std::string(ent->d_name)[0] != '.') {
        // std::cout << "matches is :" << std::string(ent->d_name) << '\n';
        std::string * temp = new std::string(ent->d_name);
        args.push_back(temp);
      }
      else if (original[0] == '.') {
        std::string * temp = new std::string(ent->d_name);
        args.push_back(temp);
      }
    }
  }

  std::sort(args.begin(), args.end(), compareFunction);
  for (unsigned int i = 0; i < args.size(); i++) {
    _argumentsArray.push_back(args[i]);
  }

  regfree(&reg);
  closedir(dir);
  return;
}

std::vector<std::string> SimpleCommand::wild_Expansions(std::vector<std::string> prefixes, std::string suffix) {
  std::vector<std::string> new_prefixes;
  for (unsigned int i = 0; i < suffix.size(); i++) {
    if (suffix[i] == '*') {
      suffix.insert(i, 1, '.');
      i++;
    }
    if (suffix[i] == '.') {
      suffix.insert(i, 1, '\\');
      i++;
    }
    if (suffix[i] == '?') {
      suffix[i] = '.';
    }
  }
  suffix.insert(0, 1, '^');
  suffix.push_back('$');
  for (unsigned int i = 0; i < prefixes.size(); i++) {
    regex_t reg;
    int expbuf = regcomp( &reg, suffix.c_str(), REG_EXTENDED | REG_NOSUB);
    if (expbuf < 0) {
      prefixes.erase(prefixes.begin() + i);
      i--;
      continue;
    }
    // std::cout << "path : " << prefixes[i] << '\n';
    if (prefixes[i] == "") {
      prefixes[i] = "/";
    }
    // std::cout << "reg : " << suffix << '\n';
    DIR *dir = opendir(prefixes[i].c_str());
    if (dir == NULL) {
      prefixes.erase(prefixes.begin() + i);
      i--;
      continue;
    }
    struct dirent * ent;
    regmatch_t match;
    while ((ent = readdir(dir)) != NULL) {
      if (regexec(&reg, ent->d_name, 1, &match, 0) == 0) {
        // std::cout << "matches is :" << std::string(ent->d_name) << '\n';
        if (suffix[0] != '.' && std::string(ent->d_name)[0] != '.') {
          // std::cout << "matches is :" << std::string(ent->d_name) << '\n';
          std::string t = prefixes[i];
          if (prefixes[i] != "/") {
            t += "/";
          }
          t += std::string(ent->d_name);
          new_prefixes.push_back(t);
        }
        else if (suffix[0] == '.') {
          std::string t = prefixes[i];
          if (prefixes[i] != "/") {
            t += "/";
          }
          t += std::string(ent->d_name);
          new_prefixes.push_back(t);
        }
      }
    }
    regfree(&reg);
    closedir(dir);
  }
  return new_prefixes;
}



std::string SimpleCommand::tilda( std::string argument ) {
  std::string final;
  if (argument.size() == 1) {
    char * e = getenv("HOME");
    final = std::string(e);
  }
  else {
    if (argument[1] == '/') {
      char * e = getenv("HOME");
      final += e;
      final += std::string(argument, 1, argument.size() - 1);
    }
    else {
      final += "/homes";
      final += '/';
      final += std::string(argument, 1, argument.size() - 1);
    }
  }
  return final;
}

// Print out the simple command
void SimpleCommand::print() {
  for (auto & arg : _argumentsArray) {
    std::cout << "\"" << *arg << "\" \t";
  }
  // effectively the same as printf("\n\n");
  std::cout << std::endl;
}
