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
    term->has_variable = 0;

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

// 1001 --> 1001
// coef len = 4
// decimal pos = -1
// base start = 1 = 10 ^ 0

// 10.01 --> 10.01
// coef len = 4
// decimal pos = 2
// base start = 0.01 = 10^-2

// 1001. --> 1001.0
// coef len = 5
// decimal pos = 4
// base start = 1 = 10 ^ 0

// .1001 --> 0.1001
// coef len = 5
// decimal pos = 1
// base start = 0.0001 = 10^-4

void term_from_str(char *expr){

    int coeff_len = 0, decimal_pos = -1;
    struct term *term = create_term();

    // if our term has a variable
    if ( strstr(expr, "x") )
        term->has_variable = 1;

    // isolate our coefficient
    char *new_coefficient = format_coefficient(expr, &coeff_len, &decimal_pos);

    // if our term had a coefficient we should assign it to our term, otherwise
    // we will give our term the value 1
    term->coefficient = (coeff_len) ? atof(new_coefficient) : (float) 1;
    
    // check if power is present
    int power_pos = coeff_len;
    if (term->has_variable) ++power_pos;
    if (decimal_pos != -1) ++power_pos;
    printf("\nlen: %d\nnew_coefficient: %s\nconverted_coefficient: %.2lf\nexpr[power_pos]: %c\nshifted: %s\n", coeff_len, new_coefficient, term->coefficient, expr[power_pos], expr + power_pos + 1);
    

    // in function creation, add parentheses
    // need to handle possible inner term. ex: 10.01(x^2+x)^(12)
}

char *format_coefficient(char *expr, int *coeff_len_store, 
                         int *decimal_pos_store) {
    
    // max length coef. we'll hold is 256 chars, otherwise things will break
    char *coefficient = malloc(256); 
    char *new_coefficient = malloc(257);

    // get details about the coefficient
    int coeff_len = 0, decimal_pos = -1;
    for (int i = 0; expr[i] != 'x' && expr[i] != '\0'; i++) {

        // handle decimal point for floats
        if (expr[i] == '.') decimal_pos = i;
        else ++coeff_len;
    }

    // if we need to, change the format of the coefficient. if we have a 
    // string like ".001" or "100.", lets add that leading/trailing zero to
    // maintain a consistent formatting.
    if (decimal_pos != -1){

        // copy over the coefficient to a new string so we can use strcat
        // with it for easy string manipulation
        strncpy(coefficient, expr, coeff_len + 1);
        coefficient[coeff_len + 2] = '\0';
        
        // case where we have no leading zero on our decimal
        if (coefficient[0] == '.') {
            strcpy(new_coefficient, "0");
            strcat(new_coefficient, coefficient);
        }

        // case where we have no trailing zero following our integer
        else if (coefficient[coeff_len] == '.') {
            strcpy(new_coefficient, coefficient);
            strcat(new_coefficient, "0");
        }
    }

    // otherwise, we should just copy the entire coefficient from our 
    // expression into our new_coefficient variable to be converted to a float
    else strncpy(new_coefficient, expr, coeff_len);

    // set additional return types and free some mem
    if (coeff_len_store) *coeff_len_store = coeff_len;
    if (decimal_pos_store) *decimal_pos_store = decimal_pos;
    free(coefficient);

    return new_coefficient;
}