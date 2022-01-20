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
 *                               tmpl_bool                                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Define bool, false, and true for C89/C90 compilers. C89/C90 does      *
 *      not define such a data type. Booleans were first introduced in C99.   *
 *  Notes:                                                                    *
 *      This code is identical to the code I wrote for rss_ringoccs, only the *
 *      rssringoccs titles have been replaced with tmpl. rss_ringoccs is also *
 *      released under GPL3.                                                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  None.                                                                     *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 1, 2021                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/09/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/01: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs and edited.                                  *
 *  2021/02/02: Ryan Maguire                                                  *
 *      Soft freeze for libtmpl alpha release.                                *
 *  2021/04/08: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code/comments. No  *
 *      more changes to comments or code unless something breaks.             *
 *  2021/08/31: Ryan Maguire                                                  *
 *      Added extern "C" statement for C++ support.                           *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BOOL_H
#define TMPL_BOOL_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus 
extern "C" {
#endif

/*  The C99, C11, and C18 standards require support for booleans, but it is   *
 *  not available in C89/C90. We've typedef'd Booleans as tmpl_Bool to avoid  *
 *  naming conflicts with C99 and higher Booleans. If your compiler           *
 *  supports Booleans, you should be able to use stdbools with libtmpl.       */

/*  We prepend tmpl onto False, True, and Bool to avoid name conflicts.       */
typedef enum _tmpl_Bool {tmpl_False, tmpl_True} tmpl_Bool;

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
