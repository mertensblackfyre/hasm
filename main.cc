#include "includes/helper.h"
#include "includes/parser.h"
#include "includes/translate.h"
#include <fstream>
#include <iostream>
#include <string>


int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "Usage: program <filename>\n";
    return 1;
  }

  std::string s = argv[1];

  Parser parse;
  Translate t;
  std::string line;

  std::ifstream inputFile(s);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }
  parse.parse_symbols(s);
  parse.parse_variables(s);

  while (std::getline(inputFile, line)) {
    if (line.size() < 1 || line[0] == '/' || line[0] == '(') {
      continue;
    } else if (line[0] == '@') {
      std::string final_output = t.translate_a_instruc(line);
      helper_append_file(final_output);
    } else {
      C_Instruction m = parse.parse_C_instruction(line);
      std::string final_output = t.translate_c_instruc(m);
      helper_append_file(final_output);
    };
  };

  helper_remove_trailing_newline("final.hack");
  inputFile.close();
  return 0;
}
