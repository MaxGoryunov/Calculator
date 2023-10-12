#include <iostream>
#include <functional>
#include "Expression.h"
#include "StringUtils.h"
#include "Tokens.h"

using std::map;
using std::string;
using std::stack;
using std::function;
using std::cout;
using std::endl;
using std::vector;
using std::stod;
using std::to_string;
using std::runtime_error;
using SU = StringUtils;

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
    return readWhile(input, start, current, [](char tok) { return SU::isDigit(string{ tok }) || tok == '.'; });
}

void Expression::readWholeWord(string const& input, int& start, string& current) {
    return readWhile(input, start, current, [](char tok) { return SU::isLetter(string{ tok }); });
}

void Expression::separateTokens(string const& input, Funcs& funcs) {
    Tokens tokens;
    //Funcs funcs;
    int length = input.length();
    this->tokens.clear();
    for (int i = 0; i < length; ++i) {
        char tok = input[i];
        string current{ tok };
        if (current != " ") {
            if (SU::isDigit(string{ tok })) {
                readWholeNumber(input, i, current);
                this->tokens.push_back(current);
            }
            else if (SU::isLetter(string{ tok })) {
                readWholeWord(input, i, current);
                if (funcs.isUnary(current)) {
                    tokens.push(current);
                }
            }
            else if (funcs.isArithmetic(current)) {
                tokens.rearrangeOperators(current, funcs, this->tokens);
            }
            else if (current == "(") {
                tokens.push(current);
            }
            else if (current == ")") {
                if (!tokens.rearrangeParentheses(funcs, this->tokens)) {
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
    tokens.cleanup(this->tokens);
}

void Expression::printResult(Funcs& funcs) {
    int length = this->tokens.size();
    vector<string> labels(length);
    vector<double> values(length);
    int last = 0;
    int iteration = 0;
    for (int i = 0; i < length; ++i) {
        string current = this->tokens[i];
        if (SU::isNumber(current)) {
            labels[last] = current;
            values[last] = stod(current);
            ++last;
        }
        else {
            if (SU::isWord(current)) {
                labels[last] = current;
            }
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
                    cout << labels[last] << " " << current << " " <<
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