

#include <iostream>
#include <unordered_map>

extern void helper_remove_trailing_newline(const std::string &filename);
extern int helper_string_int(std::string string);
extern std::string helper_decimal_string(int decimal);
extern void helper_append_file(std::string binary);
extern int helper_delimiter_pos(const std::string &line, char delimiter);
extern std::string
helper_find_value(const std::string &key,
                  const std::unordered_map<std::string, std::string> &table);
