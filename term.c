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
    term->inner_has_variable = 0;
    term->has_complex_inner = 0;
    term->power_has_variable = 0;
    term->has_complex_power = 0;

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

    int coeff_len = 0, decimal_pos = -1, inner_len = 0;
    struct term *term = create_term();

    // isolate our coefficient, we'll need to free this later
    char *new_coefficient = format_coefficient(expr, &coeff_len, &decimal_pos);

    // if our term had a coefficient we should assign it to our term, otherwise
    // we will give our term the value 1
    term->coefficient = (coeff_len) ? atof(new_coefficient) : (float) 1;

    // plug in the shifted value of expr into get_inner. this will also store
    // values within terms has_variable and complex_inner data members.
    int inner_pos = (decimal_pos != -1) ? coeff_len + 1 : coeff_len;
    char *inner = get_inner(expr + inner_pos, &inner_len, 
                      &(term->inner_has_variable), &(term->has_complex_inner));

    // if inner term is complex, we should make a new function out of it
    if (term->inner_has_variable && term->has_complex_inner) 
        term->inner = func_from_str(inner);
    
    printf("\nterm: %s\nhas_variable: %d\nhas_complex_inner: %d\nshifted expr: %s\n", inner, term->inner_has_variable, term->has_complex_inner, expr + inner_pos + inner_len);
    // check if power is present
    int power_pos = inner_pos + inner_len;
    char *power = get_power(expr + power_pos);

    // in function creation, add parentheses
    // need to handle possible inner term. ex: 10.01(x^2+x)^(12)
}

char *format_coefficient(char *expr, int *coeff_len_store, 
                         int *decimal_pos_store) {
    
    // max length coef. we'll hold is 256 chars, otherwise things will break
    char *coefficient = malloc(256); 
    char *new_coefficient = malloc(257);
    new_coefficient[0] = '\0'; // make sure str is null-terminated if empty

    // get details about the coefficient
    int coeff_len = 0, decimal_pos = -1;
    for (int i = 0; expr[i] != 'x' && expr[i] != '\0' 
                    && (i == 0 || expr[i] != '('); i++) {

        if (expr[i] == '(' || expr[i] == ')') continue;

        // handle decimal point for floats
        if (expr[i] == '.') decimal_pos = i;
        else ++coeff_len;
    }

    // lets shift our expr over by one if the coefficient is surrounded by
    // parenthese. this will make our str copies much simpler
    int shifted = 0;
    if (expr[0] == '('){ expr++; shifted++; }

    // if we need to, change the format of the coefficient. if we have a 
    // string like ".001" or "100.", lets add that leading/trailing zero to
    // maintain a consistent formatting.
    if (decimal_pos != -1){

        // copy over the coefficient to a new string so we can use strcat
        // with it for easy string manipulation
        strncpy(coefficient, expr, coeff_len + 1);
        coefficient[coeff_len + 1] = '\0';
        
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

        // case where decimal is already in correct format
        else strcpy(new_coefficient, coefficient);
    }

    // otherwise, we should just copy the entire coefficient from our 
    // expression into our new_coefficient variable to be converted to a float
    else {
        strncpy(new_coefficient, expr, coeff_len);
        new_coefficient[coeff_len] = '\0';
    }

    // if we shifted our expression, lets move it back for our next if
    // statement
    if (shifted) expr--;

    // set additional return types and free some mem
    if (expr[0] == '(') coeff_len += 2;
    if (coeff_len_store) *coeff_len_store = coeff_len;
    if (decimal_pos_store) *decimal_pos_store = decimal_pos;
    free(coefficient);

    return new_coefficient;
}

char *get_inner(char *expr, int *inner_len_store, int *has_variable_store, 
                int *is_complex_store) {

    char *inner = malloc(256);

    // par_cnt, short for 'parentheses_count', will sort of act like a stack
    // for tracking correct order of parentheses. it will shift 'left' (-1) if
    // '(', and 'right' (+1) if ')'.
    int inner_len = 0, par_cnt = 0, shifted = 0, has_var = 0, is_complex = 0;
    for (int i = 0; expr[i] != '^' && expr[i] != '\0' 
                    && !(par_cnt == -1 && expr[i] == ')'); i++) {

        // shift parentheses count
        if (expr[i] == '(') {
            par_cnt--;
            if (!i) continue; // dont want to store the first parentheses
        }
        else if (expr[i] == ')') par_cnt++;

        if (expr[i] == 'x') has_var++;
        else if ( (int) expr[i] < 48 ) is_complex++;
        
        inner_len++;
    }
    
    // shift our expression if needed before the copy
    if (expr[0] == '(') {expr++; shifted++;}
    strncpy(inner, expr, inner_len);
    inner[inner_len] = '\0';
    
    // store has_var and is_complex
    if (has_variable_store) *has_variable_store = has_var;
    if (is_complex_store) *is_complex_store = is_complex;

    // store the length of the inner term
    if (shifted) inner_len += 2;
    if (inner_len_store) *inner_len_store = inner_len;
    
    return inner;
}

char *get_power(char *expr){
    
    char *power = malloc(256);
    printf("expr: %s\n", expr);
    if (*expr == '\0') return "";

    return NULL;
}