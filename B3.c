#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 100
#define EPSILON 0.000001f

typedef struct {
    int degree;
    float coef[MAX_DEGREE + 1];
} Polynomial;

float coefficientAt(Polynomial p, int exponent)
{
    if (exponent < 0 || exponent > p.degree)
        return 0.0f;
    return p.coef[p.degree - exponent];
}

Polynomial addPolynomials(Polynomial a, Polynomial b)
{
    Polynomial result;
    int exponent;
    result.degree = (a.degree > b.degree)
                    ? a.degree : b.degree;
    for (exponent = result.degree; exponent >= 0; exponent--) {
        float sum = coefficientAt(a, exponent)
                  + coefficientAt(b, exponent);
        if (fabsf(sum) < EPSILON)
            sum = 0.0f;
        result.coef[result.degree - exponent] = sum;
    }
    return result;
}

void readPolynomial(Polynomial *p, char label)
{
    int i;
    printf("Enter degree of %c(x): ", label);
    scanf("%d", &p->degree);
    if (p->degree < 0 || p->degree > MAX_DEGREE) {
        printf("Degree must be between 0 and %d.\n",
               MAX_DEGREE);
        p->degree = -1;
        return;
    }
    printf("Enter %d coefficients from x^%d to x^0:\n",
           p->degree + 1, p->degree);
    for (i = 0; i <= p->degree; i++)
        scanf("%f", &p->coef[i]);
}

void displayPolynomial(Polynomial p)
{
    int i, exponent, first = 1;
    float c, magnitude;
    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exponent = p.degree - i;
        if (fabsf(c) < EPSILON)
            continue;
        if (!first)
            printf(c < 0 ? " - " : " + ");
        else if (c < 0)
            printf("-");
        magnitude = fabsf(c);
        if (exponent == 0) {
            printf("%g", magnitude);
        } else {
            if (fabsf(magnitude - 1.0f) >= EPSILON)
                printf("%g", magnitude);
            if (exponent == 1)
                printf("x");
            else
                printf("x^%d", exponent);
        }
        first = 0;
    }
    if (first)
        printf("0");
    printf("\n");
}

int main(void)
{
    Polynomial a, b, result;
    readPolynomial(&a, 'A');
    if (a.degree < 0)
        return 1;
    readPolynomial(&b, 'B');
    if (b.degree < 0)
        return 1;
    printf("\nA(x) = ");
    displayPolynomial(a);
    printf("B(x) = ");
    displayPolynomial(b);
    result = addPolynomials(a, b);
    printf("Sum = ");
    displayPolynomial(result);
    return 0;
}