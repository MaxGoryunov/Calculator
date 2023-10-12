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

	Precedence precedence(string name);

	Associativity associativity(string name);

	int arity(string name);

	double call(string name, double left, double right);

	bool isUnary(string const& name);

	bool isArithmetic(string const& name);

	Funcs(Funcs const& other) = default;
	Funcs(Funcs&& other) = default;
	Funcs& operator = (Funcs const& other) = default;
	Funcs& operator = (Funcs&& other) = default;
	~Funcs() = default;
};