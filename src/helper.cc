#include "../includes/helper.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool helper_is_number(const std::string &string) {
  std::stringstream ss(string);
  double value;
  ss >> value;
  return ss.eof() && !ss.fail();
}

void helper_remove_trailing_newline(const std::string &filename) {
  std::ifstream inFile(filename);
  if (!inFile.is_open()) {
    std::cerr << "Error opening file for reading: " << filename << std::endl;
    return;
  }

  std::string content;
  std::string line;
  while (std::getline(inFile, line)) {
    content += line + "\n";
  }
  inFile.close();

  if (!content.empty()) {
    if (content.back() == '\n') {
      content.pop_back();
      if (!content.empty() && content.back() == '\r') {
        content.pop_back();
      }
    }
  }

  std::ofstream outFile(filename, std::ios::trunc);
  if (!outFile.is_open()) {
    std::cerr << "Error opening file for writing: " << filename << std::endl;
    return;
  }

  outFile << content;
  outFile.close();
}

int helper_string_int(std::string string) {

  int num = 0;
  try {
    num = std::stoi(string);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Error converting string to int: " << e.what() << std::endl;
  } catch (const std::out_of_range &e) {
    std::cerr << "Error: Value out of range for int: " << e.what() << std::endl;
  }

  return num;
}

std::string helper_decimal_string(int decimal) {
  std::bitset<15> binary(decimal);
  return binary.to_string();
};

void helper_append_file(std::string binary, const std::string &filename) {
  std::ofstream outputFile;
  outputFile.open(filename, std::ios::app);
  if (outputFile.is_open()) {
    outputFile << binary << std::endl;
    outputFile.close();
  } else {
    std::cerr << "Error opening file for appending." << std::endl;
  }
}

int helper_delimiter_pos(const std::string &line, char delimiter) {
  int pos = line.find(delimiter);
  if (pos == std::string::npos) {
    return 0;
  };
  return pos;
};

std::string
helper_find_value(const std::string &key,
                  const std::unordered_map<std::string, std::string> &table) {
  auto it = table.find(key);
  if (it != table.end()) {
    return it->second;
  } else {
    return "0";
  }
  return "0";
};
