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
        Token cur_tok = tokens[0];
        unsigned long int idx = 0;
    
    public:
        Parser() {}
        Parser(vector<Token> tokens) : tokens(tokens){}

        Node* expression();
        Node* term();
        Node* factor();
        Node *variable();
        Node *statement();

        bool in_bounds();
        void shift();
        void print_tree(Node*);
};

#endif