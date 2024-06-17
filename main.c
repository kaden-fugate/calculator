#include "function.h"
#include "term.h"

int main(){

    char expression[] = "3x^(2x)-(2x+1*x^2/3x^3)";
    struct function *func = create_function();

    func = func_from_str(expression);
    term_from_str("1001x^1");
    term_from_str(".1001x^x");
    term_from_str("1001.x^3");
    term_from_str("x^4");
    
    return 0;
}