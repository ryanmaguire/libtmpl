/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                          tmpidl_special_functions                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide the special functions sublibrary of libtmpl for IDL users.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 9, 2022                                                 *
 ******************************************************************************/

/*  All special functions functions are found here.                           */
#include <libtmpl/include/tmpl_special_functions.h>

extern void tmpidl_Bessel_J0(int argc, void *argv[]);
extern void tmpidl_Bessel_I0(int argc, void *argv[]);
extern void tmpidl_LambertW(int argc, void *argv[]);
extern void tmpidl_Fresnel_Cos(int argc, void *argv[]);
extern void tmpidl_Fresnel_Sin(int argc, void *argv[]);

/*  IDL wrapper for the Bessel I0 function.                                   */
void tmpidl_Bessel_I0(int argc, void *argv[])
{
    /*  Declare two double pointers, the input and output for IDL.            */
    double *x, *y;

    /*  Size is the size of the input IDL array.                              */
    unsigned long n, size;

    /*  We're expecting three inputs, so check this.                          */
    if (argc != 3)
        return;

    /*  Get the parameters passed from IDL.                                   */
    x = (double *)argv[0];
    y = (double *)argv[2];
    size = *(unsigned long *)argv[1];

    /*  Loop through each point and compute the function for every value.     */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
        y[n] = tmpl_Double_Bessel_I0(x[n]);
}
/*  End of tmpidl_Bessel_I0.                                                  */

/*  IDL wrapper for the Bessel J0 function.                                   */
void tmpidl_Bessel_J0(int argc, void *argv[])
{
    /*  Declare two double pointers, the input and output for IDL.            */
    double *x, *y;

    /*  Size is the size of the input IDL array.                              */
    unsigned long n, size;

    /*  We're expecting three inputs, so check this.                          */
    if (argc != 3)
        return;

    /*  Get the parameters passed from IDL.                                   */
    x = (double *)argv[0];
    y = (double *)argv[2];
    size = *(unsigned long *)argv[1];

    /*  Loop through each point and compute the function for every value.     */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
        y[n] = tmpl_Double_Bessel_J0(x[n]);
}
/*  End of tmpidl_Bessel_J0.                                                  */

/*  IDL wrapper for the Lambert W function.                                   */
void tmpidl_LambertW(int argc, void *argv[])
{
    /*  Declare two double pointers, the input and output for IDL.            */
    double *x, *y;

    /*  Size is the size of the input IDL array.                              */
    unsigned long n, size;

    /*  We're expecting three inputs, so check this.                          */
    if (argc != 3)
        return;

    /*  Get the parameters passed from IDL.                                   */
    x = (double *)argv[0];
    y = (double *)argv[2];
    size = *(unsigned long *)argv[1];

    /*  Loop through each point and compute the function for every value.     */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
        y[n] = tmpl_Double_LambertW(x[n]);
}
/*  End of tmpidl_LambertW.                                                   */

/*  IDL wrapper for the Fresnel Cosine function.                              */
void tmpidl_Fresnel_Cos(int argc, void *argv[])
{
    /*  Declare two double pointers, the input and output for IDL.            */
    double *x, *y;

    /*  Size is the size of the input IDL array.                              */
    unsigned long n, size;

    /*  We're expecting three inputs, so check this.                          */
    if (argc != 3)
        return;

    /*  Get the parameters passed from IDL.                                   */
    x = (double *)argv[0];
    y = (double *)argv[2];
    size = *(unsigned long *)argv[1];

    /*  Loop through each point and compute the function for every value.     */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
        y[n] = tmpl_Double_Fresnel_Cos(x[n]);
}
/*  End of tmpidl_Fresnel_Cos.                                                */

/*  IDL wrapper for the Fresnel Sine function.                                */
void tmpidl_Fresnel_Sin(int argc, void *argv[])
{
    /*  Declare two double pointers, the input and output for IDL.            */
    double *x, *y;

    /*  Size is the size of the input IDL array.                              */
    unsigned long n, size;

    /*  We're expecting three inputs, so check this.                          */
    if (argc != 3)
        return;

    /*  Get the parameters passed from IDL.                                   */
    x = (double *)argv[0];
    y = (double *)argv[2];
    size = *(unsigned long *)argv[1];

    /*  Loop through each point and compute the function for every value.     */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
        y[n] = tmpl_Double_Fresnel_Sin(x[n]);
}
/*  End of tmpidl_Fresnel_Sin.                                                */
