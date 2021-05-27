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
 *                            tmpl_idl_bessel_j0                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide an example of the C-IDL API to call libtmpl functions in IDL. *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 27, 2021                                                  *
 ******************************************************************************/

#include <libtmpl/include/tmpl_special_functions.h>
#include <stdio.h>

void tmpl_IDL_Bessel_J0(int argc, void *argv[]);

/*  This function will be callable from IDL via the string                    *
 *  'tmpl_IDL_Bessel_J0' using the CALL_EXTERNAL routine.                     */
void tmpl_IDL_Bessel_J0(int argc, void *argv[])
{
    /*  Declare two double pointers, the input and output for IDL.            */
    double *x, *y;

    /*  Size is the size of the input IDL array.                              */
    unsigned long n, size;

    /*  We're expecting three inputs, so check this.                          */
    if (argc != 3)
    {
        printf("\nError: libtmpl\n"
               "\ttmpl_IDL_Bessel_J0\n\n"
               "Invalid number of arguments. Expected 3.\n"
               "Number of inputs provided: %d\n"
               "Aborting computation and returning.\n\n", argc);
        return;
    }

    /*  Get the parameters passed from IDL.                                   */
    x = (double *)argv[0];
    y = (double *)argv[2];
    size = *(unsigned long *)argv[1];

    /*  Loop through each point and compute the Bessel J0 function.           */
    for (n = 0U; n < size; ++n)
        y[n] = tmpl_Double_Bessel_J0(x[n]);
}

/******************************************************************************
 *  Compile this with:                                                        *
 *      gcc tmpl_idl_bessel_j0.c -O3 -shared -o tmpl_idl_bessel_j0.so -ltmpl  *
 *                                                                            *
 *  -shared means we're creating a shared object (library file).              *
 *  -O3 means we want level 3 optimization to make it faster.                 *
 *  -o tmpl_idl_bessel_j0.so means we're compiling this into a file           *
 *      called 'tmpl_idl_bessel_j0.so'.                                       *
 *  -ltmpl is a linker parameter, telling the linking to link the             *
 *      program to libtmpl.so which should be in /usr/local/lib/.             *
 *                                                                            *
 *  See bessel_j0.pro for details on the IDL part of this program.            *
 ******************************************************************************/
