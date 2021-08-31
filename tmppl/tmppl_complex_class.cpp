#include "tmppl_complex.hpp"

/******************************************************************************
 *  Function:                                                                 *
 *      complex                                                               *
 *  Purpose:                                                                  *
 *      Empty constructor for (double precision) complex class.               *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 ******************************************************************************/
tmppl::complex::complex(void)
{
    return;
}

/******************************************************************************
 *  Function:                                                                 *
 *      complex                                                               *
 *  Purpose:                                                                  *
 *      Constructor for the (double precision) complex class from two         *
 *      doubles. The number real + i*imag is given.                           *
 *  Arguments:                                                                *
 *      real (double):                                                        *
 *          The real part of the complex number.                              *
 *      imag (double):                                                        *
 *          The imag part of the complex number.                              *
 ******************************************************************************/
tmppl::complex::complex(double real, double imag)
{
    data = tmpl_CDouble_Rect(real, imag);
}

/******************************************************************************
 *  Function:                                                                 *
 *      complex                                                               *
 *  Purpose:                                                                  *
 *      Constructor for the (double precision) complex class from a           *
 *      tmpl_ComplexDouble, which is the C struct for complex numbers in      *
 *      libtmpl.                                                              *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 ******************************************************************************/
tmppl::complex::complex(tmpl_Complex z)
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
double tmppl::complex::real_part(void)
{
    return tmpl_CDouble_Real_Part(data);
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
double tmppl::complex::imag_part(void)
{
    return tmpl_CDouble_Imag_Part(data);
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
double tmppl::complex::abs(void)
{
    return tmpl_CDouble_Abs(data);
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
double tmppl::complex::arg(void)
{
    return tmpl_CDouble_Argument(data);
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
double tmppl::complex::abs_squared(void)
{
    return tmpl_CDouble_Abs_Squared(data);
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
tmppl::complex tmppl::complex::conjugate(void)
{
    tmppl::complex conj;
    return complex(tmpl_CDouble_Conjugate(data));
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
double tmppl::complex::dist(tmppl::complex w)
{
    return tmpl_CDouble_Dist(data, w.data);
}

tmppl::complex tmppl::complex::reciprocal(void)
{
    tmppl::complex conj;
    return complex(tmpl_CDouble_Reciprocal(data));
}

tmppl::complex tmppl::complex::operator +(tmppl::complex w)
{
    tmpl_Complex sum = tmpl_CDouble_Add(data, w.data);
    return tmppl::complex(sum);
}

tmppl::complex tmppl::complex::operator -(tmppl::complex w)
{
    tmpl_Complex diff = tmpl_CDouble_Subtract(data, w.data);
    return tmppl::complex(diff);
}

tmppl::complex tmppl::complex::operator *(tmppl::complex w)
{
    tmpl_Complex prod = tmpl_CDouble_Multiply(w.data, data);
    return tmppl::complex(prod);
}

tmppl::complex tmppl::complex::operator /(tmppl::complex w)
{
    tmpl_Complex quot = tmpl_CDouble_Multiply(data, w.data);
    return tmppl::complex(quot);
}

tmppl::complex tmppl::complex::operator +(double x)
{
    tmpl_Complex sum = tmpl_CDouble_Add_Real(x, data);
    return tmppl::complex(sum);
}

tmppl::complex tmppl::complex::operator *(double x)
{
    tmpl_Complex prod = tmpl_CDouble_Multiply_Real(x, data);
    return tmppl::complex(prod);
}

tmppl::complex operator - (double x, tmppl::complex z)
{
    tmpl_Complex diff = tmpl_CDouble_Subtract_Real(x, z.data);
    return tmppl::complex(diff);
}

tmppl::complex operator - (tmppl::complex z, double x)
{
    tmpl_Complex diff = tmpl_CDouble_Add_Real(-x, z.data);
    return tmppl::complex(diff);
}

