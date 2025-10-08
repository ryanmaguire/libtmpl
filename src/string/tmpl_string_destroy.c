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
 *                            tmpl_string_destroy                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Free's the memory in a dynamically allocated string and then sets     *
 *      the pointer to NULL to avoid double free's.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_String_Destroy                                                   *
 *  Purpose:                                                                  *
 *      Safely free's the memory in a dynamically allocated string.           *
 *  Arguments:                                                                *
 *      str_ptr (char ** const):                                              *
 *          A pointer to a string.                                            *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          free:                                                             *
 *              Free's dynamically allocated memory.                          *
 *  Method:                                                                   *
 *      Use the TMPL_FREE macro to check if the string is NULL, freeing it if *
 *      is not, and then setting the string to NULL to avoid double frees.    *
 *  Notes:                                                                    *
 *      This function checks if either str_ptr or *str_ptr are NULL. Nothing  *
 *      is done in these cases.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_free.h:                                                          *
 *          Header providing TMPL_FREE with C vs. C++ compatibility.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 29, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/08: Ryan Maguire                                                  *
 *      Added docstring and replaced free with TMPL_FREE.                     *
 ******************************************************************************/

/*  Location of the TMPL_FREE macro.                                          */
#include <libtmpl/include/compat/tmpl_free.h>

/*  Forward declaration / function prototype, found in tmpl_string.h as well. */
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
