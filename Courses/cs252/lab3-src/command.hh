#ifndef command_hh
#define command_hh

#include "simpleCommand.hh"

// Command Data Structure

struct Command {
  std::vector<SimpleCommand *> _simpleCommandsArray;
  std::string * _outFileName;
  std::string * _inFileName;
  std::string * _errFileName;
  std::string lastcmd;
  int exlcam_pid;
  bool _backgnd;
  bool _append;

  Command();
  void insertSimpleCommand( SimpleCommand * simpleCommand );

  void clear();
  void print();
  void execute();

  static SimpleCommand *_currSimpleCommand;
};

#endif
