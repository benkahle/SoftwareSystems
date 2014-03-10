#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    int numer;
    int denom;
} Rational;

// Returns a new Rational with the given numer and denom.
// If unable to allocate, prints an error message and exits.
Rational *make_rational(int numer, int denom) {
    Rational *rat = malloc(sizeof(Rational));
    if (!rat) {
        printf("%s\n", "Malloc encountered an error.");
        exit(1);
    }
    rat->numer = numer;
    rat->denom = denom;
    return rat;
}

// Computes a floating-point approximation of a Rational.
double rational_to_double(Rational *rational) {
    double numer = (double) rational->numer;
    double denom = (double) rational->denom;
    double result = numer/denom;
    return result;
}

// Multiplies two rational numbers; returns a new Rational.
Rational *mult_rational(Rational *r1, Rational *r2) {
    int numer = r1->numer*r2->numer;
    int denom = r1->denom*r2->denom;
    Rational *r3 = make_rational(numer, denom);
    return r3;
}

// Frees a Rational.
void free_rational(Rational *rational) {
    free(rational);
}

// Prints a rational in fraction form.
void print_rational(Rational *rational) {
    printf("%d / %d\n", rational->numer, rational->denom);
}

int main(void)
{
    Rational *rational = make_rational(3, 7);
    print_rational(rational);

    double d = rational_to_double(rational);
    printf("%lf\n", d);

    Rational *square = mult_rational(rational, rational);
    print_rational(square);
	
    free_rational(rational);
    free_rational(square);

    return EXIT_SUCCESS;
}
