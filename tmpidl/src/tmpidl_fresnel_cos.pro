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
;                              tmpidl_fresnel_cos                              ;
;******************************************************************************;
;  Purpose:                                                                    ;
;      Provide IDL wrappers for libtmpl's Fresnel Cosine function.             ;
;******************************************************************************;
;  Author:     Ryan Maguire                                                    ;
;  Date:       March 9, 2022                                                   ;
;******************************************************************************;

FUNCTION TMPIDL_FRESNEL_COS, x

    ; libtmpl wants a double, so convert if necessary.
    IF TYPENAME(x) NE "DOUBLE" THEN in = DOUBLE(x) ELSE in = x

    ; Get the number of elements in the input array.
    n = LONG(N_ELEMENTS(x))

    ; Create an empty array to store the values.
    out = DBLARR(n)

    ; Use 'call_external' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('/usr/local/lib/libtmpidl.so', $
                      'tmpidl_Fresnel_Cos', in, n, out)

    ; The output has been stored in out, so return this.
    RETURN, out
END
