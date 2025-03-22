#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>

#include "token.hpp"
#include "node.hpp"

using std::string, std::vector;

class Parser {
    private:
        vector<Token> tokens;
        unsigned long int idx = 0;
    
    public:
        Parser() {}
        Parser(vector<Token> tokens) : tokens(tokens) {}

        Node* expression();
        Node* term();
        Node* factor();
        bool in_bounds();
        void shift();
        void print_tree(Node*);
};

#endif