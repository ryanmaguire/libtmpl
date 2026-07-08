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
 *                             tmpl_float_barrier                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides macros for protecting against aggressive optimizations.      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_LDOUBLE_TYPE macro.                             *
 *  2.) tmpl_ieee754_ldouble.h:                                               *
 *          Contains the tmpl_IEEE754_LDouble typedef.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 7, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FLOAT_BARRIER_H
#define TMPL_FLOAT_BARRIER_H

/*  TMPL_LDOUBLE_TYPE macro found here.                                       */
#include <libtmpl/include/tmpl_config.h>

/*  The following __asm__ tricks are supported by GCC (version 3+) and Clang  *
 *  (version 9+). Older versions may work, but have not been tested.          */
#if defined(__GNUC__) || defined(__clang__)

/*  x86-64, SSE2 support is required by GCC and Clang (released in 2000).     *
 *  Various x86-64 extensions provide FMA-like instructions for float and     *
 *  double. A simple barrier can prevent aggressive optimizations without     *
 *  introducing redundant moves, producing a more performant build when       *
 *  compared to the volatile method.                                          */
#if defined(__x86_64__) || defined(__amd64__)

/*  "x" is the identifier for 32-bit and 64-bit floating-point SSE registers. */
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+x"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+x"(x))

/*  Older i386 platforms use a more generic fallback. On GCC and Clang, the   *
 *  optimizer will replace a * x + b with FMA, which ruins splits and         *
 *  double-double arithmetic. A barrier is needed, or a volatile specifier.   */
#elif defined(__i386__)

/*  Use generic registers. This is not guaranteed to be a no-op, this may     *
 *  produce a move. Nevertheless, it is still faster than declaring variables *
 *  volatile, which produces many moves.                                      */
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+r"(x))

/*  aarch64 provides FMA, and GCC and Clang will use it when optimizations    *
 *  are enabled. A barrier is faster than volatile on this architecture.      */
#elif defined(__aarch64__)

/*  aarch64 has "x", like x86-64, but this is restricted to registers 0-15.   *
 *  "w" is the more general floating-point register identifier.               */
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+w"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+w"(x))

/*  armhf (hardware-float), FMA may be available. The barrier uses VFP        *
 *  registers, and so these need to be available.                             */
#elif defined(__arm__) && defined(__ARM_PCS_VFP) && defined(__VFP_FP__)

/*  "t" is used for 32-bit floating-point, and "w" is used for 64-bit.        */
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+t"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+w"(x))

/*  On armhf, long double and double are identical. Set this flag for later.  */
#define TMPL_LDOUBLE_BARRIER_SAME_AS_DOUBLE 1

/*  POWER3 through POWER10 (and likely later versions) have FMA instructions. *
 *  Since POWER3 was released in 1998, it is likely that any computer running *
 *  powerpc (32-bit, 64-bit, big-endian, little-endian) will have FMA support *
 *  and a barrier will be needed to protect against optimizations.            */
#elif defined(__powerpc__) || defined(__PPC__) || defined(__ppc__)

/*  PowerPC uses "f" for floating-point registers.                            */
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+f"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))

/*  SPARC and SPARC64 provide FMA instructions that need to be prevented in   *
 *  various routines. The same barrier trick also works on this architecture. */
#elif defined(__sparc__)

/*  On SPARC LEON we need to use a general register.                          */
#if defined(__leon__)

#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+r"(x))

/*  SPARC and SPARC64 (V8 and V9) use "+e" for floating-point registers.      */
#else

#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+e"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+e"(x))

#endif
/*  End of SPARC options.                                                     */

/*  Hewlett-Packard PA-RISC and s390 can use the same trick.                  */
#elif defined(__hppa__) || defined(__s390__)

#define TMPL_FLOAT_BARRIER(x)  __asm__ __volatile__("" : "+f"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))

/*  LoongArch provides the __loongarch_frlen macro for FPU support.           */
#elif defined(__loongarch__)

/*  Use FPU registers if available, and generic if soft float is used.        */
#if defined(__loongarch_frlen) && (__loongarch_frlen >= 32)
#define TMPL_FLOAT_BARRIER(x)  __asm__ __volatile__("" : "+f"(x))
#else
#define TMPL_FLOAT_BARRIER(x)  __asm__ __volatile__("" : "+r"(x))
#endif

/*  Same check for double precision.                                          */
#if defined(__loongarch_frlen) && (__loongarch_frlen >= 64)
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))
#else
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#endif

/*  Motorola 68000 is not guaranteed an FPU. If 68881 registers are available *
 *  then we can define a barrier.                                             */
#elif defined(__m68k__) && (defined(__HAVE_68881__) || defined(__mcffpu__))

#define TMPL_FLOAT_BARRIER(x)  __asm__ __volatile__("" : "+f"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))

/*  MIPS also doesn't always use hardware float. If FPU registers are         *
 *  available, we may provide a barrier.                                      */
#elif defined(__mips__) && defined(__mips_hard_float)

#define TMPL_FLOAT_BARRIER(x)  __asm__ __volatile__("" : "+f"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))

/*  RISC-V is a bit more subtle, we need to examine other macros as well.     */
#elif defined(__riscv)

/*  RISC-V defined the __riscv_flen macro for floating-point support.         */
#if defined(__riscv_flen)

/*  If __riscv_flen is at least 32, then we have single-precision floats.     *
 *  Use a generic fallback to general registers otherwise.                    */
#if __riscv_flen >= 32
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+f"(x))
#else
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#endif

/*  Similarly, if __riscv_flen is at least 64, then we have doubles.          */
#if __riscv_flen >= 64
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))
#else
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#endif

/*  Generic fallback for RISC-V.                                              */
#else

#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+r"(x))

#endif
/*  End of RISC-V options.                                                    */

/*  SuperH with FPU (SH3e / SH4 / SH4A / SH2A-FPU). Single-precision float    *
 *  has the FMAC instruction, so the float barrier is necessary. There is no  *
 *  double FMAC, so the double barrier only prevents associative math         *
 *  optimizations from occurring.                                             */
#elif defined(__SH_FPU_ANY__)
#define TMPL_FLOAT_BARRIER(x)  __asm__ __volatile__("" : "+f"(x))

#if defined(__SH_FPU_DOUBLE__)
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))
#else
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#endif

#else
/*  Else for x86-64 vs. aarch64 vs. ... vs. riscv.                            */

/*  Generic fallback, GCC and Clang provide "r" as a general register.        */
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+r"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+r"(x))

#endif
/*  End of x86-64 vs. aarch64 vs. ... vs. riscv.                              */

/*  Solaris Developer Studio C Compiler provides a similar trick.             */
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

/*  "g" is used for generic registers with Solaris.                           */
#define TMPL_FLOAT_BARRIER(x) __asm__ __volatile__("" : "+g"(x))
#define TMPL_DOUBLE_BARRIER(x) __asm__ __volatile__("" : "+g"(x))

#else
/*  Else for GCC vs. Clang vs. Solaris.                                       */

#define TMPL_FLOAT_BARRIER(x)                                       \
    do {                                                            \
        const volatile float tmpl_tmp_float_barrier_variable = x;   \
        (x) = tmpl_tmp_float_barrier_variable;                      \
    } while (0)

#define TMPL_DOUBLE_BARRIER(x)                                      \
    do {                                                            \
        const volatile double tmpl_tmp_double_barrier_variable = x; \
        (x) = tmpl_tmp_double_barrier_variable;                     \
    } while (0)

#endif
/*  End of GCC vs. Clang vs. Solaris.                                         */

/******************************************************************************
 *                            Long Double Barrier                             *
 ******************************************************************************/

/*  64-bit double representation of long double, use the same barrier.        */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT
#define TMPL_LDOUBLE_BARRIER_SAME_AS_DOUBLE 1

/*  Double-double can use the double barriers twice.                          */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
#define TMPL_LDOUBLE_BARRIER(x)                                                \
    do {                                                                       \
        tmpl_IEEE754_LDouble tmpl_tmp_ld_word;                                 \
        tmpl_tmp_ld_word.r = (x);                                              \
        TMPL_DOUBLE_BARRIER(tmpl_tmp_ld_word.dat[0]);                          \
        TMPL_DOUBLE_BARRIER(tmpl_tmp_ld_word.dat[1]);                          \
        (x) = tmpl_tmp_ld_word.r;                                              \
    } while (0)

/*  80-bit extended and 128-bit quadruple have similar tricks on some         *
 *  architectures when using GCC or clang.                                    */
#elif defined(__GNUC__) || defined(__clang__)

/*  80-bit extended has "+t" with GCC and Clang.                              */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT

#if (defined(__x86_64__) || defined(__i386__))
#define TMPL_LDOUBLE_BARRIER(x) __asm__ __volatile__("" : "+t"(x))
#endif

/*  128-bit has "+w" on aarch64 and "+f" on RISC-V.                           */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

#if defined(__aarch64__)
#define TMPL_LDOUBLE_BARRIER(x) __asm__ __volatile__("" : "+w"(x))

#elif defined(__riscv) && defined(__riscv_flen) && (__riscv_flen >= 128)
#define TMPL_LDOUBLE_BARRIER(x) __asm__ __volatile__("" : "+f"(x))

#endif
/*  End of aarch64 vs. RISC-V.                                                */

#endif
/*  End of 80-bit vs. 128-bit.                                                */

#endif
/*  End of #elif defined(__GNUC__) || defined(__clang__).                     */

#if !defined(TMPL_LDOUBLE_BARRIER)

#if defined(TMPL_LDOUBLE_BARRIER_SAME_AS_DOUBLE)
#define TMPL_LDOUBLE_BARRIER(x) TMPL_DOUBLE_BARRIER(x)
#else

#define TMPL_LDOUBLE_BARRIER(x)                                              \
    do {                                                                     \
        const volatile long double tmpl_tmp_ldouble_barrier_variable = (x);  \
        (x) = tmpl_tmp_ldouble_barrier_variable;                             \
    } while (0)

#endif

#endif

#endif
/*  End of include guard.                                                     */
