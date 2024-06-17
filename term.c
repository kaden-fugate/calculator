#include "term.h"

// allocate mem for term, return pointer to it
struct term *create_term(){

    // alloc mem
    struct term *term = malloc(sizeof(struct term));
    assert(term);

    // init
    term->coefficient = 0;
    term->inner = NULL;
    term->power = NULL;

    return term;

}

// free all of the memory associated with a term
void free_term(struct term *term){

    if ( !term ) return;

    // free the functions within then free the term itself
    free_function(term->inner);
    free_function(term->power);

    free(term);

}