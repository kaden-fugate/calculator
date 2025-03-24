#include "interpreter.hpp"

bool is_leaf(Node *node) {
    if (!node->left && !node->right)
        return true;

    return false;
}

void *to_void_ptr(Data data) {

    return std::visit([](auto val) -> void* {
        using T = decltype(val);
        T *ptr = new T(val);
        return (void *) (ptr);
    }, data);

}

Type get_type(Data data) {
    if (std::holds_alternative<int>(data))
        return INT;

    else if (std::holds_alternative<long double>(data))
        return LONG;

    return NONE;
}

Token Interpreter::compute(Token left, Token right, string opr) {

    Token token;
    Data data;

    // if assignment, make token with rights data stored (casted to void*) and
    // rights data type stored
    if (opr == "=") {
        
        // will have to convert rights value to int/long before this (if token
        // type not INT or LONG)
        Data val = right.get_val();
        string var_name = left.to_str();
        this->insert(var_name, val);

        // return token that was assigned to left side
        return right;

    }

    // if not assignment, handle values inside of left/right->val instead
    // (these will be int, long, var, etc.)
    Data data_left = left.get_val();
    Data data_right = right.get_val();

    // handle converting non int/long data types to int/long here
    
    if (opr == "+")
        data = std::visit(OperatorVisitor<Add>{}, data_left, data_right);
    else if (opr == "-")
        data = std::visit(OperatorVisitor<Sub>{}, data_left, data_right);
    else if (opr == "*")
        data = std::visit(OperatorVisitor<Mult>{}, data_left, data_right);
    else if (opr == "/")
        data = std::visit(OperatorVisitor<Div>{}, data_left, data_right);

    token.val = to_void_ptr(data);
    token.type = get_type(data);

    return token;
}

Token Interpreter::interpret(Node *root) {

    // edge case, passed root is leaf node
    if ( is_leaf(root) )
        return root->val;

    Token left;
    // case where left node is not leaf
    if ( !is_leaf(root->left) )
        left = interpret(root->left);

    // otherwise, simply set left to left nodes data
    else
        left = root->left->val;

    // in the future, we can use get_val to retrieve this
    string opr = root->opr.to_str();

    Token right;
    // case where right node is not leaf
    if ( !is_leaf(root->right) )
        right = interpret(root->right);
    else
        right = root->right->val;

    return this->compute(left, right, opr);

}

void Interpreter::insert(string key, Data val) {
    (*this->map)[key] = val;
}

bool Interpreter::in_map(string key) {
    return this->map->count(key);
}

void Interpreter::print_map() {
    std::cout << "{ ";
    for (const auto& pair : *this->map) {
        std::cout << pair.first << ": ";
        std::visit([](auto&& res) { std::cout << res << " "; }, pair.second);
    }
    std::cout << "}";
}