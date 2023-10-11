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

## Example

Input:
```
(3+4)*(5-2/4)+sin(1.57+0)*exp(2)-round(3.14)
```

Output:
```
3;4;+;5;2;4;/;-;*;1.57;0;+;sin;2;exp;*;+;3.14;round;-;
[0] = 3 + 4 = 7
[1] = 2 / 4 = 0.5
[2] = 5 - [1] = 4.5
[3] = [0] * [2] = 31.5
[4] = 1.57 + 0 = 1.57
[5] = sin [4] = 1
[6] = exp 2 = 7.38906
[7] = [5] * [6] = 7.38905
[8] = [3] + [7] = 38.8891
[9] = round 3.14 = 3
[10] = [8] - [9] = 35.8891
Finally: [10] = 35.8891
```