#include <libtmpl/include/tmpl_array_integer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	const size_t N = (size_t)1E7;
	long *arr = malloc(sizeof(*arr) * N);
	size_t n;
	double ans;
	clock_t t0, t1;

	for (n = 0; n < N; ++n)
		arr[n] = (long)n + 9223372036844775807L;

	t0 = clock();
	ans = tmpl_Long_Array_Double_RMS(arr, N);
	t1 = clock();

	printf("%.18f\n", (double)(t1 - t0)/CLOCKS_PER_SEC);
	printf("%.18e\n", ans);
        free(arr);
	return 0;
}
