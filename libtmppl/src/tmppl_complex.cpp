#include <libtmppl/include/tmppl_complex.hpp>

/******************************************************************************
 *  Function:                                                                 *
 *      cos                                                                   *
 *  Purpose:                                                                  *
 *      Compute complex cosine at single, double, and long double precision.  *
 *  Arguments:                                                                *
 *      z (const tmppl::complex &):                                           *
 *          Reference to a complex number.                                    *
 *  Output:                                                                   *
 *      cos_z (tmppl::complex):                                               *
 *          The complex cosine of z.                                          *
 ******************************************************************************/
tmppl::complex tmppl::cos(const tmppl::complex &z)
{
    return tmppl::complex(tmpl_CDouble_Cos(z.data));
}

tmppl::complexf tmppl::cos(const tmppl::complexf &z)
{
    return tmppl::complexf(tmpl_CFloat_Cos(z.data));
}

tmppl::complexl tmppl::cos(const tmppl::complexl &z)
{
    return tmppl::complexl(tmpl_CLDouble_Cos(z.data));
}

/******************************************************************************
 *  Function:                                                                 *
 *      exp                                                                   *
 *  Purpose:                                                                  *
 *      Compute complex exp at single, double, and long double precision.     *
 *  Arguments:                                                                *
 *      z (const tmppl::complex &):                                           *
 *          Reference to a complex number.                                    *
 *  Output:                                                                   *
 *      sin_z (tmppl::complex):                                               *
 *          The complex exponential of z.                                     *
 ******************************************************************************/
tmppl::complex tmppl::exp(const tmppl::complex &z)
{
    return tmppl::complex(tmpl_CDouble_Exp(z.data));
}

tmppl::complexf tmppl::exp(const tmppl::complexf &z)
{
    return tmppl::complexf(tmpl_CFloat_Exp(z.data));
}

tmppl::complexl tmppl::exp(const tmppl::complexl &z)
{
    return tmppl::complexl(tmpl_CLDouble_Exp(z.data));
}

/******************************************************************************
 *  Function:                                                                 *
 *      sin                                                                   *
 *  Purpose:                                                                  *
 *      Compute complex sine at single, double, and long double precision.    *
 *  Arguments:                                                                *
 *      z (const tmppl::complex &):                                           *
 *          Reference to a complex number.                                    *
 *  Output:                                                                   *
 *      sin_z (tmppl::complex):                                               *
 *          The complex sine of z.                                            *
 ******************************************************************************/
tmppl::complex tmppl::sin(const tmppl::complex &z)
{
    return tmppl::complex(tmpl_CDouble_Sin(z.data));
}

tmppl::complexf tmppl::sin(const tmppl::complexf &z)
{
    return tmppl::complexf(tmpl_CFloat_Sin(z.data));
}

tmppl::complexl tmppl::sin(const tmppl::complexl &z)
{
    return tmppl::complexl(tmpl_CLDouble_Sin(z.data));
}
