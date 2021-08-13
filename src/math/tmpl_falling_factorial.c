/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

unsigned long tmpl_Falling_Factorial(unsigned int x, unsigned int N)
{
    unsigned int n;
    unsigned long falling_factorial;

    if (N == 0U)
        falling_factorial = 1;
    else if (N > x)
        falling_factorial = 0;
    else if (N == 1U)
        falling_factorial = x;
    else
    {
        falling_factorial = x;
        for (n=1; n<N; ++n)
            falling_factorial *= (x-n);
    }
    return falling_factorial;
}

