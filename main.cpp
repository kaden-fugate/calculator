#include <unordered_map>

#include "lexer.hpp"

using std::unordered_map;

string get_input() {

    string input = "";
    std::cout << "> ";
    getline(std::cin, input);

    return input;

}

int main() {

    // need to do a few things in main:
    //
    // 1. we need to allocate some memory for variables that the user can
    //    declare
    // 2. prompt user
    // 3. need to get prompt from user
    // 4. 
    //      a. if declaring variable, we can add it to the variable list
    //      b. if doing operation, compute operation and store in ans variable
    //         in variable list
    //      c. if calling function, output result of function to terminal
    //      d. if 'exit', free memory, exit program
    //      e. if existing variable name, print "<var_name> = <var_val>"
    //      f. if 'var_list' is user input, print all variables and their 
    //         values
    //         - note: matrices/vectors will simply print their dimensions
    //      f. if error, catch error and output error message to terminal

    // we'll need to declare the memory for variables here but we'll need to
    // further examine how we can store all types of user variables. first, 
    // lets examine what kind of variables we'll need to store:
    //
    // 1. default data types like int, float, (maybe) string, etc.
    // 2. 2d vector of anything in 1 (the above line).
    //
    // to be able to efficiently store all of these things, we'll need to do
    // two things: 
    // 
    // 1. make a hash map that will store variables and their name as a
    //    key-value pair
    // 2. define some kind of structure where we can define a variable
    //      a. store primative data types (i.e. int, float, etc.) in a derived
    //         class
    //      b. store matrices/vectors in another derived class
    //      - note: we'll type cast these to a pointer of the parent class so
    //              that we can store both in the map

    string input = "";
    vector<Token> tokens;
    vector<string> keywords = {"let"};
    vector<string> funcs = {"func"};

    // do prompt loop while user input is not 'exit'
    do {

        // user input
        input = get_input();
        std::cout << "input: " << input << std::endl;

        // tokenize user input
        Lexer lexer(input, keywords, funcs);
        tokens = lexer.tokenize();
        lexer.print_tokens();

    } while(input != "exit");

    // free mem

    return 0;
}