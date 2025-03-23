#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <variant>

using Data = std::variant<int, long double>;

enum Type {
    INT,
    LONG,
    MATRIX,
    FUNC,
    VAR,
    OPR,
    KEY,
    NONE
};

// will change this later when we want to start adding matrices
struct Token {
    void *val = nullptr;
    Type type = NONE; 

    Data get_val() {
        if (this->type == INT)
            return *((int *) this->val);

        else if (this->type == LONG)
            return *((long double *) this->val);

        // else if (this->type == FUNC || this->type == VAR || this->type == OPR
        //       || this->type == KEY)
        //     return *((std::string *) this->val);
        
        return 1;
    }
};

#endif