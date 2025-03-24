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
        
        // main funcs
        Token compute(Token, Token, string);
        Token interpret(Node*);

        // map funcs
        void insert(string, Data);
        Data read(string);
        bool in_map(string);
        void print_map();

        // token funcs
        Data get_data(Token);

};

#endif