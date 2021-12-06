;******************************************************************************;
;                                 LICENSE                                      ;
;******************************************************************************;
;  This file is part of libtmpl.                                               ;
;                                                                              ;
;  libtmpl is free software: you can redistribute it and/or modify it          ;
;  it under the terms of the GNU General Public License as published by        ;
;  the Free Software Foundation, either version 3 of the License, or           ;
;  (at your option) any later version.                                         ;
;                                                                              ;
;  libtmpl is distributed in the hope that it will be useful,                  ;
;  but WITHOUT ANY WARRANTY; without even the implied warranty of              ;
;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               ;
;  GNU General Public License for more details.                                ;
;                                                                              ;
;  You should have received a copy of the GNU General Public License           ;
;  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.           ;
;******************************************************************************;
;                             tmpl_idl_bessel_j0                               ;
;******************************************************************************;
;  Purpose:                                                                    ;
;      Provide an example of using the C-IDL API to call libtmpl               ;
;      functions in IDL.                                                       ;
;******************************************************************************;
;  Author:     Ryan Maguire, Wellesley College                                 ;
;  Date:       December 3, 2020                                                ;
;******************************************************************************;

; Function for computing the Bessel J0 function via the library libtmpl.
FUNCTION BESSEL_J0, x

    ; libtmpl wants a double, so convert if necessary.
    x = DOUBLE(x)

    ; Get the number of elements in the input array.
    n = LONG(N_ELEMENTS(x))

    ; Create an empty array to store the values.
    result = DBLARR(n)

    ; Use 'call_external' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('./tmpl_idl_bessel_j0.so', $
                      'tmpl_IDL_Bessel_J0',      $
                       x, n, result)

    ; The output has been stored in result, so return this.
    RETURN, result
END

; A little test for comparing the libtmpl Bessel J0 with
; IDL's built-in version.
PRO TEST
    x = DINDGEN(100000)*0.001

    t1  = SYSTIME(/SECONDS)
    y_c = BESSEL_J0(x)
    t2  = SYSTIME(/SECONDS)

    t3    = SYSTIME(/SECONDS)
    y_idl = BESELJ(x, 0)
    t4    = SYSTIME(/SECONDS)

    PRINT, "C Time:   ", t2-t1
    PRINT, "IDL Time: ", t4-t3
    PRINT, "Ratio:    ", (t4-t3)/(t2-t1)
    PRINT, ""
    PRINT, "Max Errors: ", MAX(ABS(y_c-y_idl))
    PRINT, "RMS Error:  ", SQRT(MEAN((y_c-y_idl)^2))
END

; Running this on a 2017 iMac 3.4 GHz quad-core intel i5 with Catalini 10.15.17
; gave the following:
;
;   C Time:      0.0029559135
;   IDL Time:    0.0062208176
;
;   Max Errors:   2.2359086e-09
;   RMS Error:    1.6999667e-10
;
; Not bad! More then twice as fast and within double precision.
; Note, if we run this in a basic time test using C:
;
;   #include <stdio.h>
;   #include <stdlib.h>
;   #include <time.h>
;   #include <libtmpl/include/tmpl_special_functions.h>
;
;   int main(void)
;   {
;       double *x, *y, dx;
;       clock_t t1, t2;
;       int n, N;
;
;       N  = 100000;
;       dx = 0.001;
;
;       x = malloc(sizeof(*x)*N);
;       y = malloc(sizeof(*y)*N);
;
;       for (n=0; n<N; ++n)
;           x[n] = dx*n;
;
;       t1 = clock();
;       for (n=0; n<N; ++n)
;           y[n] = tmpl_Double_Bessel_J0(x[n]);
;       t2 = clock();
;
;       printf("Time: %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
;       free(x);
;       free(y);
;       return 0;
;   }
;
; Compiling with:
;   gcc test.c -O3 -o test -ltmpl
;
; The output is:
;   Time: 0.002859
;
; Which is barely different from IDL making the call to libtmpl.
