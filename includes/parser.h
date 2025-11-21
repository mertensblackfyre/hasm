#ifndef PARSER_H
#define PARSER_H

#include "helper.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <unordered_map>

struct C_Instruction {
  std::string dest{};
  std::string comp{};
  std::string jump{};
};

class Parser {
public:
  inline static std::unordered_map<std::string, std::string> SYMBOL_TABLE = {
      {"R0", "0"},         {"R1", "1"},      {"R2", "2"},   {"R3", "3"},
      {"R4", "4"},         {"R5", "5"},      {"R6", "6"},   {"R7", "7"},
      {"R8", "8"},         {"R9", "9"},      {"R10", "10"}, {"R11", "11"},
      {"R12", "12"},       {"R13", "13"},    {"R14", "14"}, {"R15", "15"},
      {"SCREEN", "16384"}, {"KBD", "24576"}, {"SP", "0"},   {"LCL", "1"},
      {"ARG", "2"},        {"THIS", "3"},    {"THAT", "4"},
  };

  inline void parse_symbols(const std::string &fname);
  inline void parse_variables(const std::string &fname);

  static inline std::string parse_instruction(const std::string &line);
  static inline std::string parse_A_instruction(const std::string &line);
  static inline C_Instruction parse_C_instruction(const std::string &line);

private:
  inline static int counter = 0;
  inline static int memory_counter = 16;
};

std::string Parser::parse_instruction(const std::string &line) {
  std::string parsed_string = "";
  for (const char &ch : line) {
    if (ch == '/')
      break;
    if (!std::isspace(ch) && ch != '/')
      parsed_string += ch;
  };

  return parsed_string;
};

std::string Parser::parse_A_instruction(const std::string &line) {
  if (line.size() < 1) {
    return "";
  }
  return line.substr(1, line.size() - 1);
};

void Parser::parse_symbols(const std::string &fname) {
  std::string line;

  std::ifstream inputFile(fname);
  if (!inputFile.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
  }

  while (std::getline(inputFile, line)) {
    if (line.size() < 1 || line[0] == '/') {
      continue;
    } else if (line[0] == '(') {
      std::string a_ins = parse_instruction(line);
      a_ins = a_ins.substr(1, a_ins.size() - 2);
        if (!SYMBOL_TABLE.count(a_ins)) {
          SYMBOL_TABLE[a_ins] = std::to_string(counter);
        };
    } else {
      counter++;
    }
  };
  inputFile.close();
};

void Parser::parse_variables(const std::string &fname) {
  std::string line;
  std::ifstream inputFile(fname);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
  }
  while (std::getline(inputFile, line)) {
    if (line[0] == '@') {
      std::string a_ins = parse_A_instruction(parse_instruction(line));

      if (!SYMBOL_TABLE.count(a_ins)) {
        SYMBOL_TABLE[a_ins] = std::to_string(memory_counter);
        memory_counter++;
      };
    }
  };

  inputFile.close();
};

C_Instruction Parser::parse_C_instruction(const std::string &line) {

  C_Instruction ins{"", "", ""};

  std::string parsed_string = parse_instruction(line);
  int equal_pos = helper_delimiter_pos(parsed_string, '=');
  int semicolon_pos = helper_delimiter_pos(parsed_string, ';');

  if (equal_pos && semicolon_pos) {
    ins.dest = parsed_string.substr(0, equal_pos);
    ins.comp = parsed_string.substr(equal_pos + 1, semicolon_pos - 2);
    ins.jump = parsed_string.substr(semicolon_pos + 1, line.size() - 1);
  } else if (equal_pos && !semicolon_pos) {
    ins.dest = parsed_string.substr(0, equal_pos);
    ins.comp = parsed_string.substr(equal_pos + 1, line.size() - 1);
  } else if (!equal_pos && semicolon_pos) {
    ins.comp = parsed_string.substr(0, semicolon_pos);
    ins.jump = parsed_string.substr(semicolon_pos + 1, line.size() - 1);
  } else {
    ins.comp = parsed_string;
  };

  return ins;
};

#endif
