#include "lexer.hpp"

bool valid_digit(char digit) {
    if ('0' <= digit && digit <= '9')
        return true;

    return false;
}

bool valid_letter(char letter) {
    if (('a' <= letter && letter <= 'z')
     || ('A' <= letter && letter <= 'Z'))
        return true;
    
    return false;
}

bool valid_opr(char letter) {
    if (letter == '+' || letter == '-' || letter == '*' || letter == '/'
     || letter == '(' || letter == ')' || letter == '=')
        return true;

    return false;
}

bool Lexer::valid_func(string word) {
    for (unsigned long int i = 0; i < this->funcs.size(); i++){
        if (this->funcs[i] == word)
            return true;
    }
    
    return false;
}

bool Lexer::valid_keyword(string word) {
    for (unsigned long int i = 0; i < this->funcs.size(); i++){
        if (this->keys[i] == word)
            return true;
    }
    
    return false;
}

string c_to_str(char letter) {
    return string(1, letter);
}

vector<Token> Lexer::tokenize() {

    // iterate through string to tokenize
    while (this->idx < this->text.length()) {

        char letter = this->text[this->idx];

        // extract number
        if (valid_digit(letter))
            this->tokens.push_back( this->extract_num() );
        
        // extract operator
        else if (valid_opr(letter))
            this->tokens.push_back( this->extract_opr() );

        // extract word
        else if (valid_letter(letter))
            this->tokens.push_back( this->extract_word() );
        
        // otherwise, shift ahead
        else
            this->shift();

    }

    return this->tokens;
}

void Lexer::shift() { this->idx++; }

Token Lexer::extract_num() {
    Token num {val: "", type: INT};

    // get number
    while (this->idx < this->text.length() 
        && valid_digit(this->text[this->idx])){
    
        num.val += c_to_str(this->text[this->idx]);
        this->shift();

    }

    // check if number is decimal
    if (this->idx < this->text.length() && this->text[this->idx] == '.'){

        if (this->idx + 1 < this->text.length()
            && valid_digit(this->text[this->idx + 1])){
            num.type = LONG;
            num.val += c_to_str(this->text[this->idx]);
            this->shift();
        }

    }

    // if decimal, get decimal values
    if (num.type == LONG) {

        while (this->idx < this->text.length() 
        && valid_digit(this->text[this->idx])){
    
            num.val += c_to_str(this->text[this->idx]);
            this->shift();

        }

    }

    return num;
}

Token Lexer::extract_opr() {
    Token opr {val: c_to_str(this->text[this->idx]), type: OPR};
    this->shift();

    return opr;
}

Token Lexer::extract_word() {
    Token word{val: "", type: VAR};

    char letter = this->text[this->idx];

    // get word
    while (valid_letter(letter) || valid_digit(letter)) {

        word.val += c_to_str(letter);
        this->shift();

        letter = this->text[this->idx];
    }

    // check if func or keyword, otherwise variable name
    if (valid_func(word.val))
        word.type = FUNC;

    else if (valid_keyword(word.val))
        word.type = KEY;

    return word;
}

void Lexer::print_tokens() {

    std::cout << "TOKENS: \n";

    for (long unsigned int i = 0; i < this->tokens.size(); i++){
        std::cout << "(" << this->tokens[i].val << " " 
                  << this->tokens[i].type << "), ";
    }
    std::cout << "\n";
}