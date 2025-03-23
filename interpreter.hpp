#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <variant>

#include "token.hpp"
#include "node.hpp"
#include "operators.hpp"

using std::variant;

class Interpreter {
    private:
        Node *root = nullptr;
    
    public:
        Interpreter() {}
        Interpreter(Node* root) : root(root) {}
        
        Data compute(Data, Data, std::string);
        Data interpret(Node*);
};

#endif