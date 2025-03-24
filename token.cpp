#include "token.hpp"

Data Token::get_val() {
    Data val = 0;

    if (this->type == INT)
        val = *((int *) this->val);

    else if (this->type == LONG)
        val = *((long double *) this->val);
    
    return val;
}

std::string Token::to_str() { return *((std::string *) this->val); }
int Token::to_int() { return *((int *) this->val); }
long double Token::to_long() { return *((long double *) this->val); }