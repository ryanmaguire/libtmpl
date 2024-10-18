#include <stdio.h>
#include <math.h>
#include <libtmpl/include/tmpl_math.h>

int main(void)
{
	const double x = 5.3193726483265414167072966566735410838135E+255;
	const double y = cos(x);
	const double z = tmpl_Double_Cos(x);
	const double err = fabs((y - z) / z);
	printf("%+.40E\n%+.40E\n%+.40E\n", y, z, err);
	return 0;
}
