#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/compat/tmpl_free.h>
#include <libtmpl/include/compat/tmpl_malloc.h>
#include <libtmpl/include/compat/tmpl_realloc.h>
#include <libtmpl/include/tmpl_knots.h>
#include <libtmpl/include/tmpl_string.h>

/*  Function for creating a tmpl_VirtualKnot from a string representing the   *
 *  Gauss code of the knot.                                                   */
void
tmpl_GaussCode_From_String(const char * const str, tmpl_GaussCode * const code)
{
    unsigned long int i, ind;
    size_t word_length;
    void *tmp;

    if (!code)
        return;

    tmpl_GaussCode_Init(code);

    /*  If the string is NULL, set the error_occurred variable to true and    *
     *  store an error message in the virtual knot.                           */
    if (!str)
    {
        code->error_occurred = tmpl_True;
        code->error_message =
            "Error Encountered: libtmpl\n"
            "    tmpl_GaussCode_From_String\n\n"
            "Input string is NULL.\n";

        return;
    }

    word_length = tmpl_String_Length(str);
    code->tuples = TMPL_MALLOC(tmpl_GaussTuple, word_length / 3);

    if (!code->tuples)
    {
        code->error_occurred = tmpl_True;
        code->error_message =
            "Error Encountered: libtmpl\n"
            "    tmpl_GaussCode_From_String\n\n"
            "malloc returned NULL for tuples pointer.\n";

        return;
    }

    i = 0U;
    ind = 0U;

    while (str[i])
    {
        while (str[i] == ' ')
            ++i;

        switch(str[i])
        {
            case 'o':
            case 'O':
                code->tuples[ind].crossing_type = TMPL_OVER_CROSSING;
                break;
            case 'u':
            case 'U':
                code->tuples[ind].crossing_type = TMPL_UNDER_CROSSING;
                break;
            default:
                goto PARSING_ERROR;
        }

        ++i;

        while (str[i] == ' ')
            ++i;

        if (tmpl_Char_Is_Digit(str[i]))
        {
            size_t k = i;
            while (tmpl_Char_Is_Digit(str[k]))
                ++k;

            code->tuples[ind].crossing_number = tmpl_String_To_ULong(&str[i]);
            i = k;
        }
        else
            goto PARSING_ERROR;

        while (str[i] == ' ')
            ++i;

        switch(str[i])
        {
            case '+':
                code->tuples[ind].crossing_sign = TMPL_POSITIVE_CROSSING;
                break;
            case '-':
                code->tuples[ind].crossing_sign = TMPL_NEGATIVE_CROSSING;
                break;
            default:
                goto PARSING_ERROR;
        }

        ++i;
        ++ind;
    }

    if ((ind % 2) != 0)
    {
        TMPL_FREE(code->tuples);
        code->error_occurred = tmpl_True;
        code->error_message =
            "Error Encountered: libtmpl\n"
            "    tmpl_GaussCode_From_String\n\n"
            "Input string does not have an even number of Gauss tuples.\n"
            "A Gauss code corresponding to an actual virtual knot should\n"
            "Have an even number of elements in the sequence.\n";

        return;
    }

    code->length = ind;
    code->number_of_crossings = ind << 1;

    tmp = TMPL_REALLOC(code->tuples, code->length);

    if (tmp)
        code->tuples = TMPL_CAST(tmp, tmpl_GaussTuple *);

    return;

PARSING_ERROR:

    TMPL_FREE(code->tuples);

    code->error_occurred = tmpl_True;
    code->error_message =
        "Error Encountered: libtmpl\n"
        "    tmpl_GaussCode_From_String\n\n"
        "Could not parse input string. String must be of the\n"
        "form TNSTNSTNS...TNS where T is type, N is an integer,\n"
        "and S is the sign. EX: O1+U2+O3+U1+O2+U3+\n";
}
