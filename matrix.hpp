#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "variable.hpp"

#include <vector>

using std::vector;

template <typename primative>
class matrix : public variable {

    private: 
        vector< vector<primative> > data;

};

#endif