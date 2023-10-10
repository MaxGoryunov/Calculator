#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <map>
#include <string>
#include <iostream>
#include <stack>
#include <functional>
#include "Funcs.h"

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::stack;
using std::function;

#pragma warning(disable:4996)

char const DELIMITER = ';';

// ���������
// ��������� �������� ���������������
// 4 ! ������
// 3 * / % �����
// 2 + - �����
// 1 = �����
int op_preced(const char c) {
    
    switch (c) {
    case '!':
        return 4;

    case '*':
    case '/':
        return 3;

    case '+':
    case '-':
        return 2;
    }
    return 0;
}

bool op_left_assoc(const char c)
{
    switch (c)
    {
        // ����-������������� ���������
    case '*':
    case '/':
    case '%':
    case '+':
    case '-':
        return true;
        // �����-������������� ���������
    case '!':
        return false;
    }
    return false;
}

unsigned int op_arg_count(const char c)
{
    switch (c)
    {
    case '*':
    case '/':
    case '%':
    case '+':
    case '-':
        return 2;
    case '!':
        return 1;

    default:
        return c - 'A';
    }
    return 0;
}

bool isIdent(string const& token) {
    return token >= "0" && token <= "9";
}

bool isIdent(char token) {
    return isIdent(string{ token });
}

bool isLetter(string const& token) {
    return token >= "A" && token <= "Z";
}

bool isLetter(char token) {
    return isLetter(string{ token });
}

bool isUnary(string const& name, Funcs& funcs) {
    if (name == "(" || name == ")") {
        return false;
    }
    if (funcs.associativity(name) == LEFT && funcs.arity(name) == 1) {
        return true;
    }
    return false;

}

bool isArithmeticFunction(string const& token, Funcs& funcs) {
    if (token == "(" || token == ")") {
        return false;
    }
    Associativity assoc = funcs.associativity(token);
    int arity = funcs.arity(token);
    if ((assoc == LEFT && arity == 2) || (assoc == RIGHT && arity == 1)) {
        return true;
    }
    return false;
}

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
        if (isUnary(top, funcs)) {
            output += top + DELIMITER;
            tokens.pop();
        }
    }
    return true;
}

void rearrangeOperators(stack<string>& tokens, string& current, string& output, Funcs& funcs) {
    while (!tokens.empty()) {
        string top = tokens.top();
        if (isArithmeticFunction(top, funcs) && ((funcs.associativity(current) && (funcs.precedence(current) <= funcs.precedence(top)))
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

#define is_operator(c) (c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '%')
#define is_function(c) (c >= 'A' && c <= 'Z')
#define is_ident(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))

bool shunting_yard(const char* input, char* output)
{
    const char* strpos = input, * strend = input + strlen(input);
    char c, stack[32], sc, * outpos = output;
    unsigned int sl = 0;
    while (strpos < strend)
    {
        c = *strpos;
        if (c != ' ')
        {
            // ���� ����� �������� ������ (���������������), �� �������� ��� � ������� ������.
            if (is_ident(c))
            {
                *outpos = c; ++outpos;
            }
            // ���� ����� - �������, �� �������� ��� � ����.
            else if (is_function(c))
            {
                stack[sl] = c;
                ++sl;
            }
            //���� ����� - ����������� ���������� ������� (�������):
            else if (c == ',')
            {
                bool pe = false;
                while (sl > 0)
                {
                    sc = stack[sl - 1];
                    if (sc == '(')
                    {
                        pe = true;
                        break;
                    }
                    else
                    {
                        // ���� �� ������� �� ����� ������� ������,
                        // ������������� ��������� �� ����� � ������� ������.
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                }
                // ���� �� ���� ���������� ����� ������� ������, ���� ����������� �� � ��� �����
                // ���� ���� ��������� ������
                if (!pe)
                {
                    printf("Error: separator or parentheses mismatched\n");
                    return false;
                }
            }
            // ���� ����� �������� op1, ��:
            else if (is_operator(c))
            {
                while (sl > 0)
                {
                    sc = stack[sl - 1];
                    // ���� �� ������� ����� ������������ ����� �������� op2,
                    // � ����� �������� op1 ����-������������� � ��� ��������� ������ ��� ����� �� ��� � ��������� op2,
                    // ��� �������� op1 �����-������������� � ��� ��������� ������ ��� � ��������� op2
                    if (is_operator(sc) &&
                        ((op_left_assoc(c) && (op_preced(c) <= op_preced(sc))) ||
                            (!op_left_assoc(c) && (op_preced(c) < op_preced(sc)))))
                    {
                        // ���������� �������� op2 �� ����� � ������� ������.
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                    else
                    {
                        break;
                    }
                }
                // �������� � ���� �������� op1
                stack[sl] = c;
                ++sl;
            }
            // ���� ����� - ����� ������� ������, �� �������� ��� � ����.
            else if (c == '(')
            {
                stack[sl] = c;
                ++sl;
            }
            // ���� ����� - ������ ������� ������:
            else if (c == ')')
            {
                bool pe = false;
                // �� ��������� �� ������� ����� ������ "����� ������� ������"
                // ������������� ��������� �� ����� � ������� ������.
                while (sl > 0)
                {
                    sc = stack[sl - 1];
                    if (sc == '(')
                    {
                        pe = true;
                        break;
                    }
                    else
                    {
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                }
                // ���� ���� �������� �� ���������� ������ ����� ������� ������, �� ���� ��������� ������.
                if (!pe)
                {
                    printf("Error: parentheses mismatched\n");
                    return false;
                }
                // ���������� ����� "����� ������� ������" �� ����� (�� ��������� � ������� ������).
                sl--;
                // ���� �� ������� ����� ����� - �������, �������� ��� � ������� ������.
                if (sl > 0)
                {
                    sc = stack[sl - 1];
                    if (is_function(sc))
                    {
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                }
            }
            else
            {
                printf("Unknown token %c\n", c);
                return false; // Unknown token
            }
        }
        ++strpos;
    }
    // ����� �� �������� ������� �� �����:
    // ���� � ����� �������� ������:
    while (sl > 0)
    {
        sc = stack[sl - 1];
        if (sc == '(' || sc == ')')
        {
            printf("Error: parentheses mismatched\n");
            return false;
        }
        *outpos = sc; ++outpos;
        --sl;
    }

    *outpos = 0; // ��������� ����������� ���� � ������
    return true;
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
    return readWhile(input, start, current, [](char tok) { return isIdent(tok) || tok == '.'; });
}

void readWholeWord(string const& input, int& start, string& current) {
    return readWhile(input, start, current, [](char tok) { return isLetter(tok); });
}

bool shunting_yard(string const& input, string& output) {
    cout << "SY for string" << endl;
    stack<string> tokens;
    Funcs funcs;
    int length = input.length();
    output = "";
    for (int i = 0; i < length; ++i) {
        char tok = input[i];
        string current{ tok };
        if (current != " ") {
            if (isIdent(tok)) {
                readWholeNumber(input, i, current);
                output += current + DELIMITER;
            }
            else if (isLetter(tok)) {
                readWholeWord(input, i, current);
                if (isUnary(current, funcs)) {
                    tokens.push(current);
                }
            }
            else if (isArithmeticFunction(current, funcs)) {
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
}

bool execution_order(const char* input)
{
    printf("order: (arguments in reverse order)\n");
    const char* strpos = input, * strend = input + strlen(input);
    char c, res[4];
    unsigned int sl = 0, sc, stack[32], rn = 0;
    // ���� �� ����� �������� ������
    while (strpos < strend)
    {
        // ��������� ��������� �����
        c = *strpos;
        // ���� ����� - �������� ��� �������������
        if (is_ident(c))
        {
            // ��������� ��� � ����
            stack[sl] = c;
            ++sl;
        }
        // � ��������� ������, ����� - �������� (����� ��� ���������� ���������� ��� ��������, ��� � �������� �������)
        else if (is_operator(c) || is_function(c))
        {
            sprintf(res, "_%02d", rn);
            printf("%s = ", res);
            ++rn;
            // ������� ��������, ��� �������� ��������� n ����������
            unsigned int nargs = op_arg_count(c);
            unsigned int Tnargs = nargs;
            // ���� � ����� �������� ������, ��� n
            if (sl < nargs)
            {
                // (������) ������������� ���������� ���������� � ���������.
                return false;
            }
            // � ��������� ������, ����� ��������� n ���������� �� �����
            // ��������� ��������, ���� ��� �������� � �������� ����������
            if (is_function(c))
            {
                printf("%c(", c);
                while (nargs > 0)
                {
                    sc = stack[sl - nargs];
                    if (nargs > 1)
                    {
                        printf("%s, ", &sc);
                    }
                    else
                    {
                        printf("%s)\n", &sc);
                    }
                    --nargs;
                }
                sl -= Tnargs;
            }
            else
            {
                if (nargs == 1)
                {
                    sc = stack[sl - 1];
                    sl--;
                    printf("%c %s;\n", c, &sc);
                }
                else
                {
                    sc = stack[sl - 2];
                    printf("%s %c ", &sc, c);
                    sc = stack[sl - 1];
                    printf("%s;\n", &sc);
                    sl -= 2;

                }
            }
            // ���� �������� �������������� ��������, ��������� ������� � ����.
            stack[sl] = *(unsigned int*)res;
            ++sl;
        }
        ++strpos;
    }
    // ���� � ����� �������� ���� ���� ��������,
    // ��� ����� �������� ����������� ����������.
    if (sl == 1)
    {
        sc = stack[sl - 1];
        sl--;
        printf("%s is a result\n", &sc);
        return true;
    }
    // ���� � ����� ������� ���������� ��������,
    // (������) ������������ ��� ������� ����� ��������.
    return false;
}

int main()
{
    // ����� �������: A() B(a) C(a, b), D(a, b, c) ...
    // ��������������: 0 1 2 3 ... and a b c d e ...
    // ���������: = - + / * % !
    const char* input = "D(f - b * c + d, !e, g)";
    char output[128];
    printf("input: %s\n", input);
    if (shunting_yard(input, output))
    {
        printf("output: %s\n", output);
        execution_order(output);
    }
    return 0;
}