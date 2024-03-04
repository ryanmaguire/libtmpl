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
 *                            tmpl_erf_pade_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (11, 10) Pade approximant of erf(x) at single precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Erf_Pade                                                   *
 *  Purpose:                                                                  *
 *      Computes the (7, 7) Pade approximant of erf(x) for small values x.    *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (float):                                                        *
 *          The error function erf(x).                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator and *
 *      denominator and return the rational function.                         *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 2.0 this is accurate to     *
 *      single precision.                                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_PADE_FLOAT_H
#define TMPL_ERF_PADE_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.1283791670955125738961589031215451716881012586580E+00F)
#define P01 (+1.4818344063622780648342508702687944404683762561658E-01F)
#define P02 (+4.9924515951700559030923055366106572085194252460456E-02F)
#define P03 (+2.5542683116294123224523728554057939689697321765778E-03F)
#define P04 (+3.5159126889323369538530721617592927869120131247252E-04F)
#define P05 (+6.3968493537305666510839691625610269064041214907076E-06F)
#define P06 (+4.2391052201764321880410308183667912471500726077075E-07F)
#define P07 (-6.8312621277962615664103751011667686946939609696285E-10F)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define Q01 (+4.6465748833138878611077963125758807376362120281839E-01F)
#define Q02 (+9.9130279720389021662366403714090648829651188573290E-02F)
#define Q03 (+1.2650862902444679402704568324809211538196047041335E-02F)
#define Q04 (+1.0491598800933787566943652530599815000353683156682E-03F)
#define Q05 (+5.6931167136833231335515366869543358375478850596229E-05F)
#define Q06 (+1.8869318196202652890928992053529215307601298261577E-06F)
#define Q07 (+2.9758499105344790840008255369044528307245541372743E-08F)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
#define TMPL_NUM_EVAL(z) \
P00 + z*(P01 + z*(P02 + z*(P03 + z*(P04 + z*(P05 + z*(P06 + z*P07))))))

#define TMPL_DEN_EVAL(z) \
Q00 + z*(Q01 + z*(Q02 + z*(Q03 + z*(Q04 + z*(Q05 + z*(Q06 + z*Q07))))))

/*  Function for computing the (11, 10) Pade approximant of erf(x).           */
TMPL_STATIC_INLINE
float tmpl_Float_Erf_Pade(float x)
{
    /*  Both polynomials are even. Computing x^2 and work with that.          */
    const float x2 = x*x;

    /*  Compute the two polynomials using Horner's method.                    */
    const float num = TMPL_NUM_EVAL(x2);
    const float den = TMPL_DEN_EVAL(x2);

    /*  The rational function approximates erf(x)/x. Return x*num/den.        */
    return x*num/den;
}
/*  End of tmpl_Float_Erf_Pade.                                               */

/*  #undef everything in case someone wants to #include this file.            */
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of include guard.                                                     */
