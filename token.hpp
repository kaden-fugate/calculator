#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <variant>

using Data = std::variant<int, long double>;

enum Type {
    INT,
    LONG,
    MATRIX,
    FUNC,
    VAR,
    OPR,
    KEY,
    BOOL,
    COMP,
    NONE
};

// NOTES ABOUT STRUCTURE OF TOKEN CLASS:
//
// this token holds a void* instead of a Data type because we don't want type
// conflicts with the functions in operators.hpp. 
// 
// because these functions only accept int/long inputs, if we use a variant to 
// store them, we cannot include a string in the variant (and therefore cannot
// store variable names, keywords, operators, etc. in our tokens).
//
// instead we can simply make this a void* and put reasonable trust in the
// type data member (sounds sketchy lol). with this, we can assume that if type
// is VAR, FUNC, OPR, or KEY, then we can assume that it's a string and can
// convert it accordingly. otherwise, we can just convert the value via the
// get_val() method.
//
// when matrices are added, we can simply overload the Matrix class' operators
// as needed.
struct Token {
    void *val = nullptr;
    Type type = NONE; 

    Data get_val();

    std::string to_str();
    int to_int();
    long double to_long();
    void print();
};

#endif