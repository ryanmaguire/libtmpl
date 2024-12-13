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
 *                       tmpl_fresnel_legendre_l_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the evaluation of the Fresnel-Legendre polynomials.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_compat_cast.h:                                                   *
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
#include <libtmpl/include/tmpl_compat_cast.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_orthogonal_polynomial_real.h>

/*  Standard library header file. The size_t type is found here.              */
#include <stddef.h>

/*  Computes the Fresnel-Legendre polynomials L_n(alpha, beta).               */
void
tmpl_Double_Fresnel_Legendre_L(double * const evals,
                               double alpha,
                               double beta,
                               size_t length)
{
    /*  Cast some constant values to size_t, avoiding implicit conversion.    */
    const size_t zero = TMPL_CAST(0, size_t);

    /*  Declare necessary variables. C89 requires declarations at the top of  *
     *  a block. n is used for indexing the Chebyshev polynomials.            */
    size_t n;

    /*  These are used for the recursive formulas for Legendre P and          *
     *  Chebyshev U.                                                          */
    double alpha_squared, Pn, Pn1, Pn2, Un, Un1, Un2;

    /*  Check for NULL pointers and empty arrays. Nothing to do in this case. */
    if (!evals || length == zero)
        return;

    /*  Start the computation. Use the formulas for P_n and U_n for small n.  */
    alpha_squared = alpha * alpha;

    Pn = 1.0;
    Pn1 = alpha;
    Pn2 = 0.5 * (3.0 * alpha_squared - 1.0);

    Un = 1.0;
    Un1 = 2.0 * alpha;
    Un2 = 4.0 * alpha_squared - 1.0;

    /*  Start the upwards iterative loop.                                     */
    for (n = zero; n < length; ++n)
    {
        /*  Cast to double to prevent implicit conversions.                   */
        const double index = TMPL_CAST(index, double);

        /*  Use the definition of the Fresnel-Legendre polynomials to compute.*/
        const double left = (Pn - alpha*Pn1) / (index + 2.0);
        const double right = Un2 - 2.0*Pn2;
        evals[n] = left - beta * right;

        /*  Compute the next set of Chebysev and Legendre polynomials.        */
        Pn = Pn1;
        Pn1 = Pn2;
        Pn2 = ((2.0*index - 1.0) * alpha * Pn1 - (index - 1.0) * Pn) / index;

        Un = Un1;
        Un1 = Un2;
        Un2 = 2.0 * alpha * Un1 - Un;
    }
}
