#include <libtmpl/include/tmpl_string.h>
#include <stdlib.h>

/*  Function for freeing memory in a dynamically allocated string.            */
void tmpl_String_Destroy(char **str_ptr)
{
    /*  If the input pointer is NULL, there's nothing to be done. Return.     */
    if (!str_ptr)
        return;

    /*  If the string itself is just a NULL pointer, also return.             */
    if (!(*str_ptr))
        return;

    /*  Otherwise free the string (not the pointer to the string).            */
    free(*str_ptr);

    /*  Set the strings pointer to NULL to avoid double free's.               */
    *str_ptr = NULL;
}
/*  End of tmpl_String_Destroy.                                               */
