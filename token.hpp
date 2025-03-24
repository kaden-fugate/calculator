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
    NONE
};

// will change this later when we want to start adding matrices
struct Token {
    void *val = nullptr;
    Type type = NONE; 

    Data get_val();

    std::string to_str();
    int to_int();
    long double to_long();
};

#endif