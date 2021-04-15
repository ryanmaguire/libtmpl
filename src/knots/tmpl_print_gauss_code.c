/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                         tmpl_print_gauss_code                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for printing the Gauss code of a virtual knot.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Print_Gauss_Code:                                                *
 *  Purpose:                                                                  *
 *      Prints the Gauss code of a virtual knot in the "tns tns ... tns"      *
 *      Where t is the "type" of crossing (over or under), n is the crossing  *
 *      number (an unsigned integer) and s is the "sign" of the crossing      *
 *      (positive or negative). For example, the trefoil knot 3_1 will print  *
 *      "O1+U2+O3+U1+O2+U3+".                                                 *
 *  Arguments:                                                                *
 *      tmpl_VirtualKnot *K:                                                  *
 *          A pointer to a tmpl_VirtualKnot struct. The knot whose Gauss code *
 *          we want to print.                                                 *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Loop through the Gauss Tuple array stored inside the struct and print *
 *      out the code based on the values found.                               *
 *  NOTES:                                                                    *
 *      A virtual knot with a NULL Gauss tuple pointer will be assumed to be  *
 *      the unknot, and this is what will print.                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_knots.h:                                                         *
 *          Header containing the function prototype and typedef's for        *
 *          virtual knots and Gauss tuples.                                   *
 *  2.) tmpl_integer.h:                                                       *
 *          Header file containing fixed-width integer data types for 32-bit  *
 *          and 64-bit integers.                                              *
 *  3.) stdio.h:                                                              *
 *          Standard C library header file containing printf.                 *
 *  4.) stdlib.h:                                                             *
 *          Standard C library header file containing the NULL macro.         *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       April 15, 2021                                                *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/04/15: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_knots.h>

/*  Fixed-width integer data types typedef'd here.                            */
#include <libtmpl/include/tmpl_integer.h>

/*  printf function found here.                                               */
#include <stdio.h>

/*  And the NULL macro is found here.                                         */
#include <stdlib.h>

void tmpl_Print_Gauss_Code(tmpl_VirtualKnot *K)
{
    tmpl_uint64 ind;
    tmpl_uint64 gauss_code_length;
    tmpl_GaussTuple *T_ptr;

    if (K == NULL)
    {
        printf("Unknot\n");
        return;
    }

    gauss_code_length = 2*K->number_of_crossings;

    for (ind = 0; ind < gauss_code_length; ++ind)
    {
        T_ptr = &(K->gauss_code[ind]);

        if (T_ptr->crossing_sign == tmpl_PositiveCrossing)
        {
            if (T_ptr->crossing_type == tmpl_UnderCrossing)
                printf("U%lu+", (K->gauss_code[ind]).crossing_number);
            else
                printf("O%lu+", (K->gauss_code[ind]).crossing_number);
        }
        else
        {
            if (T_ptr->crossing_type == tmpl_UnderCrossing)
                printf("U%lu-", (K->gauss_code[ind]).crossing_number);
            else
                printf("O%lu-", (K->gauss_code[ind]).crossing_number);
        }
    }
    printf("\n");
}
/*  End of tmpl_Print_Gauss_Code.                                             */

