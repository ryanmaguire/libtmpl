/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)DEFS.h	5.1 (Berkeley) 4/23/90
 * $FreeBSD: src/sys/amd64/include/asm.h,v 1.18 2007/08/22 04:26:07 jkoshy Exp $
 */

#ifndef _BSD_ASM_H_
#define _BSD_ASM_H_

#ifdef __APPLE__
#include "../i387/osx_asm.h"
#define CNAME(x) EXT(x)
#else

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

#if __GNUC__ >= 3 || defined(__INTEL_COMPILER)
#define __GNUCLIKE_ASM 3
#else
#define __GNUCLIKE_ASM 2
#endif

#define __CC_SUPPORTS___INLINE__ 1

#endif /* __GNUC__ || __INTEL_COMPILER */

#if defined(__STDC__) || defined(__cplusplus)

#define	__volatile	volatile
#if defined(__cplusplus)
#define	__inline	inline		/* convert to C++ keyword */
#else
#if !defined(__CC_SUPPORTS___INLINE)
#define	__inline			/* delete GCC keyword */
#endif /* ! __CC_SUPPORTS___INLINE */
#endif /* !__cplusplus */

#else	/* !(__STDC__ || __cplusplus) */

#if !defined(__CC_SUPPORTS___INLINE)
#define	__inline
#define	__volatile
#endif	/* !__CC_SUPPORTS___INLINE */
#endif	/* !(__STDC__ || __cplusplus) */

/*
 * Macro to test if we're using a specific version of gcc or later.
 */
#ifndef __GNUC_PREREQ__
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__GNUC_PREREQ__(ma, mi)	\
	(__GNUC__ > (ma) || __GNUC__ == (ma) && __GNUC_MINOR__ >= (mi))
#else
#define	__GNUC_PREREQ__(ma, mi)	0
#endif
#endif /* __GNUC_PREREQ__ */

/*
 * Compiler-dependent macro to help declare pure (no side effects) functions.
 * It is null except for versions of gcc that are known to support the features
 * properly (old versions of gcc-2 supported the dead and pure features
 * in a different (wrong) way), and for icc.  If we do not provide an implementation
 * for a given compiler, let the compile fail if it is told to use
 * a feature that we cannot live without.
 */
#if !defined(__pure2) && (__GNUC_PREREQ__(2, 7) || defined(__INTEL_COMPILER))
#define	__pure2		__attribute__((__const__))
#endif

#ifdef PIC
#define	PIC_PLT(x)	x@PLT
#define	PIC_GOT(x)	x@GOTPCREL(%rip)
#else
#define	PIC_PLT(x)	x
#define	PIC_GOT(x)	x
#endif

/*
 * CNAME and HIDENAME manage the relationship between symbol names in C
 * and the equivalent assembly language names.  CNAME is given a name as
 * it would be used in a C program.  It expands to the equivalent assembly
 * language name.  HIDENAME is given an assembly-language name, and expands
 * to a possibly-modified form that will be invisible to C programs.
 */
#define CNAME(csym)		csym
#define HIDENAME(asmsym)	.asmsym

#define _START_ENTRY	.p2align 4,0x90

#if defined(__ELF__)
#define _ENTRY(x)	.text; _START_ENTRY; \
			.globl CNAME(x); .type CNAME(x),@function; CNAME(x):
#define	END(x)		.size x, . - x

#elif defined(_WIN32)
#ifndef _MSC_VER
#define END(x) .end
#define _START_ENTRY_WIN .text; _START_ENTRY
#else
#define END(x) end
#define _START_ENTRY_WIN .code; _START_ENTRY
#endif
#define _ENTRY(x)	_START_ENTRY_WIN; \
            .globl CNAME(x); .section .drectve; .ascii " -export:", #x; \
            .section .text; .def CNAME(x); .scl 2; .type 32; .endef; CNAME(x):
#endif

#ifdef PROF
#define	ALTENTRY(x)	_ENTRY(x); \
			pushq %rbp; movq %rsp,%rbp; \
			call PIC_PLT(HIDENAME(mcount)); \
			popq %rbp; \
			jmp 9f
#define	ENTRY(x)	_ENTRY(x); \
			pushq %rbp; movq %rsp,%rbp; \
			call PIC_PLT(HIDENAME(mcount)); \
			popq %rbp; \
			9:
#else
#define	ALTENTRY(x)	_ENTRY(x)
#define	ENTRY(x)	_ENTRY(x)
#endif


#define RCSID(x)	.text; .asciz x

#undef __FBSDID
#if !defined(lint) && !defined(STRIP_FBSDID)
#define __FBSDID(s)	.ident s
#else
#define __FBSDID(s)	/* nothing */
#endif /* not lint and not STRIP_FBSDID */

#endif
#endif /* !_BSD_ASM_H_ */
