#ifndef MAIN_FUNCS_HPP
#define MAIN_FUNCS_HPP

#include <iostream>
#include <string>

using std::string, std::cin, std::cout, std::endl;

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

#endif