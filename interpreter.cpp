#include "interpreter.hpp"

bool is_leaf(Node *node) {
    if (!node->left && !node->right)
        return true;

    return false;
}

void *to_void_ptr(Data data) {

    // convert to whatever T is and allocate new memory with val stored
    // inside. this is so that our value is not subject to the garbage 
    // collector when it goes out of scope. cast this new pointer into 
    // void*.
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

Data call_opr(Data data1, Data data2, string opr) {

    Data data;

    if (opr == "+")
        data = std::visit(OperatorVisitor<Add>{}, data1, data2);
    else if (opr == "-")
        data = std::visit(OperatorVisitor<Sub>{}, data1, data2);
    else if (opr == "*")
        data = std::visit(OperatorVisitor<Mult>{}, data1, data2);
    else if (opr == "/")
        data = std::visit(OperatorVisitor<Div>{}, data1, data2);

    return data;

}

Token Interpreter::compute(Token left, Token right, string opr) {

    Data data;

    // if assignment, make token with rights data stored (casted to void*) and
    // rights data type stored
    if (opr == "=") {
        
        // will have to convert rights value to int/long before this (if token
        // type not INT or LONG)

        // get key (variable to assign to) from token and data (computed RHS)
        string key = left.to_str();
        data = this->get_data(right);

        // insert into map
        this->insert(key, data);

        // return token that was assigned to left side
        return right;

    }

    Token token;

    // if not assignment, handle values inside of left/right->val instead
    // (these will be int, long, var, etc.)
    Data data_left = this->get_data(left);
    Data data_right = this->get_data(right);

    // handle converting non int/long data types to int/long here
    
    data = call_opr(data_left, data_right, opr);

    token.val = to_void_ptr(data);
    token.type = get_type(data);

    return token;
}

Token Interpreter::interpret(Node *root) {

    Token left;
    Token right;

    // edge case, passed root is leaf node
    if ( is_leaf(root) )
        return root->val;

    // case where left node is not leaf
    if ( !is_leaf(root->left) )
        left = interpret(root->left);
    else
        left = root->left->val;

    // in the future, we can use get_val to retrieve this
    string opr = root->opr.to_str();

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

Data Interpreter::read(string key) {

    if (this->in_map(key)) 
        return this->map->find(key)->second;

    else {
        // TODO: make this throw an actual error
        std::cout << key << " does not exist!\n";
        exit(1);
    }
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

Data Interpreter::get_data(Token tok) {
    // if int or long, just return val
    if (tok.type == INT || tok.type == LONG)
        return tok.get_val();

    // if var
    else if (tok.type == VAR)
        return this->read(tok.to_str());

    std::cout << "Token type " << tok.type << " not implemented!\n";
    exit(1);
}