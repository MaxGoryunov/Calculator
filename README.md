# Calculator

*Calculator* is a simple CLI(command line interface) app which can take user's
input in the form of a mathematical expression, show performed calculations
step-by-step and finally produce the result.

## Supported functions

### Arithmetic functions

Addition: `3 + 4`
Subtraction: `7 - 2`
Multiplication: `4 * 8`
Division: `9 / 3`

### Mathematical functions

Sine: `sin(3.14)`
Exponentiation: `exp(1.5)`
Round function: `round(2.38)`

## Adding other implementations

Mathematical functions are implemented in the form of DLLs. If you want to add
an implementation of your own function, [create a DLL project](https://learn.microsoft.com/ru-ru/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170)
(make sure to change the project's architecture to x64) and copy the generated
`.dll` file into `libs/` folder. After that you can use this function in your
inputs.

## DLL structure

Your created dynamic library must export these functions:
```C
string name(void);

int precedence(void);

bool associativity(void);

int arity(void);

double apply(double left, double right);
```

Do not forget to append these declarations with `extern "C"` and
`__declspec(dllexport)`.

