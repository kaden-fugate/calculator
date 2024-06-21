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
    int inner_has_variable;
    int has_complex_inner;

    struct function *power;
    int power_has_variable;
    int has_complex_power;

};

struct term *create_term();
void free_term(struct term *);
void term_from_str(char *);
char *format_coefficient(char *, int *, int *);
char *get_inner(char *, int *, int *, int *);
char *get_power(char *);

#endif