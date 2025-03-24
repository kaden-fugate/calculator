#include "token.hpp"

Data Token::get_val() {
    Data val = 0;

    if (this->type == INT)
        val = this->to_int();

    else if (this->type == LONG)
        val = this->to_long();
    
    return val;
}

std::string Token::to_str() { return *((std::string *) this->val); }
int Token::to_int() { return *((int *) this->val); }
long double Token::to_long() { return *((long double *) this->val); }

void Token::print() {

    if (this->type == INT || this->type == LONG){
        std::visit([](auto&& arg) { std::cout << arg << '\n'; }, this->get_val());
    }

    else std::cout << this->to_str() << '\n';

}