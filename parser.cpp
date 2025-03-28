#include "parser.hpp"

bool is_block(Token tok) {
    return tok.type == IF || tok.type == ELSE || tok.type == WHILE;
}

bool Parser::valid() {
    return this->in_bounds() && this->cur_tok.to_str() != ";" 
    && this->cur_tok.to_str() != "{";
}

Node *Parser::variable() {
    if (this->cur_tok.type == VAR){
        Node *node = new Node;
        node->val = this->cur_tok;
        return node;
    }

    return nullptr;
}

Node* Parser::factor() {

    // int or long cases
    if (this->cur_tok.type == LONG || this->cur_tok.type == INT)
        return new Node{val: this->cur_tok};

    // expression in parentheses
    else if (this->cur_tok.type == OPR && this->cur_tok.to_str() == "("){

        this->shift();
        return this->bool_expression();

    }

    // token is variable
    else if (this->cur_tok.type == VAR)
        return new Node{val: this->cur_tok};

    // not operator
    else if (this->cur_tok.type == BOOL && this->cur_tok.to_str() == "!") {

        Node *node = new Node{opr: this->cur_tok};
        this->shift();
        node->left = this->factor();

        return node;

    }

    // expression is unary
    else if ((this->cur_tok.type == OPR || this->cur_tok.type == BOOL) && 
            (this->cur_tok.to_str() == "+" || this->cur_tok.to_str() == "-" 
          || this->cur_tok.to_str() == "!")){

        Node *node = new Node{opr: this->cur_tok};
        this->shift();
        node->left = this->factor();
        
        return node;
    }

    return nullptr;
}

Node* Parser::term() { 

    // store factor in root
    Node *root = this->factor();
    this->shift();

    while (this->valid() &&
          (this->cur_tok.to_str() == "*" || this->cur_tok.to_str() == "/")) {

        // shift previous root to left node of new root
        Node *temp = new Node;
        temp->left = root;
        root = temp;
        
        // set operator, shift ahead
        root->opr = cur_tok;
        this->shift();

        // get factor to right of operator
        root->right = this->factor();
        this->shift();

    }
    
    return root; 
}

Node* Parser::expression() {

    // store root as term
    Node *root = this->term();

    while (this->valid() &&
          (this->cur_tok.to_str() == "+" ||
          this->cur_tok.to_str() == "-")) {
        
        // shift previous root to left node of new root
        Node *temp = new Node;
        temp->left = root;
        root = temp;
        
        // set operator, shift ahead
        root->opr = cur_tok;
        this->shift();

        // get term to right of operator
        root->right = this->term();
    }
    
    return root; 

}

Node *Parser::comp_expression() {

    // store root as term
    Node *root = this->expression();

    while (this->valid() && this->cur_tok.type == COMP) {
        
        // shift previous root to left node of new root
        Node *temp = new Node;
        temp->left = root;
        root = temp;
        
        // set operator, shift ahead
        root->opr = cur_tok;
        this->shift();

        // get term to right of operator
        root->right = this->expression();
    }
    
    return root; 

}

Node *Parser::bool_expression() {

    // store root as term
    Node *root = this->comp_expression();

    while (this->valid() && this->cur_tok.type == BOOL) {
        
        // shift previous root to left node of new root
        Node *temp = new Node;
        temp->left = root;
        root = temp;
        
        // set operator, shift ahead
        root->opr = cur_tok;
        this->shift();

        // get term to right of operator
        root->right = this->comp_expression();
    }
    
    return root; 

}

Node *Parser::statement() {

    // check case where 2 or less tokens present
    if (this->tokens.size() - this->idx <= 2)
        return this->bool_expression();

    else if (is_block(this->tokens[this->idx]))
        return this->parse_block();

    // check for declaring variable ("=" as 2nd token)
    else if (this->tokens[this->idx + 1].type == OPR && this->tokens[this->idx + 1].to_str() == "="){

        Node *root = new Node;

        // set left node as given variable
        root->left = this->variable();
        this->shift();

        // set roots opr as equivalence sign
        root->opr = this->cur_tok;
        this->shift();

        // right node is evaluated expression
        root->right = this->bool_expression();

        return root;
    }

    else 
        return this->bool_expression();

    return nullptr;
}

Node *Parser::parse_block() {

    Node *node = new Node{opr: this->cur_tok};

    // first token is IF, ELSE, or WHILE
    this->shift();

    // nodes left data member will represent the condition when node is a
    // block statement (only if block is if or while statement)
    if (node->opr.type == IF || node->opr.type == WHILE)
        node->left = this->bool_expression();

    // need to shift past '{' then append all statements inside of block to
    // nodes block vector. after each push_back call, we will be on a ';' so
    // we'll need to shift again
    this->shift();
    while (this->cur_tok.type != OPR || this->cur_tok.to_str() != "}") {
        node->block.push_back( this->statement() );
        this->shift();
    }

    // shift past '}'. then we can check if there's an 'else' block next.
    // else blocks will be stored in the nodes right data member (only if
    // statements will have this property)
    this->shift();
    if (this->cur_tok.type == ELSE)
        node->right = this->parse_block();
    
    return node;
}

vector<Node*> Parser::parse_program() {

    vector<Node*> res = {};

    while (this->idx < this->tokens.size()) {
        res.push_back( this->statement() );
        this->shift();
    }

    return res;
}

bool Parser::in_bounds() {
    if (this->idx < this->tokens.size())
        return true;

    return false;
}

void Parser::shift() { 
    this->idx++; 

    if (this->idx < this->tokens.size())
        this->cur_tok = this->tokens[this->idx];
}

void Parser::print_tree(Node *node) {

    // block statement
    if (is_block(node->opr)) {

        // stringify block type
        string statement = node->opr.type == IF ? "IF" 
            : (node->opr.type == ELSE ? "ELSE" : "WHILE");

        // print block type and conditional
        std::cout << "\t" << statement;
        if (node->opr.type != ELSE){
            std::cout << " ( ";
            print_tree(node->left);
            std::cout << ")";
        }
        std::cout << " {\n";

        // print statements within curly braces
        for (unsigned long int i = 0; i < node->block.size(); i++){
            std::cout << "\t\t";
            print_tree(node->block[i]);
            std::cout << ";\n";
        }
        std::cout << "\t}\n";

        if (node->opr.type == IF && node->right)
            print_tree(node->right);

        return;
    }

    // base case, node is unary
    if (node->opr.val && node->left && !node->right) {
        std::cout << node->opr.to_str();
        print_tree(node->left);

        return;
    }

    // base case, no more nodes, print out val
    if (!node->left && !node->right) {

        if (node->val.type == OPR || node->val.type == VAR)
            std::cout << node->val.to_str() << " ";
        else if (node->val.type == INT)
            std::cout << node->val.to_int() << " ";
        else if (node->val.type == LONG)
            std::cout << node->val.to_long() << " ";

        return;
    }

    // print left node
    print_tree(node->left);

    // print operator
    std::cout << node->opr.to_str() << " ";

    // right node now
    print_tree(node->right);

}