#pragma once

#include <string>
#include <stack>
#include <functional>
#include <stdexcept>
#include "Funcs.h"

class Expression {
private:
	std::vector<std::string> tokens;
	void readWhile(std::string const& input, int& start, std::string& current, std::function<bool(char)> predicate);
	void readWholeNumber(std::string const& input, int& start, std::string& current);
	void readWholeWord(std::string const& input, int& start, std::string& current);
public:
	void separateTokens(std::string const& input, Funcs& funcs);
	void printResult(Funcs& funcs);
};