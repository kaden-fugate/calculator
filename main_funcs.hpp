#ifndef MAIN_FUNCS_HPP
#define MAIN_FUNCS_HPP

#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;

enum input_type {
    ASSIGN,
    ARITH,
    FUNC,
    PRINT,
    VARS,
    EXIT,
    ERR
};

string get_input();
input_type parse_input(string);

#endif