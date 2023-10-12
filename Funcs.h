#pragma once

#include <string>
#include <map>
#include "Func.h"

class Funcs {
private:
	std::map<std::string, Func> funcs;
public:
	Funcs() {
		this->funcs["+"] = Func("+", SUM, LEFT, 2, [](double l, double r) { return l + r; });
		this->funcs["-"] = Func("-", DIFF, LEFT, 2, [](double l, double r) { return l - r; });
		this->funcs["*"] = Func("*", MUL, LEFT, 2, [](double l, double r) { return l * r; });
		this->funcs["/"] = Func("/", DIV, LEFT, 2, [](double l, double r) { return l / r; });
	}

	void addFunc(std::string name, Func const& func) {
		this->funcs[name] = func;
	}

	Precedence precedence(std::string name);

	Associativity associativity(std::string name);

	int arity(std::string name);

	double call(std::string name, double left, double right);

	bool isUnary(std::string const& name);

	bool isArithmetic(std::string const& name);

	Funcs(Funcs const& other) = default;
	Funcs(Funcs&& other) = default;
	Funcs& operator = (Funcs const& other) = default;
	Funcs& operator = (Funcs&& other) = default;
	~Funcs() = default;
};