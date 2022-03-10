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
 *                                 tmpidl_math                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide the math sublibrary of libtmpl for IDL users.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 9, 2022                                                 *
 ******************************************************************************/

/*  Math functions found here.                                                */
#include <libtmpl/include/tmpl_math.h>

/*  IDL's ULONG is 32-bits. Use stdint for portability.                       */
#include <stdint.h>

extern void tmpidl_Log(int argc, void *argv[]);

/*  IDL wrapper for the Log function.                                         */
void tmpidl_Log(int argc, void *argv[])
{
    /*  Declare two double pointers, the input and output for IDL.            */
    double *x, *y;

    /*  Size is the size of the input IDL array.                              */
    uint32_t n, size;

    /*  We're expecting three inputs, so check this.                          */
    if (argc != 3)
        return;

    /*  Get the parameters passed from IDL.                                   */
    x = (double *)argv[0];
    y = (double *)argv[2];
    size = *(uint32_t *)argv[1];

    /*  Loop through each point and compute the function for every value.     */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
        y[n] = tmpl_Double_Log(x[n]);
}
/*  End of tmpidl_Log.                                                        */
