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
;                            tmpidl_bessel_j0_test                             ;
;******************************************************************************;
;  Purpose:                                                                    ;
;      Time and accuracy test for the IDL wrapper of Bessel J0.                ;
;******************************************************************************;
;  Author:     Ryan Maguire                                                    ;
;  Date:       March 9, 2022                                                   ;
;******************************************************************************;

; IDL wrappers are located here. @ is IDL's equivalent of #include.
@../tmpidl_special_functions

; A test for comparing the tmpidl Bessel J0 with IDL's built-in version.
PRO TEST
    x = DINDGEN(10000001) * 0.0001

    t1  = SYSTIME(/SECONDS)
    y_c = BESSEL_J0(x)
    t2  = SYSTIME(/SECONDS)

    t3    = SYSTIME(/SECONDS)
    y_idl = BESELJ(x, 0, /DOUBLE)
    t4    = SYSTIME(/SECONDS)

    PRINT, "tmpidl Time: ", t2-t1
    PRINT, "IDL Time:    ", t4-t3
    PRINT, "Ratio:       ", (t4-t3)/(t2-t1)
    PRINT, ""
    PRINT, "Max Errors: ", MAX(ABS(y_c-y_idl))
    PRINT, "RMS Error:  ", SQRT(MEAN((y_c-y_idl)^2))
END

; Running this on a 2017 iMac 3.4 GHz quad-core intel i5 with Ubuntu-Budgie
; 20.04 gave the following:
;
;   tmpidl Time:    0.42873502
;   IDL Time:        1.8394210
;   Ratio:           4.2903448
;
;   Max Errors:    1.3093551e-10
;   RMS Error:     4.8522063e-12
;
; Running this when libtmpidl was built with OpenMP support gave:
;
;   tmpidl Time:    0.19176412
;   IDL Time:        1.8159111
;   Ratio:           9.4695039
;
;   Max Errors:    1.3093551e-10
;   RMS Error:     4.8522063e-12
;
; These tests were run using GDL - GNU Data Language, Version 0.9.9, a Free and
; Open Source implementation of IDL.
