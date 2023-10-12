#include "Tokens.h"

using std::string;
using std::vector;
using std::runtime_error;

bool Tokens::rearrangeParentheses(Funcs& funcs, vector<string>& tokens) {
    string top;
    while (!this->tokens.empty()) {
        top = this->tokens.top();
        this->tokens.pop();
        if (top == "(") {
            break;
        }
        else {
            tokens.push_back(top);
        }
    }
    if (this->tokens.empty() && top != "(") {
        throw runtime_error("Number of left and right parentheses does not match");
    }
    if (!this->tokens.empty()) {
        top = this->tokens.top();
        if (funcs.isUnary(top)) {
            tokens.push_back(top);
            this->tokens.pop();
        }
    }
    return true;
}

void Tokens::rearrangeOperators(string& current, Funcs& funcs, vector<string>& tokens) {
    while (!this->tokens.empty()) {
        string top = this->tokens.top();
        if (funcs.isArithmetic(top) && ((funcs.associativity(current) && (funcs.precedence(current) <= funcs.precedence(top)))
            || (!funcs.associativity(current) && (funcs.precedence(current) < funcs.precedence(top))))) {
            tokens.push_back(top);
            this->tokens.pop();
        }
        else {
            break;
        }
    }
    this->tokens.push(current);
}


void Tokens::cleanup(vector<string>& tokens) {
    while (!this->tokens.empty()) {
        string top = this->tokens.top();
        this->tokens.pop();
        if (top == "(" || top == ")") {
            throw runtime_error("Error: parentheses mismatched");
        }
        tokens.push_back(top);
    }
}