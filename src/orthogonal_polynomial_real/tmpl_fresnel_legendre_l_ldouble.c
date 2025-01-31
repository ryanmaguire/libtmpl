/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                      tmpl_fresnel_legendre_l_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the evaluation of the Fresnel-Legendre polynomials.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cast.h:                                                          *
 *          Header file providing helper macros for casting in C vs. C++.     *
 *  2.) tmpl_orthogonal_polynomial_real.h:                                    *
 *          Header file with the functions prototype.                         *
 *  3.) stddef.h:                                                             *
 *          Standard library header file providing the size_t data type.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 13, 2024                                             *
 ******************************************************************************/

/*  Helper macro providing casting for C vs. C++ styles.                      */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_orthogonal_polynomial_real.h>

/*  Standard library header file. The size_t type is found here.              */
#include <stddef.h>

/*  Computes the Fresnel-Legendre polynomials L_n(alpha, beta).               */
void
tmpl_LDouble_Fresnel_Legendre_L(long double * const evals,
                                long double alpha,
                                long double beta,
                                size_t length)
{
    /*  Cast some constant values to size_t, avoiding implicit conversion.    */
    const size_t zero = TMPL_CAST(0, size_t);

    /*  Declare necessary variables. C89 requires declarations at the top of  *
     *  a block. n is used for indexing the Chebyshev polynomials.            */
    size_t n;

    /*  These are used for the recursive formulas for Legendre P and          *
     *  Chebyshev U.                                                          */
    long double Pn, Pn1, Un, Un1;

    /*  Check for NULL pointers and empty arrays. Nothing to do in this case. */
    if (!evals || length == zero)
        return;

    /*  Start the computation. Use the formulas for P_n and U_n for small n.  */
    Pn = 1.0L;
    Pn1 = alpha;
    Un = 1.0L;
    Un1 = 2.0L * alpha;

    /*  Start the upwards iterative loop.                                     */
    for (n = zero; n < length; ++n)
    {
        /*  Cast to long double to prevent implicit conversions.              */
        const long double ind = TMPL_CAST(n, long double);
        const long double rcpr = 1.0L / (ind + 2.0L);

        /*  Compute the next Legendre and Chebyshev polynomials.              */
        const long double Pn2 = ((2.0L*ind+3.0L)*alpha*Pn1-(ind+1.0L)*Pn)*rcpr;
        const long double Un2 = 2.0L * alpha * Un1 - Un;

        /*  Use the definition of the Fresnel-Legendre polynomials to compute.*/
        const long double left = (Pn - alpha*Pn1) * rcpr;
        const long double right = Un2 - 2.0L*Pn2;
        evals[n] = left - beta * right;

        /*  Reset the Legendre and Chebyshev polynomials for the next index.  */
        Pn = Pn1;
        Pn1 = Pn2;
        Un = Un1;
        Un1 = Un2;
    }
}
