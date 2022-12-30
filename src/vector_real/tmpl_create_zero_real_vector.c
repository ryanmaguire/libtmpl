/******************************************************************************
 *                                 LICENSE                                    *
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
 *                     tmpl_create_zero_real_vector.c                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Create a pointer to a vector that has all of its entries set to zero. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Create_Zero_FloatVector                                          *
 *      tmpl_Create_Zero_DoubleVector                                         *
 *      tmpl_Create_Zero_LongDoubleVector                                     *
 *  Purpose:                                                                  *
 *      Allocates memory for a real-valued vector and sets entries to zero.   *
 *  Arguments:                                                                *
 *      length (unsigned long int):                                           *
 *          The desired length of the vector.                                 *
 *  Output:                                                                   *
 *      vec (tmpl_FloatVector/tmpl_DoubleVector/tmpl_LongDoubleVector *):     *
 *          A pointer to a vector struct.                                     *
 *  Called Functions:                                                         *
 *      malloc      (stdlib.h):                                               *
 *          Allocates memory for a pointer.                                   *
 *      tmpl_strdup (tmpl_string.h):                                          *
 *          Copies a string const char *str into a char pointer.              *
 *  Method:                                                                   *
 *      Use calloc and return.                                                *
 *  Notes:                                                                    *
 *      You will need to free the memory allocated to the vector when you are *
 *      done with it. This is done with tmpl_Destroy_FloatVector,             *
 *      tmpl_Destroy_DoubleVector, and tmpl_Destroy_LongDoubleVector.         *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_vector_real.h:                                                   *
 *          Header file where vectors are typedef'd.                          *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file where Booleans are defined.                           *
 *  3.) tmpl_string.h:                                                        *
 *          Header file providing additional functionality with strings in C. *
 *  4.) stdlib.h:                                                             *
 *          Standard C Library header file where calloc is defined.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2021                                                  *
 ******************************************************************************/

/*  malloc is provided here.                                                  */
#include <stdlib.h>

/*  tmpl_Bool, tmpl_False, and tmpl_True are defined here.                    */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup is declared here. Used for duplicating strings.               */
#include <libtmpl/include/tmpl_string.h>

/*  Vectors are typedef'd here.                                               */
#include <libtmpl/include/tmpl_vector_real.h>

/*  Function for creating a single-precision zero vector.                     */
tmpl_FloatVector *
tmpl_Create_Zero_FloatVector(unsigned long int length)
{
    /*  Declare a variable for the vector pointer we're returning.            */
    tmpl_FloatVector *vec;

    /*  Allocate memory for the vector with malloc.                           */
    vec = malloc(sizeof(*vec));

    /*  If malloc fails it returns NULL. Check that this did not happen.      */
    if (vec == NULL)
        return NULL;

    /*  If malloc didn't fail, initialize the variables in vec to their       *
     *  default values.                                                       */
    vec->error_occurred = tmpl_False;
    vec->error_message = NULL;
    vec->length = length;

    /*  If the length is zero, set the data to a NULL pointer.                */
    if (length == 0UL)
    {
        vec->data = NULL;
        return vec;
    }

    /*  Otherwise, allocate memory for the data pointer. calloc, unlike       *
     *  malloc, will initialize everything to zero, giving us a zero vector.  */
    vec->data = calloc(sizeof(*(vec->data)), length);

    /*  Again, check that calloc did not fail.                                */
    if (vec->data == NULL)
    {
        vec->error_occurred = tmpl_True;
        vec->length = 0UL;
        vec->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_Create_Empty_FloatVector\n\n"
            "Malloc failed and returned NULL for vec->data.\n"
        );
        return vec;
    }
    /*  End of if (vec->data == NULL).                                        */

    return vec;
}
/*  End of tmpl_Create_Empty_FloatVector.                                     */

/*  Function for creating a double-precision zero vector.                     */
tmpl_DoubleVector *
tmpl_Create_Zero_DoubleVector(unsigned long int length)
{
    /*  Declare a variable for the vector pointer we're returning.            */
    tmpl_DoubleVector *vec;

    /*  Allocate memory for the vector with malloc.                           */
    vec = malloc(sizeof(*vec));

    /*  If malloc fails it returns NULL. Check that this did not happen.      */
    if (vec == NULL)
        return NULL;

    /*  If malloc didn't fail, initialize the variables in vec to their       *
     *  default values.                                                       */
    vec->error_occurred = tmpl_False;
    vec->error_message = NULL;
    vec->length = length;

    /*  If the length is zero, set the data to a NULL pointer.                */
    if (length == 0UL)
    {
        vec->data = NULL;
        return vec;
    }

    /*  Otherwise, allocate memory for the data pointer. calloc, unlike       *
     *  malloc, will initialize everything to zero, giving us a zero vector.  */
    vec->data = calloc(sizeof(*(vec->data)), length);

    /*  Again, check that calloc did not fail.                                */
    if (vec->data == NULL)
    {
        vec->error_occurred = tmpl_True;
        vec->length = 0UL;
        vec->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_Create_Empty_DoubleVector\n\n"
            "Malloc failed and returned NULL for vec->data.\n"
        );
        return vec;
    }
    /*  End of if (vec->data == NULL).                                        */

    return vec;
}
/*  End of tmpl_Create_Empty_DoubleVector.                                    */

/*  Function for creating a long double-precision zero vector.                */
tmpl_LongDoubleVector *
tmpl_Create_Zero_LongDoubleVector(unsigned long int length)
{
    /*  Declare a variable for the vector pointer we're returning.            */
    tmpl_LongDoubleVector *vec;

    /*  Allocate memory for the vector with malloc.                           */
    vec = malloc(sizeof(*vec));

    /*  If malloc fails it returns NULL. Check that this did not happen.      */
    if (vec == NULL)
        return NULL;

    /*  If malloc didn't fail, initialize the variables in vec to their       *
     *  default values.                                                       */
    vec->error_occurred = tmpl_False;
    vec->error_message = NULL;
    vec->length = length;

    /*  If the length is zero, set the data to a NULL pointer.                */
    if (length == 0UL)
    {
        vec->data = NULL;
        return vec;
    }

    /*  Otherwise, allocate memory for the data pointer. calloc, unlike       *
     *  malloc, will initialize everything to zero, giving us a zero vector.  */
    vec->data = calloc(sizeof(*(vec->data)), length);

    /*  Again, check that malloc did not fail.                                */
    if (vec->data == NULL)
    {
        vec->error_occurred = tmpl_True;
        vec->length = 0UL;
        vec->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_Create_Empty_LongDoubleVector\n\n"
            "Malloc failed and returned NULL for vec->data.\n"
        );
        return vec;
    }
    /*  End of if (vec->data == NULL).                                        */

    return vec;
}
/*  End of tmpl_Create_Empty_LongDoubleVector.                                */

