#include "Funcs.h"

bool Funcs::isUnary(string const& name) {
    if (name == "(" || name == ")") {
        return false;
    }
    if (this->associativity(name) == LEFT && this->arity(name) == 1) {
        return true;
    }
    return false;
}

bool Funcs::isArithmetic(string const& name) {
    if (name == "(" || name == ")") {
        return false;
    }
    Associativity assoc = this->associativity(name);
    int arity = this->arity(name);
    if ((assoc == LEFT && arity == 2) || (assoc == RIGHT && arity == 1)) {
        return true;
    }
    return false;
}