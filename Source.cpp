#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <map>
#include <string>
#include <iostream>
#include <stack>
#include <functional>
#include <vector>
#include "Funcs.h"
#include "StringUtils.h"

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::stack;
using std::function;
using std::vector;
using std::stod;
using std::to_string;
using SU = StringUtils;

#pragma warning(disable:4996)

char const DELIMITER = ';';


bool rearrangeParentheses(stack<string>& tokens, string& output, Funcs& funcs) {
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
        cout << "Number of left and right parentheses does not match" << endl;
        return false;
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

void rearrangeOperators(stack<string>& tokens, string& current, string& output, Funcs& funcs) {
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

void readWhile(string const& input, int& start, string& current, function<bool(char)> predicate) {
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

void readWholeNumber(string const& input, int& start, string& current) {
    return readWhile(input, start, current, [](char tok) { return SU::isIdent(string{ tok }) || tok == '.'; });
}

void readWholeWord(string const& input, int& start, string& current) {
    return readWhile(input, start, current, [](char tok) { return SU::isLetter(string{tok}); });
}

bool tokensCleanup(stack<string> tokens, string& output) {
    while (!tokens.empty()) {
        string top = tokens.top();
        tokens.pop();
        if (top == "(" || top == ")") {
            cout << "Error: parentheses mismatched" << endl;
            return false;
        }
        output += top + DELIMITER;
    }
    return true;
}

bool shunting_yard(string const& input, string& output) {
    //cout << "SY for string" << endl;
    stack<string> tokens;
    Funcs funcs;
    int length = input.length();
    output = "";
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
                    return false;
                }
            }
            else
            {
                cout << "Token " << current << " is an unknown token" << endl;
                return false;
            }
        }
    }
    return tokensCleanup(tokens, output);
}

bool evaluate(string const& input) {
    int length = input.length();
    Funcs funcs;
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
                    cout << "Not enough arguments" << endl;
                    return false;
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
        return true;
    }
    cout << "Too many values entered" << endl;
    return false;
}

int main()
{
    // Имена функций: A() B(a) C(a, b), D(a, b, c) ...
    // идентификаторы: 0 1 2 3 ... and a b c d e ...
    // операторы: = - + / * % !
    const char* input = "(3*4+5)*(2+7/8)";
    char output[128];
    printf("input: %s\n", input);
    string inp = "(3*4.5+5)*(2+7.2/8)+4";
    cout << "------" << endl;
    string out;
    shunting_yard(string{ inp }, out);
    cout << out << endl;
    evaluate(out);
    return 0;
}