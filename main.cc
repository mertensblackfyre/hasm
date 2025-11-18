#include "includes/helper.h"
#include "includes/parser.h"
#include "includes/translate.h"
#include <fstream>
#include <iostream>
#include <string>

void removeTrailingNewline(const std::string &filename) {
  std::ifstream inFile(filename);
  if (!inFile.is_open()) {
    std::cerr << "Error opening file for reading: " << filename << std::endl;
    return;
  }

  std::string content;
  std::string line;
  while (std::getline(inFile, line)) {
    content +=
        line +
        "\n"; // Re-add newline characters as they were removed by getline
  }
  inFile.close();

  // Check and remove the trailing newline
  if (!content.empty()) {
    if (content.back() == '\n') {
      content.pop_back(); // Remove the last character (newline)
      if (!content.empty() && content.back() == '\r') {
        content.pop_back(); // Remove carriage return if present
      }
    }
  }

  std::ofstream outFile(
      filename, std::ios::trunc); // Open in truncate mode to clear content
  if (!outFile.is_open()) {
    std::cerr << "Error opening file for writing: " << filename << std::endl;
    return;
  }

  outFile << content;
  outFile.close();
}
int main() {

  Parser parse;
  Translate t;
  std::string line;

  std::ifstream inputFile("m.asm");
  if (!inputFile.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  parse.parse_symbols("sum.asm");
  parse.parse_variables("sum.asm");
  for (auto it : parse.SYMBOL_TABLE) {
    std::cout << "(SYM) " << it.first << " [Val] " << it.second << std::endl;
  }
  /*
  while (std::getline(inputFile, line)) {
    if (line.size() < 1) {
      continue;
    } else if (line[0] == '/') {
      continue;
    } else if (line[0] == '@') {
      std::string final_output = t.translate_a_instruc(line);
      helper_append_file(final_output);
    } else {
      C_Instruction m = parse.parse_C__(line);
      std::string final_output = t.translate_c_instruc(m);
      helper_append_file(final_output);
    };
  };



  removeTrailingNewline("final.hack");
  */

  inputFile.close();
  return 0;
}
