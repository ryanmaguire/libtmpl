/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                              tmpl_sqrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          The square root of x at double precision.                         *
 *  Called Functions:                                                         *
 *      sqrtsd                                                                *
 *  Method:                                                                   *
 *      For x86_64/amd64 machines sqrt is a built-in function.                *
 *  Notes:                                                                    *
 *      This file compiles using GCC, clang, or PCC on GNU/Linux, and         *
 *      using GCC or clang on FreeBSD and macOS (PCC may work on those        *
 *      platforms, but I haven't tested this), for x86_64/amd64 computers.    *
 *      This assembly code is significantly faster than the equivalent C code *
 *      found in tmpl_sqrt_double.c.                                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 5, 2022                                                 *
 ******************************************************************************/

/*  Windows, 64-bit, version. Works with clang-cl in 64-bit mode.             */
#if defined(_WIN64)
.p2align 4,0x90;
.globl tmpl_Double_Sqrt;
.section .drectve;
.ascii " -export:", "tmpl_Double_Sqrt";
.section .text;
.def tmpl_Double_Sqrt;
.scl 2;
.type 32;
.endef;

tmpl_Double_Sqrt:
        sqrtsd %xmm0, %xmm0
        ret

/*  Apple x86_64 machines. Works with clang and gcc.                          */
#elif defined(__APPLE__)
.globl _tmpl_Double_Sqrt
.align 4,0x90;

_tmpl_Double_Sqrt:
    sqrtsd %xmm0, %xmm0
    ret

/*  GNU/Linux and FreeBSD (and others). Works with gcc, clang, and pcc.       */
#else
.text;
.p2align 4,0x90;
.globl tmpl_Double_Sqrt;
.type tmpl_Double_Sqrt,@function;

tmpl_Double_Sqrt:
    sqrtsd %xmm0, %xmm0
    ret

.size tmpl_Double_Sqrt, . - tmpl_Double_Sqrt
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
