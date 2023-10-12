#include "Funcs.h"

#include <stdexcept>

using std::cerr;
using std::runtime_error;

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

Precedence Funcs::precedence(string name) {
	if (this->funcs.count(name) == 1) {
		return this->funcs[name].precedence();
	}
	throw runtime_error("Precedence of " + name + " is unknown");
}

Associativity Funcs::associativity(string name) {
	if (this->funcs.count(name) == 1) {
		return this->funcs[name].associativity();
	}
	throw runtime_error("Associativity of " + name + " is unknown");
}

int Funcs::arity(string name) {
	if (this->funcs.count(name) == 1) {
		return this->funcs[name].Arity();
	}
	throw runtime_error("Arity of " + name + " is unknown");
}

double Funcs::call(string name, double left, double right) {
	if (this->funcs.count(name) == 1) {
		return this->funcs[name].apply(left, right);
	}
	throw runtime_error("Functionality of " + name + " is unknown");
}