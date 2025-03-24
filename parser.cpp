#include "parser.hpp"



Node* Parser::factor() {

    // int or long cases
    if (this->cur_tok.type == LONG || this->cur_tok.type == INT)
        return new Node{val: this->cur_tok};

    // expression in parentheses
    else if (this->cur_tok.type == OPR && this->cur_tok.to_str() == "("){

        this->shift();
        return this->expression();

    }

    // token is variable
    else if (this->cur_tok.type == VAR)
        return new Node{val: this->cur_tok};

    // expression is unary
    else if (this->cur_tok.type == OPR && 
            (this->cur_tok.to_str() == "+" || this->cur_tok.to_str() == "-")){

        Node *node = new Node{opr: this->cur_tok};
        this->shift();
        node->val = this->cur_tok;
        
        return node;
    }

    return nullptr;
}

Node* Parser::term() { 

    // store factor in root
    Node *root = this->factor();
    this->shift();

    while (this->in_bounds() &&
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

    while (this->in_bounds() &&
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

Node *Parser::variable() {
    if (this->cur_tok.type == VAR){
        Node *node = new Node;
        node->val = this->cur_tok;
        return node;
    }

    return nullptr;
}

Node *Parser::statement() {

    // check case where 2 or less tokens present
    if (this->tokens.size() <= 2)
        return this->expression();

    // check for declaring variable ("=" as 2nd token)
    else if (this->tokens[1].type == OPR && this->tokens[1].to_str() == "="){

        Node *root = new Node;

        // set left node as given variable
        root->left = this->variable();
        this->shift();

        // set roots opr as equivalence sign
        root->opr = this->cur_tok;
        this->shift();

        // right node is evaluated expression
        root->right = this->expression();

        return root;
    }

    else 
        return this->expression();

    return nullptr;
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

    // base case, node is unary
    if (node->val.val && node->opr.val) {
        std::cout << node->opr.to_str();

        if (node->val.type == OPR || node->val.type == VAR)
            std::cout << node->val.to_str() << " ";
        else if (node->val.type == INT)
            std::cout << node->val.to_int() << " ";
        else if (node->val.type == LONG)
            std::cout << node->val.to_long() << " ";

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