#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "constant.h"
#include "helper.h"
#include "parser.h"
#include <bitset>
#include <iostream>

class Translate {

public:
  inline std::string translate_a_instruc(const std::string &parsed_string);
  inline std::string translate_c_instruc(const C_Instruction &parsed_strings);
};

std::string Translate::translate_a_instruc(const std::string &parsed_string) {
  std::string string_value = Parser::parse_A__(parsed_string);
  int number_value = helper_string_int(string_value);
  std::string binary_string = helper_decimal_string(number_value);
  std::string ss = binary_string.insert(0, "0");
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

  return final_output;
};

#endif
