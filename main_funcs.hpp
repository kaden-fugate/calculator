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

enum term_type {
    INT,
    FLOAT,
    MATRIX,
    PARNTH,
    VAR,
    FUNC_CALL
};

void print_input_type(input_type);
void print_term_type(term_type);
string get_input();
input_type parse_input(string);
void assign(string);
string get_var_name(string);
string get_term(string, term_type*);
string get_parnth_str(string);
string get_mat_string(string);
string get_operator(string);

#endif