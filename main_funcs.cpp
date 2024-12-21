#include "main_funcs.hpp"

// simply for debugging purposes. priting the enumarated type will make it 
// easier to understand/debug
void print_input_type(input_type type) {

    if (type == 0) cout << "input_type (0): ASSIGN" << endl;
    if (type == 1) cout << "input_type (1): FUNC" << endl;
    if (type == 2) cout << "input_type (2): PRINT" << endl;
    if (type == 3) cout << "input_type (3): VARS" << endl;
    if (type == 4) cout << "input_type (4): EXIT" << endl;
    if (type == 5) cout << "input_type (5): NEWLN" << endl;

}

// simply for debugging purposes. priting the enumarated type will make it 
// easier to understand/debug
void print_term_type(term_type type) {

    if (type == 0) cout << "term_type (0): INT" << endl;
    if (type == 1) cout << "term_type (1): FLOAT" << endl;
    if (type == 2) cout << "term_type (2): MATRIX" << endl;
    if (type == 3) cout << "term_type (3): PARNTH" << endl;
    if (type == 4) cout << "term_type (4): VAR" << endl;
    if (type == 5) cout << "term_type (5): FUNC_CALL" << endl;

}

// get input and remove whitespace. no newline character will be at end of
// resulting string.
string get_input() {

    string input = "", res = "";
    cout << "> ";
    getline(cin, input);

    // remove all whitespace from input
    for (int i = 0; i < (int) input.length(); i++) 

        if (input[i] != ' ')
            res += input[i];

    return res;

}

// in this function we will need to handle figuring out what kind of operation
// the user has input. here are the possible operations:
//
// 1. variable assignment/declaration
// 2. function call
// 3. print
// 4. print all variables
// 5. exit program
// 6. newline
//
// these are all dentoed by a specific input_type enumeration. we can find out
// what kind of operation the user is trying to achieve through iterating
// through the list and checking the following things:
//
// variable assignment:
//      - if '=' in the input, this is assignment
// function call:
//      - if "(" is found, this is a function call
// print_vars:
//      - if input == "var_list", print variable list
// exit:
//      - if input == "exit", this is an exit statement
// newline: 
//      - if input = "", user didnt enter anything and we should just skip to
//        the next input
// print:
//      - if none of the above is true, this is something to print out to the
//        terminal.
//      - additionally, we should check for a '[' and if true, it is print.
//        this is because the user can do something like [func(); 1; func()]
//        where func() returns a value and we should print this matrix
//      - we should be able to handle printing existing variables, arithmetic,
//        primative variables, and matrices
input_type parse_input(string input) {

    input_type opr = PRINT;

    if (input == "exit") return EXIT;
    else if (input == "var_list") return VARS;
    else if (input == "") return NEWLN;

    for (int i = 0; i < (int) input.length(); i++) {

        if (input[i] == '=') return ASSIGN;
        else if (input[i] == '(') return FUNC;
        else if (input[i] == '[') return PRINT;

    }

    return opr;

}

// in this function we'll need to handle variable assignment. to do this, this
// function will need to return the name of the variable being assigned to and
// the value being assigned to it. to get these values, we'll need to do the
// following:
//
// 1. variable name:
//      - this should be the easy part, we can simply look at any text before
//        the '=' and call this the variable name.
//      - we'll need to put a few constraints on the variable name as it cannot
//        start with a number, cannot be called 'exit' or 'var_list', and there
//        are some special characters that it should not be allowed to contain
// 2. value:
//      - if the right side of the equation is an int or float, that's great,
//        we can simply return it.
//      - if the right side is a matrix, build that matrix and set it as the
//        value. 
//      - if the right side is a function, simply call it and it's return value
//        will be the value that we return
//      - if the right side contains arithmetic, we'll need to compute it and
//        return the value
void assign(string input) {

    term_type type = INT;
    string term_name = "";
    string opr_name = "";

    // variable name, will throw errors if invalid
    string var_name = get_var_name(input);
    input = input.substr(var_name.length() + 1);

    // value
    // this will be a bit more difficult than how it's described above. this is
    // because of the fact that the right side of the equation can look like:
    //
    // expression --> (x * f(y) + 1.2 * 1) / 3 * 2
    //
    // with this, we'll need to do something along the lines of the following:
    // 
    // 1. iterate through the right-side of the equation doing 4 things:
    //      a. if variable is referenced, fetch value, throw error if does not
    //         exist.
    //      b. if function is referenced, get output, throw error if does not
    //         exist or if input is wrong in some sort of way
    //      c. if invalid character is referenced, throw error
    //      d. if a or b, we will replace the variable/function name with its
    //         outputted value.
    // 2. use PEMDAS to move through the equation in the correct order. we'll
    //    use a stack for this.
    // 3. make a variable pointer initialized to the correct output value.
    //    we'll need to figure out what type the variable is so we can
    //    initialize it (because we're using templates). for now, we'll only
    //    support storing int's and doubles as these are really the only things
    //    you can do arithmetic with. in the future it would be nice to store
    //    variables as strings as well (though this will be more applicable if
    //    plotting is ever added).
    //
    //    here's how we'll determine how we should return as our value:
    //     
    //    a. if []'s, we'll start processing it as a matrix where values will
    //       be delimited by " "'s (space characters) and new rows will be 
    //       delimited by ";"'s (i.e. matlab style, this programs inspiration).
    //       of course, some further checks will need to be made on the 
    //       dimensions of the matrix. for now, block matrices will not be
    //       implemented.
    //
    //       we can use the process in (b.) directly below this to parse each
    //       individual element in the matrix.
    //    b. if processing an expression (something like the expression given
    //       above at the start of this comment block), we know two things:
    //          i.   if there is a double in the expression, then the output 
    //               will also be a double. 
    //          ii.  if there are only integers, then the output will only be 
    //               a double if the expression is divided by a non-divisor of
    //               the numerator.
    //          iii. else, output should be stored as an int for precision that
    //               integer arithemetic offers
    
    // get all the terms as individual strings
    while (input.length() > 0) {

        // cut out term from input string
        term_name = get_term(input, &type);
        input = input.substr(term_name.length());

        // get next operator
        if (input.length()) {
            opr_name = get_operator(input);
            input = input.substr(opr_name.length());
        }
        
    }

}
// this function simply checks that the variable name given by the user is 
// valid. if valid, it will return the variable name as a string. if not, it
// will throw an error to be caught in main.
string get_var_name(string input) {

    string var_name = "", invalid_chars = "`~-=+{}[]|\\';:,<.>/?!@#$%^&*()";

    // get the users variable name
    for (int i = 0; i < (int) input.length() && input[i] != '='; i++)
        var_name += input[i];

    // do checks on the variable name
    if (var_name == "exit") 
        throw runtime_error("variable name cannot be 'exit'.");
    
    else if (var_name == "var_list") 
        throw runtime_error("variable name cannot be 'var_list'.");

    else if ((int) var_name[0] >= 48 && (int) var_name[0] <= 57) 
        throw runtime_error("first character of variable name cannot be" 
                            " numeric value.");

    else if (var_name.find_first_of(invalid_chars) != string::npos) {
        int idx = var_name.find_first_of(invalid_chars);
        string err_msg = (string) "variable name cannot contain " 
                        + var_name[idx] + (string) "'s.";
        throw runtime_error(err_msg);
    }

    return var_name;

}

// this function will get the next term in an expression (whether it be an int,
// float, matrix, variable name, or function call). once we can get this 
// string, it'll make it easier to calculate the handle the individual terms.
//
// this function will probably need to return 2 things:
//
// 1. the string containing the individual term
// 2. some enum that tells us what the term is (i.e. func, primative, matrix,
//    etc.) so that we won't need a function to re-check the term
//
// test cases:
// 
// 1. valid ints: 1, 56, 196, 1234, ...
// 2. invalid ints: any int where x > abs(9223372036854775807) - these will not
//    be handled at this point. instead, the user will simply find their
//    output to be incredibly inaccurate.
// 3. valid floats: 1.0, 1.00000, ... - i believe that as the value in the
//    mantissa of a floating point number increases, it loses decimal point
//    accuracy
// 4. valid variables: a, a_1, norms, etc. - as long as these names reference
//    an existing variable in our map.
// 5. valid functions: func_1(), func_2(a), func_3(a, b), etc. - as long as
//    all referencing functions and variable names exist
//
// we will be given expressions such as the following:
//
// expression: 3 * x + 10
// returned term: 3
//
// expression: (3 * x) + 10
// returned term: (3 * x)
// 
// expression: func(1) * x + 10
// returned term: func(1)
//
// expression: x * 3 + 10
// returned term: x
//
// expression: [1.23 func(1) 0.01] * [1 ; 2; 3]
// returned term: [1.23 func(1) 0.01]
//
// expression: 3a12
// returned term: 3a12
string get_term(string input, term_type *type_ptr) {

    // there will be 2 different cases where we can encounter parentheses,
    // either when a function is being called or when the next term to
    // evaluate in the expression is contained within parentheses.
    //
    // to keep track of this, we will have two variables:
    //
    // 1. seen_var_name - boolean to keep track of if we've seen letters
    // 2. par_count - int value to keep track of opening and closing parenthese
    //    count so we can correctly return expressions contained within ()'s
    bool seen_var_name = false;
    int par_count = 0;

    // we'll also need a boolean value to keep track of if what we're looking
    // at is a number. this will be set to true if the term starts with a
    // number:
    bool is_num = false;

    // finally we need to account for the matrices. this will be updated when
    // the term starts with a square opening bracket. we'll use brack_count
    // similar to par_count but for now, we are not supporting block matrices
    // so this will throw an error if it encounters two consecutive square
    // opening brackets:
    bool is_matrix = false;
    int brack_count = 0;

    term_type type = VAR;
    string term = "";

    // numeric term
    if ((int) input[0] >= '0' && (int) input[0] <= '9') {
        type = INT;
        for (int i = 0; i < (int) input.length(); i++) {
            
            // stop processing string when reaching an ending char
            if (input[i] == ' ' || input[i] == '*' || input[i] == '/'
                || input[i] == '+' || input[i] == '-') break;

            term += input[i];

            // check if float
            if (input[i] == '.')
                type = FLOAT;

        }   

    }

    // matrix term
    else if (input[0] == '[') {
        type = MATRIX;
        term = get_mat_string(input);

    }

    // term stored in parentheses
    else if (input[0] == '(') {
        type = PARNTH;
        term = get_parnth_str(input);

    }

    // function or variable term
    else {
        type = VAR;        
    }

    if (type_ptr) *type_ptr = type;

    return term;
}

string get_parnth_str(string input) {

    string term = "";
    int par_count = 0;

    // iterate thru term, stop when term complete (using par_count)
    for (int i = 0; i < (int) input.length(); i++) {
        
        if (input[i] == '(') 
            par_count--;

        else if (input[i] == ')') 
            par_count++;
        
        term += input[i];
        if (!par_count) break;

    }

    return term;
}

string get_mat_string(string input) {

    string term = "";
    int brack_count = 0;

    // iterate thru matrix, stop when matrix complete (using brack_count)
    for (int i = 0; i < (int) input.length(); i++) {
        
        if (input[i] == '[') {
            if (i) runtime_error("block matricies not currently"
                                 " supported");
            brack_count--;
        }

        else if (input[i] == ']') 
            brack_count++;
        
        term += input[i];
        if (!brack_count) break;
    }

    return term;

}

string get_operator(string input) {

    string res = "";

    // . operators for elementwise matrix operations
    if (input[0] == '.') {
        res += '.';
        input = input.substr(1);
    }

    res += input[0];

    return res;

}