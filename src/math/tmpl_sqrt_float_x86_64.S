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
 *                              tmpl_sqrt_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at single precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Sqrt                                                       *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (float):                                                       *
 *          The square root of x at single precision.                         *
 *  Called Functions:                                                         *
 *      sqrtss                                                                *
 *  Method:                                                                   *
 *      For x86_64/amd64 machines sqrt is a built-in function.                *
 *  Notes:                                                                    *
 *      This file compiles using GCC, clang, or PCC on GNU/Linux, and         *
 *      using GCC or clang on FreeBSD and macOS (PCC may work on those        *
 *      platforms, but I haven't tested this), for x86_64/amd64 computers.    *
 *      This assembly code is significantly faster than the equivalent C code *
 *      found in tmpl_sqrt_double.c.                                          *
 *                                                                            *
 *  Accuracy and Performance:                                                 *
 *                                                                            *
 *      A time and accuracy test against glibc produced the following:        *
 *                                                                            *
 *      libtmpl using assembly code (tmpl_sqrt_double_x86_64.S):              *
 *                                                                            *
 *          tmpl_Float_Sqrt vs. sqrtf                                         *
 *          start:   9.9999997473787516e-05                                   *
 *          end:     1.0000000000000000e+04                                   *
 *          samples: 5220285568                                               *
 *          dx:      1.9156041162204929e-06                                   *
 *          libtmpl: 11.913069 seconds                                        *
 *          C:       10.062599 seconds                                        *
 *          max abs error: 0.0000000000000000e+00                             *
 *          max rel error: 0.0000000000000000e+00                             *
 *          rms abs error: 0.0000000000000000e+00                             *
 *          rms rel error: 0.0000000000000000e+00                             *
 *                                                                            *
 *      These tests were performed with the following specs:                  *
 *                                                                            *
 *          CPU:  AMD Ryzen 3900 12-core                                      *
 *          MAX:  4672.0698 MHz                                               *
 *          MIN:  2200.0000 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  Ripjaw DDR4-3600 16GBx4                                     *
 *          MB:   Gigabyte Aorus x570 Elite WiFi                              *
 *          OS:   Debian 11 (Bullseye) GNU/LINUX                              *
 *                                                                            *
 *      Performance will of course vary on different systems.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 5, 2022                                                 *
 ******************************************************************************/

/*  Windows, 64-bit, version. Works with clang-cl in 64-bit mode.             */
#if defined(_WIN64)
.p2align 4,0x90;
.globl tmpl_Float_Sqrt;
.section .drectve;
.ascii " -export:", "tmpl_Float_Sqrt";
.section .text;
.def tmpl_Float_Sqrt;
.scl 2;
.type 32;
.endef;

tmpl_Float_Sqrt:
        sqrtss  %xmm0, %xmm0
        ret

/*  Apple x86_64 machines. Works with clang and gcc.                          */
#elif defined(__APPLE__)
.globl _tmpl_Float_Sqrt
.align 4,0x90;

_tmpl_Float_Sqrt:
    sqrtss %xmm0, %xmm0
    ret

/*  GNU/Linux and FreeBSD (and others). Works with gcc, clang, and pcc.       */
#else
.text;
.p2align 4,0x90;
.globl tmpl_Float_Sqrt;
.type tmpl_Float_Sqrt,@function;

tmpl_Float_Sqrt:
    sqrtss %xmm0, %xmm0
    ret

.size tmpl_Float_Sqrt, . - tmpl_Float_Sqrt
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
