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
 *                                 tmpl_fft                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for Fourier analysis such as FFT's and Convolutions.    *
 *  NOTES:                                                                    *
 *      This file is a fork of the complex library I wrote for rss_ringoccs.  *
 *      rss_ringoccs is also released under GPL 3.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 2, 2021                                              *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/02/02 (Ryan Maguire):                                                *
 *      Copied from rss_ringoccs.                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_FFT_H__
#define __TMPL_FFT_H__

/*  Booleans defined here. Needed for the FFT routines.                       */
#include <libtmpl/include/tmpl_bool.h>

/*  Complex data types and functions defined here.                            */
#include <libtmpl/include/tmpl_complex.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_FFT_Cooley_Tukey                                         *
 *  Purpose:                                                                  *
 *      Computes the FFT of a data set that has 2^N entries for some          *
 *      non-negative integer N using the classic Cooley-Tukey algorithm.      *
 *  Arguments:                                                                *
 *      tmpl_ComplexDouble *in:                                               *
 *          A pointer to a tmpl_ComplexDouble array. This is the complex data.*
 *      tmpl_ComplexDouble *out:                                              *
 *          A pointer to a tmply_ComplexDouble array. The FFT of in is stored *
 *          in this pointer when the function is done.                        *
 *      unsigned long N:                                                      *
 *          The number of entries in the array in. This MUST be a power of 2. *
 *      tmpl_Bool inverse:                                                    *
 *          A Boolean for determining if the forward or inverse FFT is        *
 *          computed.                                                         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  NOTES:                                                                    *
 *      It is assumed that in and out have had sufficient memory allocated to *
 *      them BEFORE using this function. Improper usage may result in         *
 *      segmentation faults and crashes. See libtmpl/examples/fft_examples/   *
 *      for complete examples of proper usage.                                *
 ******************************************************************************/
extern void
tmpl_CDouble_FFT_Cooley_Tukey(tmpl_ComplexDouble *in, tmpl_ComplexDouble *out,
                              unsigned long N, tmpl_Bool inverse);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_FFT_Bluestein_Chirp_Z                                    *
 *  Purpose:                                                                  *
 *      Computes the FFT of a data set that has an arbitrary number of        *
 *      elements using the Bluestein convolution method.                      *
 *  Arguments:                                                                *
 *      tmpl_ComplexDouble *in:                                               *
 *          A pointer to a tmpl_ComplexDouble array. This is the complex data.*
 *      tmpl_ComplexDouble *out:                                              *
 *          A pointer to a tmply_ComplexDouble array. The FFT of in is stored *
 *          in this pointer when the function is done.                        *
 *      unsigned long N:                                                      *
 *          The number of entries in the array in (and out).                  *
 *      tmpl_Bool inverse:                                                    *
 *          A Boolean for determining if the forward or inverse FFT is        *
 *          computed.                                                         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  NOTES:                                                                    *
 *      It is assumed that in and out have had sufficient memory allocated to *
 *      them BEFORE using this function. Improper usage may result in         *
 *      segmentation faults and crashes. See libtmpl/examples/fft_examples/   *
 *      for complete examples of proper usage.                                *
 ******************************************************************************/
extern tmpl_ComplexDouble *
tmpl_CDouble_FFT_Bluestein_Chirp_Z(tmpl_ComplexDouble *in,
                                   tmpl_ComplexDouble *out,
                                   unsigned long N, tmpl_Bool inverse);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_FFT                                                      *
 *  Purpose:                                                                  *
 *      Computes the FFT of a data set in of arbitrary length. This will use  *
 *      the Cooley-Tukey method if N is a power of 2 and the Bluestein method *
 *      otherwise. It is provided for convenience.                            *
 *  Arguments:                                                                *
 *      tmpl_ComplexDouble *in:                                               *
 *          A pointer to a tmpl_ComplexDouble array. This is the complex data.*
 *      tmpl_ComplexDouble *out:                                              *
 *          A pointer to a tmply_ComplexDouble array. The FFT of in is stored *
 *          in this pointer when the function is done.                        *
 *      unsigned long N:                                                      *
 *          The number of entries in the array in (and out).                  *
 *      tmpl_Bool inverse:                                                    *
 *          A Boolean for determining if the forward or inverse FFT is        *
 *          computed.                                                         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  NOTES:                                                                    *
 *      It is assumed that in and out have had sufficient memory allocated to *
 *      them BEFORE using this function. Improper usage may result in         *
 *      segmentation faults and crashes. See libtmpl/examples/fft_examples/   *
 *      for complete examples of proper usage.                                *
 ******************************************************************************/
extern tmpl_ComplexDouble *
tmpl_CDouble_FFT(tmpl_ComplexDouble *in, tmpl_ComplexDouble *out,
                 unsigned long N, tmpl_Bool inverse);

#endif
/*  End of include guard.                                                     */

