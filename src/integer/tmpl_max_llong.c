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
 ******************************************************************************/

/*  The TMPL_HAS_LONGLONG macro is found here.                                */
#include <libtmpl/include/tmpl_inttype.h>

/*  Only compile this is long long support is available / requested.          */
#if TMPL_HAS_LONGLONG == 1

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for finding the maximum of two longs.                            */
long long int tmpl_LLong_Max(long long int x, long long int y)
{
    if (x < y)
        return y;
    else
        return x;
}
/*  End of tmpl_LLong_Max.                                                    */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
