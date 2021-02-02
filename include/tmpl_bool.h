/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *      Define bool, false, and true for C89/C90 compilers. The C89/C90 does  *
 *      not define such a data type. Booleans were first introduced in C99.   *
 *  NOTES:                                                                    *
 *      This code is identical to the code I wrote for rss_ringoccs, only the *
 *      rssringoccs titles have been replaced with tmpl. rss_ringoccs is also *
 *      released under GPL3.                                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 1, 2021                                              *
 ******************************************************************************
 *                          Revision History                                  *
 ******************************************************************************
 *  2021/02/01: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs and edited.                                  *
 *  2021/02/02: Ryan Maguire:                                                 *
 *      Soft freeze for libtmpl alpha release.                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_BOOL_H__
#define __TMPL_BOOL_H__

/*  The C99, C11, and C18 standards require support for booleans, but it is   *
 *  not available in C89/C90. We've typedef'd Booleans as tmpl_Bool to avoid  *
 *  naming conflicts with C99 and higher Booleans. If you compiler            *
 *  supports Booleans, you should be able to use stdbools with libtmpl.       */

/*  We prepend tmpl onto False, True, and Bool to avoid name conflicts.       */
typedef enum {tmpl_False, tmpl_True} tmpl_Bool;

#endif
/*  End of include guard.                                                     */

