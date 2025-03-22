#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

#include "token.hpp"

struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    Token opr;
    Token val;
};

#endif