#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static double parse_number(const char *s, int *ok) {
    char *end = NULL;
    errno = 0;
    double val = strtod(s, &end);

    if (s == end || *end != '\0' || errno != 0) {
        *ok = 0;
        return 0.0;
    }
    *ok = 1;
    return val;
}

static double add(double a, double b)      { return a + b; }
static double subtract(double a, double b) { return a - b; }
static double multiply(double a, double b) { return a * b; }
static double divide(double a, double b)   { return a / b; }

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <number1> <operator> <number2>\n", argv[0]);
        return 1;
    }

    
    if (strlen(argv[2]) != 1) {
        printf("Error: Operator must be one of +  -  *  /\n");
        return 1;
    }

    int ok1 = 0, ok2 = 0;
    double num1 = parse_number(argv[1], &ok1);
    double num2 = parse_number(argv[3], &ok2);

    if (!ok1 || !ok2) {
        printf("Error: Invalid number input.\n");
        return 1;
    }

    char op = argv[2][0];
    double result;

    switch (op) {
        case '+':
            result = add(num1, num2);
            break;
        case '-':
            result = subtract(num1, num2);
            break;
        case '*':  
            result = multiply(num1, num2);
            break;
        case '/':
            if (num2 == 0.0) {
                printf("Error: Division by zero is not allowed.\n");
                return 1;
            }
            result = divide(num1, num2);
            break;
        default:
            printf("Error: Unsupported operator. Use +  -  *  /\n");
            return 1;
    }

    printf("Result: %.2f\n", result);
    return 0;
}
