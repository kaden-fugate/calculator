#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <variant>
#include <unordered_map>

#include "token.hpp"
#include "node.hpp"
#include "operators.hpp"

using std::variant, std::unordered_map, std::string;

class Interpreter {
    private:
        Node *root = nullptr;
        unordered_map<string, Data> *map = nullptr;
    
    public:
        Interpreter(){}
        Interpreter(Node* root, unordered_map<string, Data> *map) : root(root), 
        map(map) {}
        
        Token compute(Token, Token, string);
        Token interpret(Node*);

        void insert(string, Data);
        bool in_map(string);
        void print_map();
};

#endif