#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>


int main(void)
{
	char *str, *test1, *test2, *test3;
	int random;
	double max1, max2, temp;
	unsigned long int n;
	unsigned long int N = 1E8;
	clock_t t1, t2;

	str = malloc(N);
	test1 = malloc(N);
	test2 = malloc(N);
	test3 = malloc(N);

	for (n = 0; n < N; ++n)
	{
		random = rand() % 255;
		str[n] = (char)random;
	}

	t1 = clock();
	for (n = 0; n < N; ++n)
		test1[n] = lower1(str[n]);
	t2 = clock();
	printf("Test 1:  %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0; n < N; ++n)
        test2[n] = lower2(str[n]);
    t2 = clock();
    printf("Test 2:  %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0; n < N; ++n)
        test3[n] = tolower(str[n]);
    t2 = clock();
    printf("tolower: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);


	max1 = 0.0;
	max2 = 0.0;
	for (n = 0U; n < N; ++n)
	{
		temp = (double)test1[n] - (double)test3[n];
		if (temp < 0.0)
			temp = -temp;

		if (max1 < temp)
			max1 = temp;

        temp = (double)test2[n] - (double)test3[n];
        if (temp < 0.0)
            temp = -temp;

        if (max2 < temp)
            max2 = temp;

	}

	printf("Max Errors:\n\t%f\n\t%f\n", max1, max2);

	free(test1);
	free(test2);
	free(test3);
	return 0;
}

