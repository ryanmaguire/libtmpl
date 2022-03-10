#include <libtmppl/include/tmppl_complex.hpp>

/******************************************************************************
 *  Function:                                                                 *
 *      complex                                                               *
 *  Purpose:                                                                  *
 *      Empty constructor for complex class.                                  *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 ******************************************************************************/
tmppl::complexf::complexf(void)
{
    return;
}

tmppl::complex::complex(void)
{
    return;
}

tmppl::complexl::complexl(void)
{
    return;
}

/******************************************************************************
 *  Function:                                                                 *
 *      complex                                                               *
 *  Purpose:                                                                  *
 *      Constructor for the complex class from two real numbers. The output   *
 *      is the complex number z = real + i*imag.                              *
 *  Arguments:                                                                *
 *      real (double):                                                        *
 *          The real part of the complex number.                              *
 *      imag (double):                                                        *
 *          The imag part of the complex number.                              *
 ******************************************************************************/
tmppl::complexf::complexf(float real, float imag)
{
    data = tmpl_CFloat_Rect(real, imag);
}

tmppl::complex::complex(double real, double imag)
{
    data = tmpl_CDouble_Rect(real, imag);
}

tmppl::complexl::complexl(long double real, long double imag)
{
    data = tmpl_CLDouble_Rect(real, imag);
}

/******************************************************************************
 *  Function:                                                                 *
 *      complex                                                               *
 *  Purpose:                                                                  *
 *      Constructor for the complex class from a tmpl_ComplexDouble, which is *
 *      the C struct for complex numbers in libtmpl.                          *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 ******************************************************************************/
tmppl::complexf::complexf(tmpl_ComplexFloat z)
{
    data = z;
}

tmppl::complex::complex(tmpl_ComplexDouble z)
{
    data = z;
}

tmppl::complexl::complexl(tmpl_ComplexLongDouble z)
{
    data = z;
}

/******************************************************************************
 *  Function:                                                                 *
 *      real_part                                                             *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the real part of    *
 *      the complex number.                                                   *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      re (double):                                                          *
 *          The real part of the complex number.                              *
 ******************************************************************************/
float tmppl::complexf::real_part(void) const
{
    return tmpl_CFloat_Real_Part(data);
}

double tmppl::complex::real_part(void) const
{
    return tmpl_CDouble_Real_Part(data);
}

long double tmppl::complexl::real_part(void) const
{
    return tmpl_CLDouble_Real_Part(data);
}

/******************************************************************************
 *  Function:                                                                 *
 *      imag_part                                                             *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the imaginary part  *
 *      of the complex number.                                                *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      im (double):                                                          *
 *          The imaginary part of the complex number.                         *
 ******************************************************************************/
float tmppl::complexf::imag_part(void) const
{
    return tmpl_CFloat_Imag_Part(data);
}

double tmppl::complex::imag_part(void) const
{
    return tmpl_CDouble_Imag_Part(data);
}

long double tmppl::complexl::imag_part(void) const
{
    return tmpl_CLDouble_Imag_Part(data);
}

/******************************************************************************
 *  Function:                                                                 *
 *      abs                                                                   *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the absolute value  *
 *      of the complex number.                                                *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      abs (double):                                                         *
 *          The absolute value of the complex number.                         *
 ******************************************************************************/
float tmppl::complexf::abs(void) const
{
    return tmpl_CFloat_Abs(data);
}

double tmppl::complex::abs(void) const
{
    return tmpl_CDouble_Abs(data);
}

long double tmppl::complexl::abs(void) const
{
    return tmpl_CLDouble_Abs(data);
}

/******************************************************************************
 *  Function:                                                                 *
 *      arg                                                                   *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the complex         *
 *      argument of the complex number.                                       *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      abs (double):                                                         *
 *          The absolute value of the complex number.                         *
 ******************************************************************************/
float tmppl::complexf::arg(void) const
{
    return tmpl_CFloat_Argument(data);
}

double tmppl::complex::arg(void) const
{
    return tmpl_CDouble_Argument(data);
}

long double tmppl::complexl::arg(void) const
{
    return tmpl_CLDouble_Argument(data);
}

/******************************************************************************
 *  Function:                                                                 *
 *      abs_squared                                                           *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the square of the   *
 *      absolute value of the complex number.                                 *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      abs_sq (double):                                                      *
 *          The square of the absolute value of the complex number.           *
 ******************************************************************************/
float tmppl::complexf::abs_squared(void) const
{
    return tmpl_CFloat_Abs_Squared(data);
}

double tmppl::complex::abs_squared(void) const
{
    return tmpl_CDouble_Abs_Squared(data);
}

long double tmppl::complexl::abs_squared(void) const
{
    return tmpl_CLDouble_Abs_Squared(data);
}

/******************************************************************************
 *  Function:                                                                 *
 *      conjugate                                                             *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the conjugate       *
 *      of the complex number.                                                *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      conj (complex):                                                       *
 *          The conjugate of the given complex number.                        *
 ******************************************************************************/
tmppl::complexf tmppl::complexf::conjugate(void) const
{
    return complexf(tmpl_CFloat_Conjugate(data));
}

tmppl::complex tmppl::complex::conjugate(void) const
{
    return complex(tmpl_CDouble_Conjugate(data));
}

tmppl::complexl tmppl::complexl::conjugate(void) const
{
    return complexl(tmpl_CLDouble_Conjugate(data));
}

/******************************************************************************
 *  Function:                                                                 *
 *      dist                                                                  *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the distance        *
 *      to another complex number.                                            *
 *  Arguments:                                                                *
 *      w (tmppl::complex).                                                   *
 *  Output:                                                                   *
 *      dist (double):                                                        *
 *          The Euclidean distance to the complex number w.                   *
 ******************************************************************************/
float tmppl::complexf::dist(const tmppl::complexf &w) const
{
    return tmpl_CFloat_Dist(data, w.data);
}

double tmppl::complex::dist(const tmppl::complex &w) const
{
    return tmpl_CDouble_Dist(data, w.data);
}

long double tmppl::complexl::dist(const tmppl::complexl &w) const
{
    return tmpl_CLDouble_Dist(data, w.data);
}

/******************************************************************************
 *  Function:                                                                 *
 *      dist_squared                                                          *
 *  Purpose:                                                                  *
 *      Method for the tmppl::complex class for computing the squared of the  *
 *      distance to another complex number.                                   *
 *  Arguments:                                                                *
 *      w (tmppl::complex).                                                   *
 *  Output:                                                                   *
 *      dist (double):                                                        *
 *          The Euclidean distance to the complex number w.                   *
 ******************************************************************************/
float tmppl::complexf::dist_squared(const tmppl::complexf &w) const
{
    return tmpl_CFloat_Dist_Squared(data, w.data);
}

double tmppl::complex::dist_squared(const tmppl::complex &w) const
{
    return tmpl_CDouble_Dist_Squared(data, w.data);
}

long double tmppl::complexl::dist_squared(const tmppl::complexl &w) const
{
    return tmpl_CLDouble_Dist_Squared(data, w.data);
}

/******************************************************************************
 *  Function:                                                                 *
 *      reciprocal                                                            *
 *  Purpose:                                                                  *
 *      Computes the complex reciprocal of the complex number, 1/z = z^-1.    *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      rcpr (tmppl::complex):                                                *
 *          The reciprocal of the complex number.                             *
 ******************************************************************************/
tmppl::complexf tmppl::complexf::reciprocal(void) const
{
    return complexf(tmpl_CFloat_Reciprocal(data));
}

tmppl::complex tmppl::complex::reciprocal(void) const
{
    return complex(tmpl_CDouble_Reciprocal(data));
}

tmppl::complexl tmppl::complexl::reciprocal(void) const
{
    return complexl(tmpl_CLDouble_Reciprocal(data));
}

/******************************************************************************
 *  Operator:                                                                 *
 *      Addition                                                              *
 *  Purpose:                                                                  *
 *      Computes the complex sum of two complex numbers.                      *
 *  Arguments:                                                                *
 *      z (const tmppl::complex &):                                           *
 *          Reference to the first complex number.                            *
 *      w (const tmppl::complex &):                                           *
 *          Reference to the second complex number.                           *
 *  Output:                                                                   *
 *      sum (tmppl::complex):                                                 *
 *          The sum of z and w.                                               *
 ******************************************************************************/
tmppl::complexf operator + (const tmppl::complexf &z, const tmppl::complexf &w)
{
    return tmppl::complexf(tmpl_CFloat_Add(z.data, w.data));
}

tmppl::complex operator + (const tmppl::complex &z, const tmppl::complex &w)
{
    return tmppl::complex(tmpl_CDouble_Add(z.data, w.data));
}

tmppl::complexl operator + (const tmppl::complexl &z, const tmppl::complexl &w)
{
    return tmppl::complexl(tmpl_CLDouble_Add(z.data, w.data));
}

/******************************************************************************
 *  Operator:                                                                 *
 *      Addition                                                              *
 *  Purpose:                                                                  *
 *      Computes the complex sum of complex and real numbers.                 *
 *  Arguments:                                                                *
 *      x (const double &):                                                   *
 *          Reference to the real number.                                     *
 *      z (const tmppl::complex &):                                           *
 *          Reference to the complex number.                                  *
 *  Output:                                                                   *
 *      sum (tmppl::complex):                                                 *
 *          The sum of x and z.                                               *
 ******************************************************************************/
tmppl::complexf operator + (const float &x, const tmppl::complexf &z)
{
    return tmppl::complexf(tmpl_CFloat_Add_Real(x, z.data));
}

tmppl::complex operator + (const double &x, const tmppl::complex &z)
{
    return tmppl::complex(tmpl_CDouble_Add_Real(x, z.data));
}

tmppl::complexl operator + (const long double &x, const tmppl::complexl &z)
{
    return tmppl::complexl(tmpl_CLDouble_Add_Real(x, z.data));
}

/******************************************************************************
 *  Operator:                                                                 *
 *      Addition                                                              *
 *  Purpose:                                                                  *
 *      Computes the complex sum of complex and real numbers.                 *
 *  Arguments:                                                                *
 *      z (const tmppl::complex &):                                           *
 *          Reference to the complex number.                                  *
 *      x (const double &):                                                   *
 *          Reference to the real number.                                     *
 *  Output:                                                                   *
 *      sum (tmppl::complex):                                                 *
 *          The sum of x and z.                                               *
 ******************************************************************************/
tmppl::complexf operator + (const tmppl::complexf &z, const float &x)
{
    return tmppl::complexf(tmpl_CFloat_Add_Real(x, z.data));
}

tmppl::complex operator + (const tmppl::complex &z, const double &x)
{
    return tmppl::complex(tmpl_CDouble_Add_Real(x, z.data));
}

tmppl::complexl operator + (const tmppl::complexl &z, const long double &x)
{
    return tmppl::complexl(tmpl_CLDouble_Add_Real(x, z.data));
}

/******************************************************************************
 *  Operator:                                                                 *
 *      Multiplication                                                        *
 *  Purpose:                                                                  *
 *      Computes the complex product of two complex numbers.                  *
 *  Arguments:                                                                *
 *      z (const tmppl::complex &):                                           *
 *          Reference to the first complex number.                            *
 *      w (const tmppl::complex &):                                           *
 *          Reference to the second complex number.                           *
 *  Output:                                                                   *
 *      prod (tmppl::complex):                                                *
 *          The product of z and w.                                           *
 ******************************************************************************/
tmppl::complexf operator * (const tmppl::complexf &z, const tmppl::complexf &w)
{
    return tmppl::complexf(tmpl_CFloat_Multiply(z.data, w.data));
}

tmppl::complex operator * (const tmppl::complex &z, const tmppl::complex &w)
{
    return tmppl::complex(tmpl_CDouble_Multiply(z.data, w.data));
}

tmppl::complexl operator * (const tmppl::complexl &z, const tmppl::complexl &w)
{
    return tmppl::complexl(tmpl_CLDouble_Multiply(z.data, w.data));
}

/******************************************************************************
 *  Operator:                                                                 *
 *      Multiplication                                                        *
 *  Purpose:                                                                  *
 *      Computes the complex product of complex and real numbers.             *
 *  Arguments:                                                                *
 *      x (const double &):                                                   *
 *          Reference to the real number.                                     *
 *      z (const tmppl::complex &):                                           *
 *          Reference to the complex number.                                  *
 *  Output:                                                                   *
 *      prod (tmppl::complex):                                                *
 *          The product of x and z.                                           *
 ******************************************************************************/
tmppl::complexf operator * (const float &x, const tmppl::complexf &z)
{
    return tmppl::complexf(tmpl_CFloat_Multiply_Real(x, z.data));
}

tmppl::complex operator * (const double &x, const tmppl::complex &z)
{
    return tmppl::complex(tmpl_CDouble_Multiply_Real(x, z.data));
}

tmppl::complexl operator * (const long double &x, const tmppl::complexl &z)
{
    return tmppl::complexl(tmpl_CLDouble_Multiply_Real(x, z.data));
}

/******************************************************************************
 *  Operator:                                                                 *
 *      Multiplication                                                        *
 *  Purpose:                                                                  *
 *      Computes the complex product of complex and real numbers.             *
 *  Arguments:                                                                *
 *      z (const tmppl::complex &):                                           *
 *          Reference to the complex number.                                  *
 *      x (const double &):                                                   *
 *          Reference to the real number.                                     *
 *  Output:                                                                   *
 *      prod (tmppl::complex):                                                *
 *          The product of x and z.                                           *
 ******************************************************************************/
tmppl::complexf operator * (const tmppl::complexf &z, const float &x)
{
    return tmppl::complexf(tmpl_CFloat_Multiply_Real(x, z.data));
}

tmppl::complex operator * (const tmppl::complex &z, const double &x)
{
    return tmppl::complex(tmpl_CDouble_Multiply_Real(x, z.data));
}

tmppl::complexl operator * (const tmppl::complexl &z, const long double &x)
{
    return tmppl::complexl(tmpl_CLDouble_Multiply_Real(x, z.data));
}
