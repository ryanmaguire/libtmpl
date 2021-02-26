#include <libtmpl/include/tmpl_math.h>
#include "tmpl_compare_funcs.h"
#include <math.h>
#include <stdio.h>

int main(void)
{
    FILE *fp;

    const float start     = -1.0e6F;
    const float end       =  1.0e6F;
    const unsigned long N = 1E8;
    const float eps = 1.0e-6F;

    fp = fopen("test_results_float.txt", "w");

    tmpl_Compare_Float_1in1out("tmpl_Float_Abs", tmpl_Float_Abs, "fabsf (C99)",
                               fabsf, start, end, N, eps, fp);

    tmpl_Compare_Float_1in1out("tmpl_Float_Log", tmpl_Float_Log, "logf (C99)",
                               logf, 0.0F, end, N, eps, fp);

    fclose(fp);
    return 0;
}
