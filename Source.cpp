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
#include "App.h"
#include "Expression.h"
#include "DllCatalogue.h"

using std::cin;
using std::string;
using std::getline;

int main() {
    Expression expression;
    Funcs funcs;
    DllCatalogue libraries("libs");
    App app(expression, libraries, funcs);
    while (true) {
        string input;
        getline(cin, input);
        app.calculate(input);
    }
    return 0;
}