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
 *                    tmpl_create_vector_from_long_data.c                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Create a pointer to a vector from a pointer to a long-valued array.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Create_IntVector_From_Data                                       *
 *      tmpl_Create_UIntVector_From_Data                                      *
 *  Purpose:                                                                  *
 *      Given a pointer to a int/unsigned int array, create a pointer         *
 *      to a vector with the data set to this input array.                    *
 *  Arguments:                                                                *
 *      arr (int/unsigned int *):                                             *
 *          A pointer to a char-valued array.                                 *
 *      length (unsigned long int):                                           *
 *          The length of the array pointed to by arr.                        *
 *  Output:                                                                   *
 *      vec (tmpl_IntVector/tmpl_UIntVector *):                               *
 *          A pointer to a vector struct.                                     *
 *  Called Functions:                                                         *
 *      malloc      (stdlib.h):                                               *
 *          Allocates memory for a pointer.                                   *
 *      tmpl_strdup (tmpl_string.h):                                          *
 *          Copies a string const char *str into a char pointer.              *
 *  Method:                                                                   *
 *      Loop through the input array and store the values in the vector.      *
 *  Notes:                                                                    *
 *      You will need to free the memory allocated to the vector when you are *
 *      done with it. This is done with tmpl_Destroy_IntVector and            *
 *      tmpl_Destroy_UIntVector.                                              *
 *                                                                            *
 *      The memory pointed to be arr is NOT stolen, but rather copied. You    *
 *      will still need to free arr if malloc was used on it.                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_vector_integer.h:                                                *
 *          Header file where vectors are typedef'd.                          *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file where Booleans are defined.                           *
 *  3.) tmpl_string.h:                                                        *
 *          Header file providing additional functionality with strings in C. *
 *  4.) stdlib.h:                                                             *
 *          Standard C Library header file where malloc is defined.           *
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
#include <libtmpl/include/tmpl_vector_integer.h>

/*  Function for creating a int vector from an int array.                     */
tmpl_LongVector *
tmpl_Create_LongVector_From_Data(long *arr, unsigned long int length)
{
    /*  Declare a variable for indexing over the array, and a pointer to the  *
     *  vector we'll be returning.                                            */
    unsigned long int n;
    tmpl_LongVector *vec;

    /*  Allocate memory for vec using malloc.                                 */
    vec = malloc(sizeof(*vec));

    /*  If malloc failed it returns NULL. Check that this did not happen.     */
    if (vec == NULL)
        return NULL;

    /*  Initialize the error variables to their default values.               */
    vec->error_message  = NULL;
    vec->error_occurred = tmpl_False;

    /*  Set the length of the vector to the length provided.                  */
    vec->length = length;

    /*  If the length is zero, this is an empty vector. Set the data to NULL. */
    if (length == 0UL)
    {
        vec->data = NULL;
        return vec;
    }

    /*  If the input array is NULL but the length is not zero, an error has   *
     *  occured. Set the data to NULL and store an error message in vec.      */
    if (arr == NULL)
    {
        vec->data = NULL;
        vec->error_occurred = tmpl_True;

        /*  Since the data is NULL, there are zero elements. Specify this.    */
        vec->length = 0UL;

        /*  Store an error message detailing what went wrong in the struct.   */
        vec->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_Create_LongVector_From_Data\n\n"
            "Input pointer is NULL but input length is not zero.\n"
            "Setting vec->data to NULL and returning.\n"
        );

        return vec;
    }
    /*  End of if (arr == NULL).                                              */

    /*  If we get here, malloc didn't fail and a non-NULL pointer was given.  *
     *  Allocate memory for the data inside the vector.                       */
    vec->data = malloc(sizeof(*(vec->data)) * length);

    /*  Check if malloc failed.                                               */
    if (vec->data == NULL)
    {
        vec->error_occurred = tmpl_True;
        vec->length = 0UL;
        vec->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_Create_LongVector_From_Data\n\n"
            "Malloc failed and returned NULL for vec->data.\n"
        );
        return vec;
    }
    /*  End of if (vec->data == NULL).                                        */

    /*  If malloc didn't fail, loop through the array and store the values.   */
    for (n = 0UL; n < length; ++n)
        (vec->data)[n] = arr[n];

    return vec;
}
/*  End of tmpl_Create_LongVector_From_Data.                                  */

/*  Function for creating an unsigned int vector from an unsigned int array.  */
tmpl_ULongVector *
tmpl_Create_ULongVector_From_Data(unsigned long int *arr,
                                  unsigned long int length)
{
    /*  Declare a variable for indexing over the array, and a pointer to the  *
     *  vector we'll be returning.                                            */
    unsigned long int n;
    tmpl_ULongVector *vec;

    /*  Allocate memory for vec using malloc.                                 */
    vec = malloc(sizeof(*vec));

    /*  If malloc failed it returns NULL. Check that this did not happen.     */
    if (vec == NULL)
        return NULL;

    /*  Initialize the error variables to their default values.               */
    vec->error_message  = NULL;
    vec->error_occurred = tmpl_False;

    /*  Set the length of the vector to the length provided.                  */
    vec->length = length;

    /*  If the length is zero, this is an empty vector. Set the data to NULL. */
    if (length == 0UL)
    {
        vec->data = NULL;
        return vec;
    }

    /*  If the input array is NULL but the length is not zero, an error has   *
     *  occured. Set the data to NULL and store an error message in vec.      */
    if (arr == NULL)
    {
        vec->data = NULL;
        vec->error_occurred = tmpl_True;

        /*  Since the data is NULL, there are zero elements. Specify this.    */
        vec->length = 0UL;

        /*  Store an error message detailing what went wrong in the struct.   */
        vec->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_Create_ULongVector_From_Data\n\n"
            "Input pointer is NULL but input length is not zero.\n"
            "Setting vec->data to NULL and returning.\n"
        );

        return vec;
    }
    /*  End of if (arr == NULL).                                              */

    /*  If we get here, malloc didn't fail and a non-NULL pointer was given.  *
     *  Allocate memory for the data inside the vector.                       */
    vec->data = malloc(sizeof(*(vec->data)) * length);

    /*  Check if malloc failed.                                               */
    if (vec->data == NULL)
    {
        vec->error_occurred = tmpl_True;
        vec->length = 0UL;
        vec->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_Create_ULongVector_From_Data\n\n"
            "Malloc failed and returned NULL for vec->data.\n"
        );
        return vec;
    }
    /*  End of if (vec->data == NULL).                                        */

    /*  If malloc didn't fail, loop through the array and store the values.   */
    for (n = 0UL; n < length; ++n)
        (vec->data)[n] = arr[n];

    return vec;
}
/*  End of tmpl_Create_ULongVector_From_Data.                                 */
