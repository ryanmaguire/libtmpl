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
 *                    tmpl_create_empty_char_vector.c                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Create a pointer to a vector that has had it's data pointer allocated *
 *      memory, but not initialized.                                          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Create_Empty_CharVector                                          *
 *      tmpl_Create_Empty_UCharVector                                         *
 *  Purpose:                                                                  *
 *      Allocates memory for an char-valued vector.                           *
 *  Arguments:                                                                *
 *      length (unsigned long int):                                           *
 *          The desired length of the vector.                                 *
 *  Output:                                                                   *
 *      vec (tmpl_CharVector/tmpl_UCharVector *):                             *
 *          A pointer to a vector struct.                                     *
 *  Called Functions:                                                         *
 *      malloc      (stdlib.h):                                               *
 *          Allocates memory for a pointer.                                   *
 *      tmpl_strdup (tmpl_string.h):                                          *
 *          Copies a string const char *str into a char pointer.              *
 *  Method:                                                                   *
 *      Use malloc and return.                                                *
 *  Notes:                                                                    *
 *      You will need to free the memory allocated to the vector when you are *
 *      done with it. This is done with tmpl_Destroy_UCharVector and          *
 *      tmpl_Destroy_CharVector.                                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_vector.h:                                                        *
 *          Header file where vectors are typedef'd.                          *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file where Booleans are defined.                           *
 *  3.) tmpl_string.h:                                                        *
 *          Header file providing additional functionality with strings in C. *
 *  4.) stdlib.h:                                                             *
 *          Standard C Library header file where malloc is defined.           *
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
 *  Date:       May 13, 2021                                                  *
 ******************************************************************************/

/*  malloc is provided here.                                                  */
#include <stdlib.h>

/*  tmpl_Bool, tmpl_False, and tmpl_True are defined here.                    */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup is declared here. Used for duplicating strings.               */
#include <libtmpl/include/tmpl_string.h>

/*  Vectors are typedef'd here.                                               */
#include <libtmpl/include/tmpl_vector.h>

void
tmpl_FloatVector_Add(tmpl_FloatVector *v, tmpl_FloatVector *u,
                     tmpl_FloatVector *sum)
{
    unsigned long int n;

    if (sum == NULL)
        return;

    else if (sum->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "The sum vector has sum->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (sum->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "The sum vector has sum->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (v == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "First input vector is v == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (v->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "First input vector has v->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (v->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "First input vector has v->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (u == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "Second input vector is u == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (u->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "Second input vector has u->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (u->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "Second input vector has u->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (u->length != v->length)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "Input vectors have v->length != u->length.\n"
            "The sum is undefined. Returning.\n\n"
        );
        return;
    }
    else if (sum->length != v->length)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_FloatVector_Add\n\n"
            "Input vectors have sum->length != v->length.\n"
            "The sum vector doesn't have the right dimensions to compute.\n\n"
        );
        return;
    }

    for (n = 0UL; n < sum->length; ++n)
        (sum->data)[n] = (v->data)[n] + (u->data)[n];
}

void
tmpl_DoubleVector_Add(tmpl_DoubleVector *v, tmpl_DoubleVector *u,
                      tmpl_DoubleVector *sum)
{
    unsigned long int n;

    if (sum == NULL)
        return;

    else if (sum->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "The sum vector has sum->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (sum->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "The sum vector has sum->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (v == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "First input vector is v == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (v->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "First input vector has v->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (v->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "First input vector has v->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (u == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Second input vector is u == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (u->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Second input vector has u->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (u->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Second input vector has u->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (u->length != v->length)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Input vectors have v->length != u->length.\n"
            "The sum is undefined. Returning.\n\n"
        );
        return;
    }
    else if (sum->length != v->length)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Input vectors have sum->length != v->length.\n"
            "The sum vector doesn't have the right dimensions to compute.\n\n"
        );
        return;
    }

    for (n = 0UL; n < sum->length; ++n)
        (sum->data)[n] = (v->data)[n] + (u->data)[n];
}

void
tmpl_LDoubleVector_Add(tmpl_LongDoubleVector *v, tmpl_LongDoubleVector *u,
                       tmpl_LongDoubleVector *sum)
{
    unsigned long int n;

    if (sum == NULL)
        return;

    else if (sum->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "The sum vector has sum->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (sum->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "The sum vector has sum->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (v == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "First input vector is v == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (v->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "First input vector has v->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (v->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "First input vector has v->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (u == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Second input vector is u == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (u->data == NULL)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Second input vector has u->data == NULL.\n"
            "Impossible to compute sum. Returning\n\n"
        );
        return;
    }
    else if (u->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Second input vector has u->error_occurred == True. Returning\n\n"
        );
        return;
    }

    if (u->length != v->length)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Input vectors have v->length != u->length.\n"
            "The sum is undefined. Returning.\n\n"
        );
        return;
    }
    else if (sum->length != v->length)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\tFunction Name: tmpl_DoubleVector_Add\n\n"
            "Input vectors have sum->length != v->length.\n"
            "The sum vector doesn't have the right dimensions to compute.\n\n"
        );
        return;
    }

    for (n = 0UL; n < sum->length; ++n)
        (sum->data)[n] = (v->data)[n] + (u->data)[n];
}

