#include <iostream>
#include <functional>
#include "Expression.h"
#include "StringUtils.h"

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::stod;
using std::to_string;
using std::runtime_error;
using SU = StringUtils;

bool Expression::rearrangeParentheses(stack<string>& tokens, string& output, Funcs& funcs) {
    string top;
    while (!tokens.empty()) {
        top = tokens.top();
        tokens.pop();
        if (top == "(") {
            break;
        }
        else {
            output += top + DELIMITER;
        }
    }
    if (tokens.empty() && top != "(") {
        throw runtime_error("Number of left and right parentheses does not match");
    }
    if (!tokens.empty()) {
        top = tokens.top();
        if (funcs.isUnary(top)) {
            output += top + DELIMITER;
            tokens.pop();
        }
    }
    return true;
}

void Expression::rearrangeOperators(stack<string>& tokens, string& current, string& output, Funcs& funcs) {
    while (!tokens.empty()) {
        string top = tokens.top();
        if (funcs.isArithmetic(top) && ((funcs.associativity(current) && (funcs.precedence(current) <= funcs.precedence(top)))
            || (!funcs.associativity(current) && (funcs.precedence(current) < funcs.precedence(top))))) {
            output += top + DELIMITER;
            tokens.pop();
        }
        else {
            break;
        }
    }
    tokens.push(current);
}

void Expression::readWhile(string const& input, int& start, string& current, function<bool(char)> predicate) {
    int length = input.length();
    int i = 0;
    while (i < length) {
        i = start + 1;
        char tok = input[i];
        if (predicate(tok)) {
            current += tok;
        }
        else {
            break;
        }
        start++;
    }
}

void Expression::readWholeNumber(string const& input, int& start, string& current) {
    return readWhile(input, start, current, [](char tok) { return SU::isIdent(string{ tok }) || tok == '.'; });
}

void Expression::readWholeWord(string const& input, int& start, string& current) {
    return readWhile(input, start, current, [](char tok) { return SU::isLetter(string{ tok }); });
}

bool Expression::tokensCleanup(stack<string> tokens, string& output) {
    while (!tokens.empty()) {
        string top = tokens.top();
        tokens.pop();
        if (top == "(" || top == ")") {
            throw runtime_error("Error: parentheses mismatched");
        }
        output += top + DELIMITER;
    }
    return true;
}

void Expression::separateTokens(string const& input, Funcs& funcs) {
    stack<string> tokens;
    //Funcs funcs;
    int length = input.length();
    string output = "";
    for (int i = 0; i < length; ++i) {
        char tok = input[i];
        string current{ tok };
        if (current != " ") {
            if (SU::isIdent(string{ tok })) {
                readWholeNumber(input, i, current);
                output += current + DELIMITER;
            }
            else if (SU::isLetter(string{ tok })) {
                readWholeWord(input, i, current);
                if (funcs.isUnary(current)) {
                    tokens.push(current);
                }
            }
            else if (funcs.isArithmetic(current)) {
                rearrangeOperators(tokens, current, output, funcs);
            }
            else if (current == "(") {
                tokens.push(current);
            }
            else if (current == ")") {
                if (!rearrangeParentheses(tokens, output, funcs)) {
                    return;
                }
            }
            else
            {
                cout << "Token " << current << " is an unknown token" << endl;
                return;
            }
        }
    }
    tokensCleanup(tokens, output);
    cout << output << endl;
    this->tokenized = output;
}

void Expression::printResult(Funcs& funcs) {
    string input = this->tokenized;
    int length = input.length();
    //Funcs funcs;
    vector<string> labels(length);
    vector<double> values(length);
    int last = 0;
    int iteration = 0;
    for (int i = 0; i < length; ++i) {
        string current{ input[i] };
        if (SU::isIdent(current)) {
            readWholeNumber(input, i, current);
            ++i;
            labels[last] = current;
            values[last] = stod(current);
            ++last;
        }
        else {
            if (SU::isLetter(current)) {
                readWholeWord(input, i, current);
                labels[last] = current;
            }
            ++i;
            if (funcs.isArithmetic(current) || funcs.isUnary(current)) {
                int arity = funcs.arity(current);
                string label = "[" + to_string(iteration++) + "]";
                cout << label << " = ";
                if (last < arity) {
                    throw runtime_error("Not enough arguments");
                    return;
                }
                --last;
                double prev = values[last];
                double value;
                if (arity == 1) {
                    if (funcs.associativity(current) == LEFT) {
                        cout << (current + " " + labels[last]);
                    }
                    else {
                        cout << (labels[last] + " " + current);
                    }
                    value = funcs.call(current, prev, 0);
                    cout << " = " << value << endl;
                }
                else {
                    --last;
                    value = funcs.call(current, values[last], prev);
                    cout << labels[last] << " " << input[i - 1] << " " <<
                        labels[last + 1] << " = " << value << endl;
                }
                labels[last] = label;
                values[last] = value;
                ++last;
            }
        }
    }
    if (last == 1) {
        --last;
        cout << "Finally: " << labels[last] << " = " << values[last] << endl;
        return;
    }
    throw runtime_error("Too many values entered");
}