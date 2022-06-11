#ifndef simplcommand_hh
#define simplecommand_hh

#include <string>
#include <vector>

struct SimpleCommand {

  // Simple command is simply a vector of strings
  std::vector<std::string *> _argumentsArray;

  SimpleCommand();
  ~SimpleCommand();
  void insertArgument( std::string * argument );
  void print();
  void wild_card(std::string arg);
  std::vector<std::string> wild_Expansions(std::vector<std::string> prefixes, std::string suffix);
  std::string tilda(std::string argument);
};

#endif
