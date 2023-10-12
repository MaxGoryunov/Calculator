#pragma once

#include <string>
#include <stack>
#include <functional>
#include <stdexcept>
#include "Funcs.h"

using std::string;
using std::stack;
using std::function;

class Expression {
private:
	static char const DELIMITER = ';';
	string tokenized = "";
	bool rearrangeParentheses(stack<string>& tokens, string& output, Funcs& funcs);
	void rearrangeOperators(stack<string>& tokens, string& current, string& output, Funcs& funcs);
	void readWhile(string const& input, int& start, string& current, function<bool(char)> predicate);
	void readWholeNumber(string const& input, int& start, string& current);
	void readWholeWord(string const& input, int& start, string& current);
	bool tokensCleanup(stack<string> tokens, string& output);
public:
	void separateTokens(string const& input, Funcs& funcs);
	void printResult(Funcs& funcs);
};