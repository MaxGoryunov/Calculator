#pragma once

#include "Expression.h"
#include "DllCatalogue.h"
#include "Funcs.h"

class App {
private:
	Expression& expression;
	Funcs& funcs;
public:
	App(Expression& expression, DllCatalogue& libraries, Funcs& funcs) : 
		expression(expression), funcs(funcs) {
		libraries.loadFuncsFromDll(this->funcs);
	}

	void calculate(string& input);

	App() = default;
	App(App const& other) = default;
	App(App&& other) = default;
	App& operator = (App const& other) = default;
	App& operator = (App&& other) = default;
	~App() = default;
};