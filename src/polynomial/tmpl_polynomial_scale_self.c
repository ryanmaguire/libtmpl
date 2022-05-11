


/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function declared here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Rational numbers found here.                                              */
#include <libtmpl/include/tmpl_rational.h>

/*  Complex numbers found here.                                               */
#include <libtmpl/include/tmpl_complex.h>

/*  Function prototypes are given here.                                       */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and calloc are found here.                                         */
#include <stdlib.h>

/*  Make sure this macro name is available. It should be anyways.             */
#ifdef TMPL_POLYSCALE
#undef TMPL_POLYSCALE
#endif

/******************************************************************************
 *  Macro for giving the definition of the free functions for Z/Q/R/C[x].     *
 *  Arguments:                                                                *
 *      ptype:                                                                *
 *          The data type of the polynomial (the polynomial's typedef).       *
 *      ctype:                                                                *
 *          Type of the value we're scaling by.                               *
 *      fname:                                                                *
 *          The name of the function the macro defines.                       *
 ******************************************************************************/
#define TMPL_POLYSCALE(ptype, ctype, fname)                                    \
                                                                               \
/*  Function for freeing all memory for a polynomial.                        */\
void fname(ptype *poly, ctype scale)                                           \
{                                                                              \
    /*  Variable for indexing over the coeffs array.                         */\
    unsigned long int n;                                                       \
    if (poly == NULL)                                                          \
        return;                                                                \
                                                                               \
    /*  Given a NULL coeffs pointer, zero coefficients, or a polynomial with */\
    /*  the error_occurred Boolean set to true, do nothing and return.       */\
    if (!poly->coeffs || poly->number_of_coeffs == 0UL || poly->error_occurred)\
        return;                                                                \
                                                                               \
    /*  Loop over the coeffs array and perform the scale.                    */\
    for (n = 0UL; n < poly->number_of_coeffs; ++n)                             \
        TMPL_SCALE_FUNC(poly->coeffs[n], scale);                               \
                                                                               \
    return;                                                                    \
}
/*  End of TMPL_POLYSCALE.                                                    */

#define TMPL_SCALE_FUNC(a, b) a *= b
TMPL_POLYSCALE(tmpl_PolynomialZ, signed long int, tmpl_PolynomialZ_ScaleSelf)
#undef TMPL_SCALE_FUNC

/*  Undefine the macro in case someone wants to #include this file directly.  */
#undef TMPL_POLYSCALE
