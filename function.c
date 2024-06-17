#include "function.h"

// allocate mem for function, return pointer to mem
struct function *create_function() {

    struct function *func = malloc( sizeof(struct function) );
    assert(func); // make sure malloc didnt fail

    func->num_terms = 0;
    func->terms = NULL;

    return func;

}

void free_function(struct function *func) {

    // nothing to free
    if ( !func ) return;

    // free all our terms
    for (uint8_t i = 0; i < func->num_terms; i++)
        free_term( func->terms[i] );

    free(func->terms);
    free(func);

}