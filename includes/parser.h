#ifndef PARSER_H
#define PARSER_H

#include "helper.h"
#include <iostream>

struct C_Instruction {
  std::string dest{};
  std::string comp{};
  std::string jump{};
};

class Parser {

public:
  static inline std::string parse_A__(const std::string &line);
  static inline C_Instruction parse_C__(const std::string &line);
};

std::string Parser::parse_A__(const std::string &line) {
  return line.substr(1, line.size());
};

C_Instruction Parser::parse_C__(const std::string &line) {

  C_Instruction ins{"", "", ""};

  int equal_pos = helper_delimiter_pos(line, '=');
  int semicolon_pos = helper_delimiter_pos(line, ';');

  if (equal_pos && semicolon_pos) {
    ins.dest = line.substr(0, equal_pos);
    ins.comp = line.substr(equal_pos + 1, semicolon_pos - 3);
    ins.jump = line.substr(semicolon_pos + 1, line.size() - 1);
  } else if (equal_pos && !semicolon_pos) {
    ins.dest = line.substr(0, equal_pos);
    ins.comp = line.substr(equal_pos + 1, line.size() - 1);
  } else if (!equal_pos && semicolon_pos) {
    ins.comp = line.substr(0, semicolon_pos - 1);
    ins.jump = line.substr(semicolon_pos + 1, line.size() - 1);
  } else {
    ins.comp = line;
  };
  return ins;
};

#endif
