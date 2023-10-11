#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <map>
#include <string>
#include <iostream>
#include <stack>
#include <functional>
#include <stdexcept>
#include <vector>
#include "Funcs.h"
#include "App.h"
#include "Expression.h"
#include "DllCatalogue.h"

using std::cin;
using std::string;
using std::getline;
using std::runtime_error;

int main() {
    Expression expression;
    Funcs funcs;
    DllCatalogue libraries("plugins");
    App app(expression, libraries, funcs);
    try {
        while (true) {
            string input;
            getline(cin, input);
            app.calculate(input);
        }
    }
    catch (runtime_error const& error) {
        std::cerr << error.what() << endl;
    }
    return 0;
}