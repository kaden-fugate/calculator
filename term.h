#ifndef TERM_H
#define TERM_H

#include "function.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

struct term {

    float coefficient;
    struct function *inner;
    struct function *power;

    int has_variable;

};

struct term *create_term();
void free_term(struct term *);
void term_from_str(char *);
char *format_coefficient(char *, int *, int *);

#endif