
#include <libtmpl/include/tmpl_complex.h>

namespace tmppl {

    class complexf {
        public:
            tmpl_ComplexFloat data;
            complexf(void);
            complexf(float real, float imag);
            complexf(tmpl_ComplexFloat z);
            float real_part(void);
            float imag_part(void);
            float abs(void);
            float abs_squared(void);
            complexf operator +(complexf w);
            complexf operator -(complexf w);
            complexf operator *(complexf w);
            complexf operator /(complexf w);
    };

    class complex {
        public:
            tmpl_ComplexDouble data;

            /*  Empty constructor.                                            */
            complex(void);

            /*  Constructor from two reals. Outputs z = real + i*imag.        */
            complex(double real, double imag);

            /*  Constructor from a tmpl_ComplexDouble struct.                 */
            complex(tmpl_ComplexDouble z);

            /*  Computes the absolute value of the complex number.            */
            double abs(void);

            /*  Computes the square of the absolute value of the number.      */
            double abs_squared(void);

            /*  Computes the argument of the complex number.                  */
            double arg(void);

            /*  Computes the complex conjugate of the complex number.         */
            complex conjugate(void);

            /*  Computes the Euclidean distance to another complex number.    */
            double dist(complex w);

            /*  Computes the square of the distance to another complex number.*/
            double dist_squared(complex w);

            /*  Returns the imaginary part of the complex number.             */
            double imag_part(void);

            /*  Returns the real part of the complex number.                  */
            double real_part(void);

            /*  Computes the reciprocal of the complex number, 1 / z.         */
            complex reciprocal(void);
            complex operator +(complex w);
            complex operator -(complex w);
            complex operator *(complex w);
            complex operator /(complex w);
            complex operator +(double x);
            complex operator *(double x);
    };

    class complexl {
        public:
            tmpl_ComplexLongDouble data;
            complexl(void);
            complexl(long double real, long double imag);
            complexl(tmpl_ComplexLongDouble z);
            long double real_part(void);
            long double imag_part(void);
            long double abs(void);
            long double abs_squared(void);
            complexl operator +(complexl w);
            complexl operator -(complexl w);
            complexl operator *(complexl w);
            complexl operator /(complexl w);
    };

    complex cos(complex z);
    complex exp(complex z);
    complex sin(complex z);
}

tmppl::complex operator - (double x, tmppl::complex z);
tmppl::complex operator - (tmppl::complex z, double x);
