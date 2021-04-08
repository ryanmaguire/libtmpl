
/*  Contains the tolower function.                                            */
#include <ctype.h>

/*  NULL is defined here.                                                     */
#include <stdlib.h>

/*  Function prototype here.                                                  */
#include <libtmpl/include/tmpl_string.h>

void tmpl_Make_Lower(char *str)
{
    unsigned long n = 0;

    if (str == NULL)
        return;

    while(str[n])
    {
        str[n] = (char)tolower(str[n]);
        ++n;
    }
}

