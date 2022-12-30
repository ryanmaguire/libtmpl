#include <stdio.h>
#include <time.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_vector_integer.h>

int main(void)
{
    clock_t t1, t2;
    tmpl_ULongVector *out;
    const unsigned int N = 1E5;
    unsigned int n;

    for (n = 0; n < N; ++n)
    {
        t1 = clock();
        out = tmpl_ULong_Sieve_of_Eratosthenes(n);
        t2 = clock();

        if (!out)
        {
            puts("out == NULL. Aborting.");
            return -1;
        }
        else if (out->error_occurred)
        {
            if (out->error_message != NULL)
                puts(out->error_message);
            return -1;
        }
        tmpl_Destroy_ULongVector(&out);
        printf("%u: %f\n", n, (double)(t2-t1)/CLOCKS_PER_SEC);
    }

    return 0;
}

