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

struct Or {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a || b; }
};

struct And {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a && b; }
};

struct Less {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a < b; }
};

struct Greater {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a > b; }
};

struct Leq {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a <= b; }
};

struct Geq {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a >= b; }
};

struct Eq {
    template <typename T1, typename T2>
    static Data apply(T1 a, T2 b) { return a == b; }
};

struct Bool {
    template <typename T>
    static bool apply(T a) { return (bool) a; }
};

template <typename Op>
struct OperatorVisitor {

    template <typename T>
    Data operator()(T a) const {
        return Op::apply(a);
    }

    template <typename T1, typename T2>
    Data operator()(T1 a, T2 b) const {
        return Op::apply(a, b);
    }

};

#endif