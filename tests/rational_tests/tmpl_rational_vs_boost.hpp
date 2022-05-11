#include <boost/rational.hpp>

extern "C" {
#include <libtmpl/include/tmpl_rational.h>
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static signed long int random_int(void)
{
    int a = rand();

    while (a == 0)
    {
        a = rand();
    }

    return (signed long int)a;
}

#define TEST1(f0, op, N)                                                       \
int main(void)                                                                 \
{                                                                              \
    tmpl_RationalNumber *A, *B, *C;                                            \
    boost::rational<signed long int> *X, *Y, *Z;                               \
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
    double tmp;                                                                \
    double max = 0.0;                                                          \
    double rms = 0.0;                                                          \
    A = static_cast<tmpl_RationalNumber *>(malloc(sizeof(*A)*N));              \
    B = static_cast<tmpl_RationalNumber *>(malloc(sizeof(*B)*N));              \
    C = static_cast<tmpl_RationalNumber *>(malloc(sizeof(*C)*N));              \
    X = static_cast<boost::rational<signed long int> *>(malloc(sizeof(*X)*N)); \
    Y = static_cast<boost::rational<signed long int> *>(malloc(sizeof(*Y)*N)); \
    Z = static_cast<boost::rational<signed long int> *>(malloc(sizeof(*Z)*N)); \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        signed long int a = random_int();                                      \
        signed long int b = random_int();                                      \
        signed long int c = random_int();                                      \
        signed long int d = random_int();                                      \
        A[n] = tmpl_RationalNumber_Create(a, b);                               \
        B[n] = tmpl_RationalNumber_Create(c, d);                               \
        X[n] = boost::rational<signed long int>(a, b);                         \
        Y[n] = boost::rational<signed long int>(c, d);                         \
    }                                                                          \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0; n < N; ++n)                                                    \
        C[n] = f0(&A[n], &B[n]);                                               \
    t2 = clock();                                                              \
    printf("libtmpl: %f\n", (double)(t2 - t1)/(double)(CLOCKS_PER_SEC));       \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0; n < N; ++n)                                                    \
        Z[n] = X[n] op Y[n];                                                   \
    t2 = clock();                                                              \
    printf("boost:   %f\n", (double)(t2 - t1)/(double)(CLOCKS_PER_SEC));       \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        double x = boost::rational_cast<double>(Z[n]);                         \
        double y = tmpl_RationalNumber_As_Double(&C[n]);                       \
        tmp = fabs((x - y)/y);                                                 \
        rms += tmp*tmp;                                                        \
        if (max < tmp)                                                         \
            max = tmp;                                                         \
    }                                                                          \
                                                                               \
    rms = sqrt(rms / static_cast<double>(N));                                  \
    printf("rms error: %e\n", rms);                                            \
    printf("max error: %e\n", max);                                            \
                                                                               \
    free(A);                                                                   \
    free(B);                                                                   \
    free(C);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}

#define TEST2(f0, op, N)                                                       \
int main(void)                                                                 \
{                                                                              \
    tmpl_RationalNumber *A, *B;                                                \
    boost::rational<signed long int> *X, *Y;                                   \
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
    double tmp;                                                                \
    double max = 0.0;                                                          \
    double rms = 0.0;                                                          \
    A = static_cast<tmpl_RationalNumber *>(malloc(sizeof(*A)*N));              \
    B = static_cast<tmpl_RationalNumber *>(malloc(sizeof(*B)*N));              \
    X = static_cast<boost::rational<signed long int> *>(malloc(sizeof(*X)*N)); \
    Y = static_cast<boost::rational<signed long int> *>(malloc(sizeof(*Y)*N)); \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        signed long int a = random_int();                                      \
        signed long int b = random_int();                                      \
        signed long int c = random_int();                                      \
        signed long int d = random_int();                                      \
        A[n] = tmpl_RationalNumber_Create(a, b);                               \
        B[n] = tmpl_RationalNumber_Create(c, d);                               \
        X[n] = boost::rational<signed long int>(a, b);                         \
        Y[n] = boost::rational<signed long int>(c, d);                         \
    }                                                                          \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0; n < N; ++n)                                                    \
        f0(&A[n], &B[n]);                                                      \
    t2 = clock();                                                              \
    printf("libtmpl: %f\n", (double)(t2 - t1)/(double)(CLOCKS_PER_SEC));       \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0; n < N; ++n)                                                    \
        X[n] op Y[n];                                                          \
    t2 = clock();                                                              \
    printf("boost:   %f\n", (double)(t2 - t1)/(double)(CLOCKS_PER_SEC));       \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        double x = boost::rational_cast<double>(X[n]);                         \
        double y = tmpl_RationalNumber_As_Double(&A[n]);                       \
        tmp = fabs((x - y)/y);                                                 \
        rms += tmp*tmp;                                                        \
        if (max < tmp)                                                         \
            max = tmp;                                                         \
    }                                                                          \
                                                                               \
    rms = sqrt(rms / static_cast<double>(N));                                  \
    printf("rms error: %e\n", rms);                                            \
    printf("max error: %e\n", max);                                            \
                                                                               \
    free(A);                                                                   \
    free(B);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    return 0;                                                                  \
}
