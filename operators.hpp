#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <variant>

using Data = std::variant<int, long double>;

struct Add {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a + b; }
};

struct Sub {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a - b; }
};

struct Mult {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a * b; }
};

struct Div {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a / b; }
};

template <typename Op>
struct OperatorVisitor {

    template <typename T1, typename T2>
    Data operator()(T1 a, T2 b) const {
        return Op::apply(a, b);
    }

};

#endif