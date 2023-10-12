#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <Windows.h>
#include "Precedence.h"
#include "Associativity.h"

class Func {
private:
	std::string name;
	Precedence preced;
	Associativity assoc;
	int arity;
	std::function<double(double, double)> func;
public:
	Func() = default;
	Func(
		std::string name,
		Precedence preced,
		Associativity assoc,
		int arity,
		std::function<double(double, double)> func
	) : name(name), preced(preced), assoc(assoc), arity(arity), func(func) {}

	static Func fromLibrary(HINSTANCE const& library);

	std::string& Name() { return this->name; }

	Precedence precedence() { return this->preced; }
	
	Associativity associativity() { return this->assoc; }
	
	int Arity() { return this->arity; }
	
	double apply(double left, double right) { return this->func(left, right); }

	Func(Func const& other) = default;
	Func(Func&& other) = default;
	Func& operator = (Func const& other) = default;
	Func& operator = (Func&& other) = default;
	~Func() = default;

};