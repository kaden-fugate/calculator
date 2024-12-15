#ifndef MAIN_FUNCS_HPP
#define MAIN_FUNCS_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

using std::string, std::cin, std::cout, std::endl, std::exception,
      std::runtime_error, std::stringstream;

enum input_type {
    ASSIGN,
    FUNC,
    PRINT,
    VARS,
    EXIT,
    NEWLN
};

void print_type(input_type);
string get_input();
input_type parse_input(string);
void assign(string);

#endif