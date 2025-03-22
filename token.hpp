#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

enum Type {
    LONG,
    INT,
    MATRIX,
    FUNC,
    VAR,
    OPR,
    KEY,
    NONE
};

// will change this later when we want to start adding matrices
struct Token {
    std::string val = "";
    Type type = NONE; 
};

#endif