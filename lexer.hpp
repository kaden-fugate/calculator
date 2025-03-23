#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>

#include "token.hpp"

using std::string, std::vector;

class Lexer {
    private:
        vector<Token> tokens;
        string text = "";
        long unsigned int idx = 0;
        Token cur_token {val: nullptr, type: INT};
        vector<string> keys;
        vector<string> funcs;
    
    public:

        // constructors
        Lexer() {}
        Lexer(string text, vector<string> keys, vector<string> funcs) : 
            text(text), keys(keys), funcs(funcs) {}

        // functionalities
        vector<Token> tokenize();
        void shift();
        Token extract_num();
        Token extract_opr();
        Token extract_word();
        void print_tokens();
        bool valid_func(string);
        bool valid_keyword(string);
    
    
};

#endif