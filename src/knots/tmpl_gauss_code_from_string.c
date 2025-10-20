#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/compat/tmpl_free.h>
#include <libtmpl/include/compat/tmpl_malloc.h>
#include <libtmpl/include/compat/tmpl_realloc.h>
#include <libtmpl/include/tmpl_knots.h>
#include <libtmpl/include/tmpl_string.h>

#include <stdio.h>

/*  Function for creating a Gauss code from a string.                         */
void
tmpl_GaussCode_From_String(const char *str, tmpl_GaussCode * const code)
{
    unsigned long int ind;
    size_t word_length;
    void *tmp;
    tmpl_GaussTuple *tuples;

    if (!code)
        return;

    tmpl_GaussCode_Init(code);

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
    tuples = TMPL_MALLOC(tmpl_GaussTuple, word_length / 3);

    if (!tuples)
    {
        code->error_occurred = tmpl_True;
        code->error_message =
            "Error Encountered: libtmpl\n"
            "    tmpl_GaussCode_From_String\n\n"
            "malloc returned NULL for tuples pointer.\n";

        return;
    }

    ind = 0U;

    while (*str)
    {
        while (*str == ' ')
            ++str;

        switch (*str)
        {
            case 'o':
            case 'O':
                tuples[ind].crossing_type = TMPL_OVER_CROSSING;
                break;
            case 'u':
            case 'U':
                tuples[ind].crossing_type = TMPL_UNDER_CROSSING;
                break;
            default:
                goto PARSING_ERROR;
        }

        ++str;

        while (*str == ' ')
            ++str;

        if (!tmpl_Char_Is_Digit(*str))
            goto PARSING_ERROR;

        tuples[ind].crossing_number = tmpl_String_To_ULong_And_Increment(&str);

        while (*str == ' ')
            ++str;

        switch (*str)
        {
            case '+':
                tuples[ind].crossing_sign = TMPL_POSITIVE_CROSSING;
                break;
            case '-':
                tuples[ind].crossing_sign = TMPL_NEGATIVE_CROSSING;
                break;
            default:
                goto PARSING_ERROR;
        }

        ++str;
        ++ind;
    }

    if ((ind % 2) != 0)
    {
        TMPL_FREE(tuples);
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
    code->tuples = tuples;

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
