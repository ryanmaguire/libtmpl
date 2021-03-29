#include <stdio.h>
#include <stdlib.h>

unsigned int **Sieve_of_Eratosthenes(unsigned int N)
{
    unsigned int **out = malloc(sizeof(*out) * 2);
    unsigned int n, k;

    if (N < 2)
        return NULL;

    out[0] = malloc(sizeof(*out[0]) * 2);
    out[0][0] = 1U;
    out[0][1] = 2U;

    out[1] = malloc(sizeof(*out[1]) * N);
    out[1][0] = 0;
    out[1][1] = 0;
    out[1][2] = 2; 

    for (n = 3; n <= N; ++n)
    {
        for (k = 1U; k <= out[0][0]; ++k)
        {
            if ((n % out[0][k]) == 0)
                break;
        }
        if (k == (out[0][0]+1))
        {
            out[0][0] += 1U;
            out[0] = realloc(out[0], sizeof(*out[0]) * (out[0][0] + 1));
            out[0][out[0][0]] = n;
        }
        out[1][n] = out[0][0];
    }

    return out;
}

int main(void)
{
    unsigned int N = 1E7;
    unsigned int **out = Sieve_of_Eratosthenes(N);
    unsigned int n;
    FILE *fp = fopen("data.txt", "w");
    for (n = 1; n < N; ++n)
        fprintf(fp, "%f\n", (double)out[1][n] / (double)n);

    fclose(fp);
    free(out[0]);
    free(out[1]);
    free(out);
    return 0;
}
