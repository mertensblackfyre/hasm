#ifndef PARSER_H
#define PARSER_H

#include "helper.h"
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
  static inline std::string parse_A__(const std::string &line);
  static inline C_Instruction parse_C__(const std::string &line);

private:
  inline static int counter = 0;
  inline static int memory_counter = 16;
};

std::string Parser::parse_A__(const std::string &line) {
  return line.substr(1, line.size());
};

void Parser::parse_symbols(const std::string &fname) {
  std::string line;

  std::ifstream inputFile(fname);
  if (!inputFile.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
  }

  while (std::getline(inputFile, line)) {
    if (line.size() < 1) {
      continue;
    } else if (line[0] == '/') {
      continue;
    } else if (line[0] == '@') {
      std::string a_ins = parse_A__(line);
      if (a_ins == "LOOP" || a_ins == "END" || a_ins == "STOP") {
        if (!SYMBOL_TABLE.count(a_ins)) {
          SYMBOL_TABLE[a_ins] = std::to_string(counter);
        };
        counter++;
      }
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
      std::string a_ins = parse_A__(line);
      if (!SYMBOL_TABLE.count(a_ins)) {
        SYMBOL_TABLE[a_ins] = std::to_string(memory_counter);
        memory_counter++;
      };
    }
  };

  inputFile.close();
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
