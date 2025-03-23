#include "interpreter.hpp"

bool is_leaf(Node *node) {
    if (!node->left && !node->right)
        return true;

    return false;
}

Data Interpreter::compute(Data left, Data right, std::string opr) {

    Data data;

    if (opr == "+")
        data =  std::visit(OperatorVisitor<Add>{}, left, right);
    else if (opr == "-")
        data =  std::visit(OperatorVisitor<Sub>{}, left, right);
    else if (opr == "*")
        data =  std::visit(OperatorVisitor<Mult>{}, left, right);
    else if (opr == "/")
        data =  std::visit(OperatorVisitor<Div>{}, left, right);

    return data;
}

Data Interpreter::interpret(Node *root) {

    // edge case, passed root is leaf node
    if ( is_leaf(root) )
        return root->val.get_val();

    Data left;
    // case where left node is not leaf
    if ( !is_leaf(root->left) )
        left = interpret(root->left);

    // otherwise, simply set left to left nodes data
    else
        left = root->left->val.get_val();

    // in the future, we can use get_val to retrieve this
    std::string opr = *((std::string *) root->opr.val);

    Data right;
    // case where right node is not leaf
    if ( !is_leaf(root->right) )
        right = interpret(root->right);
    else
        right = root->right->val.get_val();

    // Data add_result = std::visit(OperatorVisitor<Add>{}, value1, value2);
    // std::visit([](auto&& res) { std::cout << "Addition: " << res << "\n"; }, add_result);

    return this->compute(left, right, opr);

}