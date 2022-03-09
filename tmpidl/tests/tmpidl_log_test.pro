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
;                           tmpidl_bessel_log_test                             ;
;******************************************************************************;
;  Purpose:                                                                    ;
;      Time and accuracy test for the IDL wrapper of Log.                      ;
;******************************************************************************;
;  Author:     Ryan Maguire                                                    ;
;  Date:       March 9, 2022                                                   ;
;******************************************************************************;

; IDL wrappers are located here. @ is IDL's equivalent of #include.
@../src/tmpidl_log

; A test for comparing the tmpidl Log with IDL's built-in version.
PRO TEST
    x = DINDGEN(10000001) * 0.0001 + 0.01

    t1  = SYSTIME(/SECONDS)
    y_c = TMPIDL_Log(x)
    t2  = SYSTIME(/SECONDS)

    t3    = SYSTIME(/SECONDS)
    y_idl = ALOG(x, /DOUBLE)
    t4    = SYSTIME(/SECONDS)

    PRINT, "tmpidl Time: ", t2-t1
    PRINT, "IDL Time:    ", t4-t3
    PRINT, "Ratio:       ", (t4-t3)/(t2-t1)
    PRINT, ""
    PRINT, "Max Errors: ", MAX(ABS(y_c-y_idl))
    PRINT, "RMS Error:  ", SQRT(MEAN((y_c-y_idl)^2))
END
