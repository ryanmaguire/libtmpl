;******************************************************************************;
;                                 LICENSE                                      ;
;******************************************************************************;
;  This file is part of libtmpl.                                               ;
;                                                                              ;
;  libtmpl is free software: you can redistribute it and/or modify             ;
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
;                            tmpidl_bessel_i0_test                             ;
;******************************************************************************;
;  Purpose:                                                                    ;
;      Time and accuracy test for the IDL wrapper of Bessel I0.                ;
;******************************************************************************;
;  Author:     Ryan Maguire                                                    ;
;  Date:       March 9, 2022                                                   ;
;******************************************************************************;

; IDL wrappers are located here. @ is IDL's equivalent of #include.
@../src/tmpidl_bessel_i0

; A test for comparing the tmpidl Bessel I0 with IDL's built-in version.
PRO TEST
    x = DINDGEN(10000001) * 0.000001

    t1  = SYSTIME(/SECONDS)
    y_c = TMPIDL_BESSEL_I0(x)
    t2  = SYSTIME(/SECONDS)

    t3    = SYSTIME(/SECONDS)
    y_idl = BESELI(x, 0, /DOUBLE)
    t4    = SYSTIME(/SECONDS)

    PRINT, "tmpidl Time: ", t2-t1
    PRINT, "IDL Time:    ", t4-t3
    PRINT, "Ratio:       ", (t4-t3)/(t2-t1)
    PRINT, ""
    PRINT, "Max Errors: ", MAX(ABS(y_c-y_idl)/y_idl)
    PRINT, "RMS Error:  ", SQRT(MEAN(((y_c-y_idl)/y_idl)^2))
END

; Running this on a 2017 iMac 3.4 GHz quad-core intel i5 with Ubuntu-Budgie
; 20.04 gave the following:
;
;   tmpidl Time:       0.28541398
;   IDL Time:          0.90176702
;   Ratio:             3.5159424
;
;   Max Errors:    1.1424720e-15
;   RMS Error:     2.0403930e-16
;
; Running this when libtmpidl was built with OpenMP support gave:
;
;   tmpidl Time:       0.15129614
;   IDL Time:          0.91348004
;   Ratio:             6.0376957
;
;   Max Errors:    1.1424720e-15
;   RMS Error:     2.0403930e-16
;
; These tests were run using GDL - GNU Data Language, Version 0.9.9, a Free and
; Open Source implementation of IDL.
