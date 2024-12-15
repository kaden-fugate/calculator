#include "main_funcs.hpp"

// simply for debugging purposes. priting the enumarated type will make it 
// easier to understand/debug
void print_type(input_type type) {

    if (type == 0) cout << "type (0): ASSIGN" << endl;
    if (type == 1) cout << "type (1): FUNC" << endl;
    if (type == 2) cout << "type (2): PRINT" << endl;
    if (type == 3) cout << "type (3): VARS" << endl;
    if (type == 4) cout << "type (4): EXIT" << endl;
    if (type == 5) cout << "type (5): NEWLN" << endl;

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
