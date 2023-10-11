#pragma once

#include <string>
#include <map>
#include "Func.h"

using std::string;
using std::map;
using std::cout;
using std::endl;

class Funcs {
private:
	map<string, Func> funcs;
public:
	Funcs() {
		this->funcs["+"] = Func("+", SUM, LEFT, 2, [](double l, double r) { return l + r; });
		this->funcs["-"] = Func("-", DIFF, LEFT, 2, [](double l, double r) { return l - r; });
		this->funcs["*"] = Func("*", MUL, LEFT, 2, [](double l, double r) { return l * r; });
		this->funcs["/"] = Func("/", DIV, LEFT, 2, [](double l, double r) { return l / r; });
	}

	void addFunc(string name, Func const& func) {
		this->funcs[name] = func;
	}

	Precedence precedence(string name) {
		if (this->funcs.count(name) == 1) {
			return this->funcs[name].precedence();
		}
		cout << "Precedence of " << name << " is unknown" << endl;
		return NO_PRECEDENCE;
	}

	Associativity associativity(string name) {
		if (this->funcs.count(name) == 1) {
			return this->funcs[name].associativity();
		}
		cout << "Associativity of " << name << " is unknown" << endl;
		return NO_ASSOCIATIVITY;
	}

	int arity(string name) {
		if (this->funcs.count(name) == 1) {
			return this->funcs[name].Arity();
		}
		cout << "Arity of " << name << " is unknown" << endl;
		return 2;
	}

	double call(string name, double left, double right) {
		if (this->funcs.count(name) == 1) {
			return this->funcs[name].apply(left, right);
		}
		cout << "Functionality of " << name << " is unknown" << endl;
		return 0;
	}

	Funcs(Funcs const& other) = default;
	Funcs(Funcs&& other) = default;
	Funcs& operator = (Funcs const& other) = default;
	Funcs& operator = (Funcs&& other) = default;
	~Funcs() = default;
};