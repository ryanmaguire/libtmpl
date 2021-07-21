#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static const double arr[53] = {4503599627370496, 2251799813685248, 1125899906842624, 562949953421312, 281474976710656, 140737488355328, 70368744177664, 35184372088832, 17592186044416, 8796093022208, 4398046511104, 2199023255552, 1099511627776, 549755813888, 274877906944, 137438953472, 68719476736, 34359738368, 17179869184, 8589934592, 4294967296, 2147483648, 1073741824, 536870912, 268435456, 134217728, 67108864, 33554432, 16777216, 8388608, 4194304, 2097152, 1048576, 524288, 262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};

static double my_abs(double x)
{
	if (x > 0)
		return x;
	return -x;
}

static double my_floor(double x)
{
	unsigned char n;
	double out;

	if (x > 1.0E16)
		return x;
	else if (x < 0.0)
		return -1.0 - my_floor(x);

	out = arr[0];
	n = 1U;

	while (my_abs(out - x) > 1.0)
	{
		if (x > out)
			out += arr[n];
		else
			out -= arr[n];

		++n;
	}

	if (out <= x)
		return out;
	else
		return out - 1.0;

}

int main(void)
{
	double *x, *y0, *y1, max, dx, temp;
	unsigned int N = 1E8;
	unsigned int n;
	clock_t t1, t2;

	max = 0.0;
	x  = malloc(sizeof(*x) * N);
	y0 = malloc(sizeof(*x) * N);
	y1 = malloc(sizeof(*x) * N);
	dx  = 1.0E16 / (double)N;

	x[0] = 0.0;
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

	for (n = 0UL; n < N; ++n)
	{
		temp = fabs(y0[n] - y1[n]);
		if (max < temp)
			max = temp;
	}

	printf("%.16f\n", max);

	free(x);
	free(y0);
	free(y1);
	return 0;
}
