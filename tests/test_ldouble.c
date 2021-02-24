#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int counter;

typedef struct long_double_test_struct_in {
    long double (*ftmpl)(long double);
    long double (*fext)(long double);
    long double start;
    long double end;
    long double EPS;
    unsigned long samples;
} long_double_test_struct_in;

typedef struct long_double_test_struct_out {
    long double rel_error;
    long double worst_rel_point;
    long double abs_error;
    long double worst_abs_point;
    double tmpl_comp_time;
    double ext_comp_time;
} long_double_test_struct_out;

static void
test_func(long_double_test_struct_in test_data, FILE *fp, const char *func_name)
{
    long double *x, *yext, *ytmpl, temp, dx;
    unsigned long n;
    long_double_test_struct_out out_data;
    clock_t t1, t2;

    dx = (test_data.end - test_data.start) / (long double)test_data.samples;

    x = malloc(sizeof(*x) * test_data.samples);
    yext = malloc(sizeof(*yext) * test_data.samples);
    ytmpl = malloc(sizeof(*ytmpl) * test_data.samples);

    x[0] = test_data.start;
    for (n = 1UL; n < test_data.samples; ++n)
        x[n] = x[n-1] + dx;

    t1 = clock();
    for (n = 0UL; n < test_data.samples; ++n)
        yext[n] = test_data.fext(x[n]);
    t2 = clock();
    out_data.ext_comp_time = (double)(t2-t1)/CLOCKS_PER_SEC;

    t1 = clock();
    for (n = 0UL; n < test_data.samples; ++n)
        ytmpl[n] = test_data.ftmpl(x[n]);
    t2 = clock();
    out_data.tmpl_comp_time = (double)(t2-t1)/CLOCKS_PER_SEC;

    out_data.rel_error = 0.0L;
    out_data.abs_error = 0.0L;
    out_data.worst_rel_point = test_data.start;
    out_data.worst_abs_point = test_data.start;

    for (n = 0UL; n < test_data.samples; ++n)
    {
        temp = fabs(ytmpl[n] - yext[n]);
        if (temp > out_data.abs_error)
        {
            out_data.abs_error       = temp;
            out_data.worst_abs_point = x[n];
        }

        temp = fabs((ytmpl[n] - yext[n])/yext[n]);
        if (temp > out_data.rel_error)
        {
            out_data.rel_error       = temp;
            out_data.worst_rel_point = x[n];
        }
    }

    fprintf(fp, "%s\n", func_name);
    fprintf(fp, "\tMax Rel Error:   %.24Lf\n", out_data.rel_error);
    fprintf(fp, "\tWorst Rel Point: %.24Lf\n", out_data.worst_rel_point);
    fprintf(fp, "\tMax Abs Error:   %.24Lf\n", out_data.abs_error);
    fprintf(fp, "\tWorst Abs Point: %.24Lf\n", out_data.worst_abs_point);
    fprintf(fp, "\ttmpl Time:       %f\n", out_data.tmpl_comp_time);
    fprintf(fp, "\text Time:        %f\n", out_data.ext_comp_time);

    if (out_data.rel_error <= test_data.EPS)
        fprintf(fp, "Test PASSED\n\n");
    else
    {
        fprintf(fp, "Test FAILED\n\n");
        counter = 1UL;
    }

    free(x);
    free(yext);
    free(ytmpl);

    return;
}

int main(void)
{
    long_double_test_struct_in in;
    FILE *fp;
    fp = fopen("test_results_long_double.txt", "w");

    in.fext = fabsl;
    in.ftmpl = tmpl_LDouble_Abs;
    in.start = -1.0e6L;
    in.end   =  1.0e6L;
    in.samples = 1E8;
    test_func(in, fp, "tmpl_LDouble_Abs vs. fabsl (C99)");

    in.fext    = logl;
    in.ftmpl   = tmpl_LDouble_Log;
    in.start   = 0.0L;
    in.end     = 1.0e6L;
    in.samples = 1E8;
    in.EPS     = 1.0e-16L;

    test_func(in, fp, "tmpl_LDouble_Log vs. logl (C99)");

    if (counter != 0)
        printf("FAILED\nSee test_results_ldouble.txt for details.\n");
    else
        printf("PASSED\nSee test_results_ldouble.txt for details.\n");

    fclose(fp);
    return 0;
}

