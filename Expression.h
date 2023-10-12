#pragma once

#include <string>
#include <stack>
#include <functional>
#include <stdexcept>
#include "Funcs.h"

class Expression {
private:
	static char const DELIMITER = ';';
	std::string tokenized = "";
	bool rearrangeParentheses(std::stack<std::string>& tokens, std::string& output, Funcs& funcs);
	void rearrangeOperators(std::stack<std::string>& tokens, std::string& current, std::string& output, Funcs& funcs);
	void readWhile(std::string const& input, int& start, std::string& current, std::function<bool(char)> predicate);
	void readWholeNumber(std::string const& input, int& start, std::string& current);
	void readWholeWord(std::string const& input, int& start, std::string& current);
	bool tokensCleanup(std::stack<std::string> tokens, std::string& output);
public:
	void separateTokens(std::string const& input, Funcs& funcs);
	void printResult(Funcs& funcs);
};