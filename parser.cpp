#include "parser.hpp"

Node* Parser::factor() {
    Node *node = new Node;
    node->val = this->tokens[this->idx];

    if (node->val.type == LONG || node->val.type == INT)
        return node;

    return nullptr;
}

Node* Parser::term() { 

    // store factor in root
    Node *root = this->factor();
    this->shift();

    // if not operator, error

    while (this->in_bounds() &&
          (this->tokens[this->idx].val == "*" ||
           this->tokens[this->idx].val == "/")) {

        // shift previous root to left node of new root
        Node *temp = new Node;
        temp->left = root;
        root = temp;
        
        // set operator, shift ahead
        root->opr = this->tokens[this->idx];
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

    // if not operator, error

    while (this->in_bounds() &&
          (this->tokens[this->idx].val == "+" ||
           this->tokens[this->idx].val == "-")) {
        
        // shift previous root to left node of new root
        Node *temp = new Node;
        temp->left = root;
        root = temp;
        
        // set operator, shift ahead
        root->opr = this->tokens[this->idx];
        this->shift();

        // get term to right of operator
        root->right = this->term();
    }
    
    return root; 

}

bool Parser::in_bounds() {
    if (this->idx < this->tokens.size())
        return true;

    return false;
}

void Parser::shift() { this->idx++; }

void Parser::print_tree(Node *node) {

    // base case, no more nodes, print out val
    if (!node->left && !node->right) {
        std::cout << node->val.val << " ";
        return;
    }

    // print left node
    print_tree(node->left);

    // print operator
    std::cout << node->opr.val << " ";

    // right node now
    print_tree(node->right);

}