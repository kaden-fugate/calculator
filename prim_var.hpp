#ifndef PRIM_VAR_HPP
#define PRIM_VAR_HPP

#include "variable.hpp"

template <typename primative> 
class prim_var : public variable {

    private:
        primative val;

};

#endif