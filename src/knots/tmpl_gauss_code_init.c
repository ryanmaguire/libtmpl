#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/types/tmpl_gauss_code.h>
#include <stddef.h>

extern void tmpl_GaussCode_Init(tmpl_GaussCode * const code);

void tmpl_GaussCode_Init(tmpl_GaussCode * const code)
{
    if (!code)
        return;

    code->length = 0UL;
    code->number_of_crossings = 0UL;
    code->tuples = NULL;
    code->error_message = NULL;
    code->error_occurred = tmpl_False;
}
