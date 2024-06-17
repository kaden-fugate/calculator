#ifndef TERM_H
#define TERM_H

#include "function.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct term {

    float coefficient;
    struct function *inner;
    struct function *power;

};

struct term *create_term();
void free_term(struct term *);

#endif