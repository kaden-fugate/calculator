#include "main_funcs.hpp"

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
// 2. arithmetic such as +, -, *, /, ...
// 3. function call
// 4. print
// 5. print all variables
// 6. exit program
//
// these are all dentoed by a specific input_type enumeration. we can find out
// what kind of operation the user is trying to achieve through iterating
// through the list and checking the following things:
//
// variable assignment:
//      - if '=' in the input, this is assignment
// 
// print_vars:
//      - if input == "var_list", print variable list
// exit:
//      - if input == "exit", this is an exit statement
input_type parse_input(string input) {

    input_type opr = ERR;

    return opr;

}
