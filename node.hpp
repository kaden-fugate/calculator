#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

#include "token.hpp"
using std::vector;

struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    vector<Node*> block = {};

    Token opr;
    Token val;
};

#endif