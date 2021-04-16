

#include <libtmpl/include/tmpl_knots.h>
#include <libtmpl/include/tmpl_string.h>
#include <stdlib.h>
#include <ctype.h>

/*  Function for creating a tmpl_VirtualKnot from a string representing the   *
 *  Gauss code of the knot.                                                   */
tmpl_VirtualKnot *tmpl_Gauss_Code_From_String(char *str)
{
    tmpl_uint64 i, ind;
    tmpl_VirtualKnot *K;

    /*  Allocate memory for our virtual knot pointer.                         */
    K = malloc(sizeof(*K));

    /*  Check that malloc didn't fail. If it did, it returns NULL. Abort and  *
     *  return a NULL pointer.                                                */
    if (K == NULL)
        return NULL;

    /*  Set the error_occured and error_message False and NULL, respectively, *
     *  indicating no error has occured. If everything executes smoothly,     *
     *  this will remain unchanged.                                           */
    K->error_occured = tmpl_False;
    K->error_message = NULL;

    /*  If the string is NULL, set the error_occured variable to true and     *
     *  store an error message in the virtual knot.                           */
    if (str == NULL)
    {
        K->number_of_crossings = 0;
        K->gauss_code = NULL;
        K->error_occured = tmpl_True;
        K->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "    tmpl_Gauss_Code_From_String\n"
            "Input string is NULL. Cannot create virtual knot. Aborting.\n"
        );
        return K;
    }

    K->gauss_code = malloc(sizeof(*K->gauss_code));

    if (K->gauss_code == NULL)
    {
        K->number_of_crossings = 0;
        K->error_occured = tmpl_True;
        K->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "    tmpl_Gauss_Code_From_String\n"
            "Malloc returned NULL for gauss_code pointer. Aborting.\n"
        );
        return K;
    }

    i = 0U;
    ind = 0U;
    while (str[i])
    {
        switch(str[i])
        {
            case 'o':
            case 'O':
                (K->gauss_code[ind]).crossing_type = tmpl_OverCrossing;
                break;
            case 'u':
            case 'U':
                (K->gauss_code[ind]).crossing_type = tmpl_UnderCrossing;
                break;
            default:
                free(K->gauss_code);
                K->gauss_code = NULL;
                K->error_occured = tmpl_True;
                K->error_message = tmpl_strdup(
                    "Error Encountered: libtmpl\n"
                    "    tmpl_Gauss_Code_From_String\n"
                    "Could not parse input string. String must be of the\n"
                    "form TNSTNSTNS...TNS where T is type, N is an integer,\n"
                    "and S is the sign. EX: O1+U2+O3+U1+O2+U3+\n"
                );

                return K;
        }
        ++i;

        if isdigit(str[i])
        {
	        size_t k = i;
            while (isdigit(str[k]))
            {
                ++k;
            }

	        (K->gauss_code[ind]).crossing_number = (tmpl_uint64)atoi(str + i);
	        i = k;
        }
        else
        {
            free(K->gauss_code);
            K->gauss_code = NULL;
            K->error_occured = tmpl_True;
            K->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "    tmpl_Gauss_Code_From_String\n"
                "Could not parse input string. String must be of the\n"
                "form TNSTNSTNS...TNS where T is type, N is an integer, and\n"
                "S is the sign. EX: O1+U2+O3+U1+O2+U3+\n"
            );
            return K;
        }

        switch(str[i])
        {
            case '+':
                (K->gauss_code[ind]).crossing_sign = tmpl_PositiveCrossing;
                break;
            case '-':
                (K->gauss_code[ind]).crossing_sign = tmpl_NegativeCrossing;
                break;
            default:
                free(K->gauss_code);
                K->gauss_code = NULL;
                K->error_occured = tmpl_True;
                K->error_message = tmpl_strdup(
                    "Error Encountered: libtmpl\n"
                    "    tmpl_Gauss_Code_From_String\n"
                    "Could not parse input string. String must be of the\n"
                    "form TNSTNSTNS...TNS where T is type, N is an integer,\n"
                    "and S is the sign. EX: O1+U2+O3+U1+O2+U3+\n"
                );

                return K;
        }
        ++i;
        ++ind;
        K->gauss_code = realloc(K->gauss_code, sizeof(*K->gauss_code)*(ind+1));
    }

    K->gauss_code = realloc(K->gauss_code, sizeof(*K->gauss_code)*ind);
    K->number_of_crossings = (tmpl_uint64) (ind / 2);

    if ((ind % 2) != 0)
    {
        K->error_occured = tmpl_True;
        K->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "    tmpl_Gauss_Code_From_String\n"
            "Input string does not have an even number of Gauss tuples.\n"
            "A Gauss code corresponding to an actual virtual knot should\n"
            "Have an even number of elements in the  sequence.\n"
        );
    }

    return K;
}

