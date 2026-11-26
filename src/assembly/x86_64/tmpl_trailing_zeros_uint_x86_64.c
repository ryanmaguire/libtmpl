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

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration.                                 */
extern int tmpl_UInt_Trailing_Zeros(const unsigned int n);

TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
int
tmpl_UInt_Trailing_Zeros(const unsigned int n)
TMPL_UNSEQUENCED
{
    int count;

#ifdef __BMI__
    __asm__("tzcntl %1, %0" : "=r" (count) : "r" (n));
    __asm__("cmovel %1, %0" : "=r" (count) : "r" (count));
#else
    __asm__("bsfl %1, %0" : "=r" (count) : "r" (n));
    __asm__("cmovel %0, %0" : "=r" (count) : "r" (count));
#endif

    return count;
}
