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
     || letter == '(' || letter == ')' || letter == '=' || letter == ';'
     || letter == '{' || letter == '}')
        return true;

    return false;
}

bool valid_bool(char letter) {
    if (letter == '&' || letter == '|' || letter == '!')
        return true;

    return false;
}

bool valid_comp(char letter) {
    if (letter == '<' || letter == '>' || letter == '=')
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
for (unsigned long int i = 0; i < this->keys.size(); i++){
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

        // exract comparison operator
        else if (this->check_comp())
            this->tokens.push_back( this->extract_comp() );
        
        // extract arithmetic operator
        else if (valid_opr(letter))
            this->tokens.push_back( this->extract_opr() );

        // extract boolean operator
        else if (valid_bool(letter))
            this->tokens.push_back( this->extract_bool() );

        // extract word
        else if (valid_letter(letter))
            this->tokens.push_back( this->extract_word() );
        
        // otherwise, shift ahead
        else
            this->shift();

    }

    return this->tokens;
}

Token Lexer::extract_num() {
    Token token {val: nullptr, type: INT};
    string num = "";

    // get number
    while (this->idx < this->text.length() 
        && valid_digit(this->text[this->idx])){
    
            num += c_to_str(this->text[this->idx]);
        this->shift();

    }

    // check if number is decimal
    if (this->idx < this->text.length() && this->text[this->idx] == '.'){

        if (this->idx + 1 < this->text.length()
            && valid_digit(this->text[this->idx + 1])){
            token.type = LONG;
            num += c_to_str(this->text[this->idx]);
            this->shift();
        }

    }

    // if decimal, get decimal values
    if (token.type == LONG) {

        while (this->idx < this->text.length() 
        && valid_digit(this->text[this->idx])){
    
            num += c_to_str(this->text[this->idx]);
            this->shift();

        }

        long double *data = new long double( std::stold(num) );
        token.val = (void *) data;

    }
    else { 
        int *data = new int ( std::stoi(num) );
        token.val = (void *) data; 
    }

    return token;
}

Token Lexer::extract_opr() {
    string *data = new string( c_to_str(this->text[this->idx]) );

    Token token {val: (void *) data, type: OPR};
    this->shift();

    return token;
}

Token Lexer::extract_word() {
    Token token{val: nullptr, type: VAR};
    string *data = new string("");

    char letter = this->text[this->idx];

    // get word
    while (valid_letter(letter) || valid_digit(letter)) {

        *data += c_to_str(letter);
        this->shift();

        letter = this->text[this->idx];
    }

    // check if func or keyword, otherwise variable name
    if (valid_func(*data))
        token.type = FUNC;

    else if (valid_keyword(*data)){
        if (*data == "if")
            token.type = IF;
        else if (*data == "else")
            token.type = ELSE;
        else if (*data == "while")
            token.type = WHILE;
    }
    token.val = (void *) data;

    return token;
}

Token Lexer::extract_bool() {
    string *data = new string( c_to_str(this->text[this->idx]) );

    Token token {val: (void *) data, type: BOOL};
    this->shift();

    return token;
}

Token Lexer::extract_comp() {

    Token token{val: nullptr, type: COMP};
    string *data = new string("");

    char letter = this->text[this->idx];

    // get word
    while (valid_comp(letter)) {

        *data += c_to_str(letter);
        this->shift();

        letter = this->text[this->idx];
    }

    token.val = (void *) data;

    return token;

}

void Lexer::shift() { this->idx++; }

bool Lexer::check_comp() {

    // check that theres another character after current idx, check that first
    // character is comparison char
    if (this->idx + 1 < this->text.length() && valid_comp(this->text[this->idx])){

        if (this->text[this->idx] == '='){

            if (this->text[this->idx + 1] == '=')
                return true;

        }
        else return true;
        
    }

    return false;
}

void Lexer::print_tokens() {

    Data val;

    for (long unsigned int i = 0; i < this->tokens.size(); i++){

        string opr = "";
        bool is_opr = !(this->tokens[i].type == LONG || this->tokens[i].type == INT);

        if (!is_opr){
            val = this->tokens[i].get_val();
            std::visit([](auto&& val) {
                std::cout << "(" << val << " ";
            }, val);
            std::cout << this->tokens[i].type << "), ";
        }
        else { 
            opr = this->tokens[i].to_str();
            std::cout << "(" << opr << " " << this->tokens[i].type << "), ";
        }
    }
    std::cout << "\n";
}