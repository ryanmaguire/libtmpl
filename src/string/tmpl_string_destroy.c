#include <libtmpl/include/compat/tmpl_free.h>

extern void tmpl_String_Destroy(char ** const str_ptr);

/*  Function for freeing memory in a dynamically allocated string.            */
void tmpl_String_Destroy(char ** const str_ptr)
{
    /*  If the input pointer is NULL, there's nothing to be done. Return.     */
    if (!str_ptr)
        return;

    /*  TMPL_FREE will free the string if it is not NULL, and then set the    *
     *  pointer to be NULL after freeing. Use this.                           */
    TMPL_FREE(*str_ptr);
}
/*  End of tmpl_String_Destroy.                                               */
