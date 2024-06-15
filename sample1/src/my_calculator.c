#include "my_calculator.h"
#include <stdio.h>
#include <math.h>

#include "my_math.h"

float calculate(const char *input)
{
    float a, b, ret = 0.f;
    char operator;
    int n = sscanf(input, "%f %c %f", &a, &operator, & b);
    if (n == 3)
    {
        switch (operator)
        {
        case '+':
            ret = add(a, b);
            break;
        case '-':
            ret = sub(a, b);
            break;
        case '*':
            ret = mul(a, b);
            break;
        case '/':
            ret = div(a, b);
            break;
        case '^':
            ret = powf(a, b);
            break;
        default:
            printf("Invalid operator %c in '%s'", operator, input);
            break;
        }
    }
    else
    {
        printf("Invalid input '%s'", input);
    }
    return ret;
}
