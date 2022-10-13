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
 *      Prints the Gauss code of a virtual knot in the from "tns tns ... tns" *
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

/*  printf function found here.                                               */
#include <stdio.h>

/*  And the NULL macro is found here.                                         */
#include <stdlib.h>

/*  Function for printing the Gauss code of a virtual knot.                   */
void tmpl_Print_Gauss_Code(tmpl_VirtualKnot *K)
{
    /*  Declare a variable for looping through the indices of the Gauss code. */
    unsigned long int ind;

    /*  The Gauss code length is twice the number of crossings. We'll store   *
     *  that value in this variable.                                          */
    unsigned long int gauss_code_length;

    /*  And to improve readability, we'll extract a pointer to the nth        *
     *  element of the Gauss sequence and then parse the pointers values.     */
    tmpl_GaussTuple *T_ptr;

    /*  Check that the virtual knot is not NULL. Trying to access a NULL      *
     *  pointer may result in a segmentation fault as you will attempt to     *
     *  access memory you do not own. More importantly, the NULL virtual knot *
     *  corresponds to the empty knot. That is, the lack of a knot in S^3,    *
     *  which is just the manifold S^3. We'll print "Empty Knot" here.        */
    if (K == NULL)
    {
        puts("Empty Knot");
        return;
    }

    /*  If the pointer is not NULL, check that it is not corrupted. That is,  *
     *  check that the error_occured Boolean is not True.                     */
    if (K->error_occured)
    {
        if (K->error_message == NULL)
            puts("Error Encountered: libtmpl\n"
                 "    tmpl_Print_Gauss_Code\n\n"
                 "Input virtual knot has error_occured Boolean set to True.\n"
                 "error_message variable is NULL, so can't print the cause.");
        else
            printf("Error Encountered: libtmpl\n"
                   "    tmpl_Print_Gauss_Code\n\n"
                   "Input virtual knot has error_occured Boolean set to True.\n"
                   "Original Error Message:\n\n%s", K->error_message);
        return;
    }

    /*  If the Gauss code inside the virtual knot is empty, then there are    *
     *  no crossings. This is the unknot.                                     */
    else if (K->gauss_code == NULL)
    {
        printf("Unknot");
        return;
    }

    /*  If we get here, we have an actual "knot". That is, there are actual   *
     *  crossings (though it may be a virtual knot, and not a classical one). */
    gauss_code_length = 2*K->number_of_crossings;

    /*  Loop through the Gauss sequence and parse the Gauss tuples.           */
    for (ind = 0; ind < gauss_code_length; ++ind)
    {
        /*  Get a pointer to the current Gauss tuple. K->gauss_code is a      *
         *  pointer to a Gauss tuple array. K->gauss_code[ind] is a Gauss     *
         *  tuple struct. It is a waste of stack memory to reserve a local    *
         *  variable for this struct, so instead we simply have a pointer     *
         *  point to it. We get the address of the struct K->gauss_code[ind]  *
         *  with an ampersand &. So we have the following pointer:            */
        T_ptr = &(K->gauss_code[ind]);

        /*  A Gauss tuple has the crossing sign, crossing number, and         *
         *  crossing type. Parse these values and print out the Gauss code.   */
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

    /*  Print out a newline at the end of the code for readability.           */
    printf("\n");
    return;
}
/*  End of tmpl_Print_Gauss_Code.                                             */
