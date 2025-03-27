#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

#include <fstream>
using std::ifstream, std::stringstream;

vector<Token> tokens;
vector<string> keywords = {"let"};
vector<string> funcs = {"func"};
vector<string> bools = {"&", "|", "!"};
Node *root = nullptr;
vector<Node*> exprs;

string get_input() {

    string input = "";
    std::cout << "> ";
    getline(std::cin, input);

    return input;

}

void parse_expression(string input, unordered_map<string, Data> *vars, 
    bool debug) {

    // tokenize user input
    Lexer lexer(input, keywords, funcs, bools);
    tokens = lexer.tokenize();

    // parse tokenized input into abstract syntax tree
    Parser parser(tokens);
    root = parser.statement();

    Interpreter interpreter(root, vars);
    Token res = interpreter.interpret(root);

    if (debug){
        // debug statements
        std::cout << "\nTOKENS:\t";
        lexer.print_tokens();
        std::cout << "\n";

        std::cout << "\nTREE:\t";
        parser.print_tree(root);
        std::cout << "\n";

        std::cout << "\nMAP:\t";
        interpreter.print_map();

        std::cout << "\nans:\t";
        res.print();
        std::cout << "\n";
    }

}

void parse_file(ifstream &file, unordered_map<string, Data> *vars, bool debug){
    stringstream buffer;
    buffer << file.rdbuf();

    string content = buffer.str();
    
    // tokenize user input
    Lexer lexer(content, keywords, funcs, bools);
    tokens = lexer.tokenize();

    if (debug) {
        std::cout << "\nTOKENS:\t";
        lexer.print_tokens();
        std::cout << "\n";
    }

    // parse tokenized input into abstract syntax tree
    Parser parser(tokens);
    exprs = parser.parse_program();

    Token res;
    for (unsigned long int i = 0; i < exprs.size(); i++) {
        Interpreter interpreter(exprs[i], vars);
        res = interpreter.interpret(exprs[i]);

        if (debug) {
            std::cout << "\nTREE:\t";
            parser.print_tree(exprs[i]);
            std::cout << "\n";
    
            std::cout << "\nMAP:\t";
            interpreter.print_map();
    
            std::cout << "\nans:\t";
            res.print();
            std::cout << "\n";
        }

    }

}

int main(int argc, char *argv[]) {

    string input = "";
    std::unordered_map<string, Data> vars = {};

    // if user passes a file to be parsed
    if (argc > 1) {
        ifstream file(argv[1]);
        parse_file(file, &vars, true);
    }

    // if user in command-line mode
    else {

        // do prompt loop while user input is not 'exit'
        do {

            // user input then parse expression
            input = get_input();
            parse_expression(input, &vars, true);

        } while(input != "exit");

    }

    

    // free mem
    // wow i really need to work on freeing the memory soon

    return 0;
}