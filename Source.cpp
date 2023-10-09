#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <map>

using std::map;

#pragma warning(disable:4996)

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
    case '%':
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