#ifndef FUNCTION_H
#define FUNCTION_H

#include "term.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

struct function {

    int num_terms;
    struct term **terms;

};

struct function *create_function();
void free_function(struct function *);
struct function *func_from_str(char *);

#endif