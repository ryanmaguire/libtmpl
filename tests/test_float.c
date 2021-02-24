#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int counter = 0U;

typedef struct float_test_struct_in {
    float (*ftmpl)(float);
    float (*fext)(float);
    float start;
    float end;
    float EPS;
    unsigned long samples;
} float_test_struct_in;

typedef struct float_test_struct_out {
    float rel_error;
    float worst_rel_point;
    float abs_error;
    float worst_abs_point;
    double tmpl_comp_time;
    double ext_comp_time;
} float_test_struct_out;

static void
test_func(float_test_struct_in test_data, FILE *fp, const char *func_name)
{
    float *x, *yext, *ytmpl, temp, dx;
    unsigned long n;
    float_test_struct_out out_data;
    clock_t t1, t2;

    dx = (test_data.end - test_data.start) / (float)test_data.samples;

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

    out_data.rel_error = 0.0;
    out_data.abs_error = 0.0;
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
    fprintf(fp, "\tMax Rel Error:   %.8f\n", out_data.rel_error);
    fprintf(fp, "\tWorst Rel Point: %.8f\n", out_data.worst_rel_point);
    fprintf(fp, "\tMax Abs Error:   %.8f\n", out_data.abs_error);
    fprintf(fp, "\tWorst Abs Point: %.8f\n", out_data.worst_abs_point);
    fprintf(fp, "\ttmpl Time:       %.8f\n", out_data.tmpl_comp_time);
    fprintf(fp, "\text Time:        %.8f\n", out_data.ext_comp_time);

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
    float_test_struct_in in;
    FILE *fp;
    fp = fopen("test_results_float.txt", "w");

    in.fext    = logf;
    in.ftmpl   = tmpl_Float_Log;
    in.start   = 0.0F;
    in.end     = 1.0e8F;
    in.samples = 1E8;
    in.EPS     = 1.0e-6F;

    test_func(in, fp, "tmpl_Float_Log vs. logf (C99)");

    if (counter != 0)
        printf("FAILED\nSee test_results_float.txt for details.\n");
    else
        printf("PASSED\nSee test_results_float.txt for details.\n");

    fclose(fp);
    return 0;
}
