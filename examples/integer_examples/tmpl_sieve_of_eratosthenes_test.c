#include <stdio.h>
#include <time.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_vector_integer.h>

int main(void)
{
    const unsigned long int N = 1000UL;
    unsigned long int n;
    tmpl_ULongVector *out = tmpl_ULong_Sieve_of_Eratosthenes(N);

    if (!out)
    {
        puts("out == NULL. Aborting.");
        return -1;
    }
    else if (out->error_occurred)
    {
        if (out->error_message != NULL)
            puts(out->error_message);
        else
            puts("error_occurred == true with no error message.");

        tmpl_Destroy_ULongVector(&out);
        return -1;
    }

    for (n = 0UL; n < out->length; ++n)
        printf("%03lu: %03lu\n", n, out->data[n]);

    tmpl_Destroy_ULongVector(&out);
    return 0;
}
