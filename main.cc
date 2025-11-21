#include "includes/helper.h"
#include "includes/parser.h"
#include "includes/translate.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {

  if (argc < 3) {
    std::cerr << "Usage: program <filename> <output filename>\n";
    return 1;
  }

  std::string input = argv[1];
  std::string output = argv[2];

  Parser parse;
  Translate t;
  std::string line;

  std::ifstream inputFile(input);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }
  parse.parse_symbols(input);
  parse.parse_variables(input);

  while (std::getline(inputFile, line)) {
    if (line.size() < 1 || line[0] == '/' || line[0] == '(') {
      continue;
    } else if (line[0] == '@') {
      std::string final_output = t.translate_a_instruc(line);
      helper_append_file(final_output, output);
    } else {
      C_Instruction m = parse.parse_C_instruction(line);
      std::string final_output = t.translate_c_instruc(m);
      helper_append_file(final_output, output);
    };
  };

  if (output == "") {
    output = "final.hack";
  }
  helper_remove_trailing_newline(output);
  inputFile.close();
  return 0;
}
