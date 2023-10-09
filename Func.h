#pragma once

#include <iostream>
#include <string>
#include <functional>
#include "Precedence.h"
#include "Associativity.h"

using std::string;
using std::function;

class Func {
private:
	string& name;
	Precedence preced;
	Associativity assoc;
	int arity;
	function<double(double, double)> func;
public:
	Func(string& name, Precedence preced, Associativity assoc, int arity) : 
		name(name), preced(preced), assoc(assoc), arity(arity) {}

	string& Name() { return this->name; }

	Precedence Precedence() { return this->preced; }
	
	Associativity Associativity() { return this->assoc; }
	
	int Arity() { return this->arity; }
	
	double apply(double left, double right) { return this->func(left, right); }

	Func(Func const& other) = default;
	Func(Func&& other) = default;
	Func& operator = (Func const& other) = default;
	Func& operator = (Func&& other) = default;
	~Func() = default;

};