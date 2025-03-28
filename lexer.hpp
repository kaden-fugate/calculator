#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <variant>

#include "token.hpp"

using std::string, std::vector, std::variant;

class Lexer {
    private:
        vector<Token> tokens;
        string text = "";
        long unsigned int idx = 0;
        Token cur_token {val: nullptr, type: INT};
        vector<string> keys;
        vector<string> funcs;
        vector<string> bools;
    
    public:

        // constructors
        Lexer() {}
        Lexer(string text, vector<string> keys, vector<string> funcs,
              vector<string> bools) : 
            text(text), keys(keys), funcs(funcs), bools(bools) {}

        // main function
        vector<Token> tokenize();

        // important extraction functions
        Token extract_num();
        Token extract_opr();
        Token extract_word();
        Token extract_bool();
        Token extract_comp();
        
        // helper functions
        bool valid_func(string);
        bool valid_keyword(string);
        void print_tokens();
        void shift();
        bool check_comp();
    
    
};

#endif