#pragma once

#include <stack>
#include <string>
#include <stdexcept>
#include "Funcs.h"

class Tokens {
private:
	std::stack<std::string> tokens;
public:
	void push(std::string const& token) {
		this->tokens.push(token);
	}

	std::string& top() {
		return this->tokens.top();
	}

	void pop() {
		return this->tokens.pop();
	}

	bool rearrangeParentheses(Funcs& funcs, std::vector<std::string>& tokens);

	void rearrangeOperators(std::string& current, Funcs& funcs, std::vector<std::string>& tokens);


	void cleanup(std::vector<std::string>& tokens);
};