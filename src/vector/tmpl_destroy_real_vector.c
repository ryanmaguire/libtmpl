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
 *                       tmpl_destroy_int_vector.c                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Create a pointer to a vector that has all of its entries set to zero. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Destroy_ShortVector                                              *
 *      tmpl_Destory_UShortVector                                             *
 *  Purpose:                                                                  *
 *      Free's all allocated memory to a vector and sets pointer to NULL.     *
 *  Arguments:                                                                *
 *      vec_ptr (tmpl_ShortVector/tmpl_UShortVector **)                       *
 *          A pointer to a pointer to a vector.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      free    (stdlib.h)                                                    *
 *          Deallocates memory allocated by malloc and calloc.                *
 *  Method:                                                                   *
 *      Free the non-NULL pointers in the structure, then set those pointers  *
 *      to NULL to avoid free'ing them twice, and finally set the pointer     *
 *      to the entire structure to NULL to avoid trying to use it after it's  *
 *      been destroyed.                                                       *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_vector.h:                                                        *
 *          Header file where vectors are typedef'd.                          *
 *  2.) stdlib.h:                                                             *
 *          Standard C Library header file where calloc is defined.           *
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
 *  Date:       May 14, 2021                                                  *
 ******************************************************************************/

/*  free is provided here.                                                    */
#include <stdlib.h>

/*  Vectors are typedef'd here.                                               */
#include <libtmpl/include/tmpl_vector.h>

/*  Function for creating a single-precision zero vector.                     */
void
tmpl_Destroy_FloatVector(tmpl_FloatVector **vec_ptr)
{
    /*  Declare a variable for the vector pointer we're returning.            */
    tmpl_FloatVector *vec;

    /*  Neither the pointer-to-a-pointer, nor the pointer should be NULL.     *
     *  Check that this is so.                                                */
    if (vec_ptr == NULL)
        return;
    else if (*vec_ptr == NULL)
        return;

    /*  Set the pointer vec to the pointer pointed to be the input vec_ptr.   */
    vec = *vec_ptr;

    /*  The functions that allocate memory for vectors automatically set the  *
     *  data pointer to NULL on error, or if no memory is requested. If the   *
     *  the data pointer is not NULL, we can free it.                         */
    if (vec->data != NULL)
    {
        /*  Free the data and then set the pointer to NULL. This will help us *
         *  avoid trying to free this pointer twice, which can crash the      *
         *  the program.                                                      */
        free(vec->data);
        vec->data = NULL;
    }

    /*  The error_message string is initialized to NULL unless an error       *
     *  occurs, in which case it becomes a pointer to a char array. If not    *
     *  NULL, we can free the string.                                         */
    if (vec->error_message != NULL)
    {
        free(vec->error_message);

        /*  Reset the pointer to NULL to avoid free'ing it twice.             */
        vec->error_message = NULL;
    }

    /*  Finally, free the pointer. All functions used to create vector        *
     *  pointers use malloc or calloc, or set the pointer to NULL. Since      *
     *  we've already checked that the pointer is not NULL, we can free it.   */
    free(vec);

    /*  Now set the vec pointer to NULL to avoid free'ing it twice.           */
    vec = NULL;
}
/*  End of tmpl_Destroy_IntVector.                                            */

/*  Function for creating a single-precision zero vector.                     */
void
tmpl_Destroy_DoubleVector(tmpl_DoubleVector **vec_ptr)
{
    /*  Declare a variable for the vector pointer we're returning.            */
    tmpl_DoubleVector *vec;

    /*  Neither the pointer-to-a-pointer, nor the pointer should be NULL.     *
     *  Check that this is so.                                                */
    if (vec_ptr == NULL)
        return;
    else if (*vec_ptr == NULL)
        return;

    /*  Set the pointer vec to the pointer pointed to be the input vec_ptr.   */
    vec = *vec_ptr;

    /*  The functions that allocate memory for vectors automatically set the  *
     *  data pointer to NULL on error, or if no memory is requested. If the   *
     *  the data pointer is not NULL, we can free it.                         */
    if (vec->data != NULL)
    {
        /*  Free the data and then set the pointer to NULL. This will help us *
         *  avoid trying to free this pointer twice, which can crash the      *
         *  the program.                                                      */
        free(vec->data);
        vec->data = NULL;
    }

    /*  The error_message string is initialized to NULL unless an error       *
     *  occurs, in which case it becomes a pointer to a char array. If not    *
     *  NULL, we can free the string.                                         */
    if (vec->error_message != NULL)
    {
        free(vec->error_message);

        /*  Reset the pointer to NULL to avoid free'ing it twice.             */
        vec->error_message = NULL;
    }

    /*  Finally, free the pointer. All functions used to create vector        *
     *  pointers use malloc or calloc, or set the pointer to NULL. Since      *
     *  we've already checked that the pointer is not NULL, we can free it.   */
    free(vec);

    /*  Now set the vec pointer to NULL to avoid free'ing it twice.           */
    vec = NULL;
}
/*  End of tmpl_Destroy_UIntVector.                                           */

/*  Function for creating a single-precision zero vector.                     */
void
tmpl_Destroy_LongDoubleVector(tmpl_LongDoubleVector **vec_ptr)
{
    /*  Declare a variable for the vector pointer we're returning.            */
    tmpl_LongDoubleVector *vec;

    /*  Neither the pointer-to-a-pointer, nor the pointer should be NULL.     *
     *  Check that this is so.                                                */
    if (vec_ptr == NULL)
        return;
    else if (*vec_ptr == NULL)
        return;

    /*  Set the pointer vec to the pointer pointed to be the input vec_ptr.   */
    vec = *vec_ptr;

    /*  The functions that allocate memory for vectors automatically set the  *
     *  data pointer to NULL on error, or if no memory is requested. If the   *
     *  the data pointer is not NULL, we can free it.                         */
    if (vec->data != NULL)
    {
        /*  Free the data and then set the pointer to NULL. This will help us *
         *  avoid trying to free this pointer twice, which can crash the      *
         *  the program.                                                      */
        free(vec->data);
        vec->data = NULL;
    }

    /*  The error_message string is initialized to NULL unless an error       *
     *  occurs, in which case it becomes a pointer to a char array. If not    *
     *  NULL, we can free the string.                                         */
    if (vec->error_message != NULL)
    {
        free(vec->error_message);

        /*  Reset the pointer to NULL to avoid free'ing it twice.             */
        vec->error_message = NULL;
    }

    /*  Finally, free the pointer. All functions used to create vector        *
     *  pointers use malloc or calloc, or set the pointer to NULL. Since      *
     *  we've already checked that the pointer is not NULL, we can free it.   */
    free(vec);

    /*  Now set the vec pointer to NULL to avoid free'ing it twice.           */
    vec = NULL;
}
/*  End of tmpl_Destroy_UIntVector.                                           */

