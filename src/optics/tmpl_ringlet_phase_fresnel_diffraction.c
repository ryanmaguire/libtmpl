/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of rss_ringoccs.                                        *
 *                                                                            *
 *  rss_ringoccs is free software: you can redistribute it and/or modify it   *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  rss_ringoccs is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with rss_ringoccs.  If not, see <https://www.gnu.org/licenses/>.    *
 ******************************************************************************
 *                  rss_ringoccs_gap_fresnel_diffraction                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the Fresnel diffraction of a gap.        *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_math.h:                                                  *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 *  2.) rss_ringoccs_complex.h:                                               *
 *          Header file where rssringoccs_ComplexDouble is defined, as well   *
 *          as the prototype for rssringoccs_Complex_Cos.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       November 27, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/27 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  The Fresnel integrals are found here.                                     */
#include <libtmpl/include/tmpl_special_functions.h>

/*  Header file containing the prototypes for the functions.                  */
#include <libtmpl/include/tmpl_optics.h>

/******************************************************************************
 *  Function:                                                                 *
 *      Ringlet_Diffraction_Phase_Float                                       *
 *  Purpose:                                                                  *
 *      Compute the phase from the diffraction pattern of a square well.      *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          The location on the x-axis for the point being computed.          *
 *      a (float):                                                            *
 *          The left-most endpoint of the ringlet.                            *
 *      b (float):                                                            *
 *          The right-most endpoint of the ringlet.                           *
 *      F (float):                                                            *
 *          The Fresnel scale.                                                *
 *  Notes:                                                                    *
 *      1.) This function relies on the C99 standard, or higher.              *
 ******************************************************************************/
float
tmpl_Float_Ringlet_Diffraction_Phase(float x, float a, float b, float F)
{
    float re, im, arg1, arg2, fs1, fs2, fc1, fc2, out;

    arg1 = tmpl_Sqrt_Pi_By_Two_F*(a-x)/F;
    arg2 = tmpl_Sqrt_Pi_By_Two_F*(b-x)/F;

    fs1 = tmpl_Float_Fresnel_Sin(arg1);
    fs2 = tmpl_Float_Fresnel_Sin(arg2);
    fc1 = tmpl_Float_Fresnel_Cos(arg1);
    fc2 = tmpl_Float_Fresnel_Cos(arg2);

    im = tmpl_Sqrt_One_By_Two_Pi_F * (fs2 - fs1 -  fc2 + fc1);
    re = 1.0F - tmpl_Sqrt_One_By_Two_Pi_F * (fc2 - fc1 + fs2 - fs1);
    out = tmpl_Float_Arctan2(im, re);

    return out;
}

/******************************************************************************
 *  Function:                                                                 *
 *      Ringlet_Diffraction_Phase_Double                                      *
 *  Purpose:                                                                  *
 *      Compute the phase from the diffraction pattern of a square well.      *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          The location on the x-axis for the point being computed.          *
 *      a (float):                                                            *
 *          The left-most endpoint of the ringlet.                            *
 *      b (float):                                                            *
 *          The right-most endpoint of the ringlet.                           *
 *      F (float):                                                            *
 *          The Fresnel scale.                                                *
 *  Notes:                                                                    *
 *      1.) This function relies on the C99 standard, or higher.              *
 ******************************************************************************/
double
tmpl_Double_Ringlet_Diffraction_Phase(double x, double a, double b, double F)
{
    double re, im, arg1, arg2, fs1, fs2, fc1, fc2, out;

    arg1 = tmpl_Sqrt_Pi_By_Two*(a-x)/F;
    arg2 = tmpl_Sqrt_Pi_By_Two*(b-x)/F;

    fs1 = tmpl_Double_Fresnel_Sin(arg1);
    fs2 = tmpl_Double_Fresnel_Sin(arg2);
    fc1 = tmpl_Double_Fresnel_Cos(arg1);
    fc2 = tmpl_Double_Fresnel_Cos(arg2);

    im = tmpl_Sqrt_One_By_Two_Pi * (fs2 - fs1 -  fc2 + fc1);
    re = 1.0 - tmpl_Sqrt_One_By_Two_Pi * (fc2 - fc1 + fs2 - fs1);
    out = tmpl_Double_Arctan2(im, re);

    return out;
}

/******************************************************************************
 *  Function:                                                                 *
 *      Ringlet_Diffraction_Phase_Long_Double                                 *
 *  Purpose:                                                                  *
 *      Compute the phase from the diffraction pattern of a square well.      *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          The location on the x-axis for the point being computed.          *
 *      a (float):                                                            *
 *          The left-most endpoint of the ringlet.                            *
 *      b (float):                                                            *
 *          The right-most endpoint of the ringlet.                           *
 *      F (float):                                                            *
 *          The Fresnel scale.                                                *
 *  Notes:                                                                    *
 *      1.) This function relies on the C99 standard, or higher.              *
 ******************************************************************************/
long double
tmpl_LDouble_Ringlet_Diffraction_Phase(long double x, long double a,
                                       long double b, long double F)
{
    long double re, im, arg1, arg2, fs1, fs2, fc1, fc2, out;

    arg1 = tmpl_Sqrt_Pi_By_Two_L*(a-x)/F;
    arg2 = tmpl_Sqrt_Pi_By_Two_L*(b-x)/F;

    fs1 = tmpl_LDouble_Fresnel_Sin(arg1);
    fs2 = tmpl_LDouble_Fresnel_Sin(arg2);
    fc1 = tmpl_LDouble_Fresnel_Cos(arg1);
    fc2 = tmpl_LDouble_Fresnel_Cos(arg2);

    im = tmpl_Sqrt_One_By_Two_Pi_L * (fs2 - fs1 -  fc2 + fc1);
    re = 1.0L - tmpl_Sqrt_One_By_Two_Pi_L * (fc2 - fc1 + fs2 - fs1);
    out = tmpl_LDouble_Arctan2(im, re);

    return out;
}

