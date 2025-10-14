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
 *  Author:     Ryan Maguire                                                  *
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
void tmpl_GaussCode_Print(const tmpl_GaussCode * const code)
{
    /*  Declare a variable for looping through the indices of the Gauss code. */
    unsigned long int ind;

    /*  Check that the virtual knot is not NULL. Trying to access a NULL      *
     *  pointer may result in a segmentation fault as you will attempt to     *
     *  access memory you do not own. More importantly, the NULL virtual knot *
     *  corresponds to the empty knot. That is, the lack of a knot in S^3,    *
     *  which is just the manifold S^3. We'll print "Empty Knot" here.        */
    if (!code)
    {
        puts("Empty Knot");
        return;
    }

    /*  If the pointer is not NULL, check that it is not corrupted. That is,  *
     *  check that the error_occured Boolean is not True.                     */
    if (code->error_occurred)
    {
        if (code->error_message == NULL)
            puts("Error Encountered: libtmpl\n"
                 "    tmpl_Print_Gauss_Code\n\n"
                 "Input virtual knot has error_occured Boolean set to True.\n"
                 "error_message variable is NULL, so can't print the cause.");
        else
            printf("Error Encountered: libtmpl\n"
                   "    tmpl_Print_Gauss_Code\n\n"
                   "Input virtual knot has error_occured Boolean set to True.\n"
                   "Original Error Message:\n\n%s", code->error_message);
        return;
    }

    /*  If the Gauss code inside the virtual knot is empty, then there are    *
     *  no crossings. This is the unknot.                                     */
    else if (!code->tuples)
    {
        printf("Unknot");
        return;
    }

    /*  Loop through the Gauss sequence and parse the Gauss tuples.           */
    for (ind = 0UL; ind < code->length; ++ind)
    {
        /*  Get a pointer to the current Gauss tuple. code->gauss_code is a   *
         *  pointer to a Gauss tuple array. code->gauss_code[ind] is a Gauss  *
         *  tuple struct. It is a waste of stack memory to reserve a local    *
         *  variable for this struct, so instead we simply have a pointer     *
         *  point to it. We get the address of code->gauss_code[ind] with an  *
         *  ampersand, &.                                                     */
        const tmpl_GaussTuple * const tuple = &(code->tuples[ind]);

        /*  A Gauss tuple has the crossing sign, crossing number, and         *
         *  crossing type. Parse these values and print out the Gauss code.   */
        if (tuple->crossing_sign == TMPL_POSITIVE_CROSSING)
        {
            if (tuple->crossing_type == TMPL_UNDER_CROSSING)
                printf("U%lu+", tuple->crossing_number);
            else
                printf("O%lu+", tuple->crossing_number);
        }
        else
        {
            if (tuple->crossing_type == TMPL_UNDER_CROSSING)
                printf("U%lu-", tuple->crossing_number);
            else
                printf("O%lu-", tuple->crossing_number);
        }
    }

    /*  Print out a newline at the end of the code for readability.           */
    printf("\n");
    return;
}
/*  End of tmpl_GaussCode_Print.                                              */
