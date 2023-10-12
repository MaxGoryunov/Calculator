#include "App.h"

using std::string;

void App::calculate(string& input) {
	this->expression.separateTokens(input, this->funcs);
	this->expression.printResult(this->funcs);
}