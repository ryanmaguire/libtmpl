#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static const double arr[53] = {
    4503599627370496.0,
    2251799813685248.0,
    1125899906842624.0,
    562949953421312.0,
    281474976710656.0,
    140737488355328.0,
    70368744177664.0,
    35184372088832.0,
    17592186044416.0,
    8796093022208.0,
    4398046511104.0,
    2199023255552.0,
    1099511627776.0,
    549755813888.0,
    274877906944.0,
    137438953472.0,
    68719476736.0,
    34359738368.0,
    17179869184.0,
    8589934592.0,
    4294967296.0,
    2147483648.0,
    1073741824.0,
    536870912.0,
    268435456.0,
    34217728.0,
    67108864.0,
    33554432.0,
    16777216.0,
    8388608.0,
    4194304.0,
    2097152.0,
    1048576.0,
    524288.0,
    262144.0,
    131072.0,
    65536.0,
    32768.0,
    16384.0,
    8192.0,
    4096.0,
    2048.0,
    1024.0,
    512.0,
    256.0,
    128.0,
    64.0,
    32.0,
    16.0,
    8.0,
    4.0,
    2.0,
    1.0
};

static double my_floor(double x)
{
	unsigned char n;
	double out, dx;
    const double abs_x = fabs(x);

	if (x > 1.0E16)
		return x;

    n = 0U;

    while(abs_x < arr[n])
    {
        ++n;
    }

	out = arr[n];
    dx = abs_x - out;
	n = n + 1U;

	while (dx > 1.0)
	{
		if (abs_x > out)
			out += arr[n];
		else if (x < out)
			out -= arr[n];
        else
            return out;

        dx = fabs(abs_x - out);
		++n;
	}

    if (x > 0.0)
    {
	    if (out <= abs_x)
		    return out;
	    else
		    return out - 1.0;
    }
    else
    {
        if (out == abs_x)
            return -abs_x;
	    else if (out < abs_x)
		    return -1.0 - out;
	    else
		    return -out;
    }
}

int main(void)
{
	double *x, *y0, *y1, max, dx, temp;
	unsigned int N = 1E8;
	unsigned int n, ind;
	clock_t t1, t2;

	max = 0.0;
	x  = malloc(sizeof(*x) * N);
	y0 = malloc(sizeof(*x) * N);
	y1 = malloc(sizeof(*x) * N);
	dx  = 0.1;

	x[0] = -0.5*dx*(double)N;
	for (n = 1UL; n < N; ++n)
		x[n] = x[n-1] + dx;

	t1 = clock();
	for (n = 0UL; n < N; ++n)
		y0[n] = my_floor(x[n]);
	t2 = clock();
	printf("%f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y1[n] = floor(x[n]);
    t2 = clock();
    printf("%f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    ind = 0UL;
	for (n = 0UL; n < N; ++n)
	{
		temp = fabs(y0[n] - y1[n]);
		if (max < temp)
        {
		    max = temp;
            ind = n;
        }
	}

	printf("Error: %.16f\nWorst: %.16f %.16f %.16f\n",
           max, x[ind], y0[ind], y1[ind]);

	free(x);
	free(y0);
	free(y1);
	return 0;
}
