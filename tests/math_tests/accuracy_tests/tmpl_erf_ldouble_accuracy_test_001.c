#include <math.h>
#include <stdio.h>
#include <libtmpl/include/tmpl_math.h>

int main(void)
{
	FILE *fp = fopen("test.txt", "w");

	const long double start = 2.0L;
	const long double end = 8.5L;
	const long double dx = 0x1.0p-12;
	long double x = start;

	while (x < end)
	{
		const long double y = erfl(x);
		const long double z = tmpl_LDouble_Erf(x);
		fprintf(fp, "%.36Le, %.36Le, %.36Le\n", x, y, z);
		x += dx;
	}

	fclose(fp);
	return 0;
}
