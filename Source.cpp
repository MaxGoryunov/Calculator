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
#include "Expression.h"

int main() {
    const char* input = "(3*4+5)*(2+7/8)";
    char output[128];
    printf("input: %s\n", input);
    string inp = "(3*4.5+5)*(2+7.2/8)+4";
    Expression exp;
    Funcs funcs;
    exp.separateTokens(inp, funcs);
    exp.printResult(funcs);
    return 0;
}