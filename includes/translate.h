#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "constant.h"
#include "helper.h"
#include "parser.h"
#include <bitset>
#include <iostream>

class Translate {

public:
  static inline std::string translate_a_instruc(const std::string &line);
  static inline std::string translate_c_instruc(const C_Instruction &line);
};

std::string Translate::translate_a_instruc(const std::string &line) {
  std::string parsed_string = Parser::parse_instruction(line);
  std::string string_value = Parser::parse_A_instruction(parsed_string);

  if (!helper_is_number(string_value) && Parser::SYMBOL_TABLE.count(string_value)) {
    string_value = Parser::SYMBOL_TABLE[string_value];
  };

  int number_value = helper_string_int(string_value);
  std::string binary_string = helper_decimal_string(number_value);
  std::string ss = binary_string.insert(0, "0");

  // std::cout << parsed_string << std::endl;
  return ss;
};

std::string
Translate::translate_c_instruc(const C_Instruction &parsed_strings) {

  std::string final_output = "111";

  std::string comp_binary_value =
      helper_find_value(parsed_strings.comp, COMP_TABLE);

  std::string dest_binary_value =
      helper_find_value(parsed_strings.dest, DEST_TABLE);

  std::string jump_binary_value =
      helper_find_value(parsed_strings.jump, JUMP_TABLE);

  if (comp_binary_value == "0") {
    final_output += "0000000";
  } else {
    final_output += comp_binary_value;
  }

  if (dest_binary_value == "0") {
    final_output += "000";
  } else {
    final_output += dest_binary_value;
  }

  if (jump_binary_value == "0") {
    final_output += "000";
  } else {
    final_output += jump_binary_value;
  }

  // std::cout << parsed_strings.dest << parsed_strings.comp <<
  // parsed_strings.jump
  //      << "-->" << final_output << std::endl;
  return final_output;
};

#endif
