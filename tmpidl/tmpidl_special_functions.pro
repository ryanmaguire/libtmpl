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
;                           tmpidl_special_functions                           ;
;******************************************************************************;
;  Purpose:                                                                    ;
;      Provide IDL wrappers for libtmpl's special functions library.           ;
;******************************************************************************;
;  Author:     Ryan Maguire                                                    ;
;  Date:       March 9, 2022                                                   ;
;******************************************************************************;

; Function for computing the Bessel I0 function via the library libtmpl.
FUNCTION BESSEL_I0, x

    ; libtmpl wants a double, so convert if necessary.
    x = DOUBLE(x)

    ; Get the number of elements in the input array.
    n = LONG(N_ELEMENTS(x))

    ; Create an empty array to store the values.
    result = DBLARR(n)

    ; Use 'call_external' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('/usr/local/lib/libtmpidl.so', $
                      'tmpidl_Bessel_I0', x, n, result)

    ; The output has been stored in result, so return this.
    RETURN, result
END

; Function for computing the Bessel J0 function via the library libtmpl.
FUNCTION BESSEL_J0, x

    ; libtmpl wants a double, so convert if necessary.
    x = DOUBLE(x)

    ; Get the number of elements in the input array.
    n = LONG(N_ELEMENTS(x))

    ; Create an empty array to store the values.
    result = DBLARR(n)

    ; Use 'call_external' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('/usr/local/lib/libtmpidl.so', $
                      'tmpidl_Bessel_J0', x, n, result)

    ; The output has been stored in result, so return this.
    RETURN, result
END

; Function for computing the Lambert W function via the library libtmpl.
FUNCTION LAMBERTW, x

    ; libtmpl wants a double, so convert if necessary.
    x = DOUBLE(x)

    ; Get the number of elements in the input array.
    n = LONG(N_ELEMENTS(x))

    ; Create an empty array to store the values.
    result = DBLARR(n)

    ; Use 'call_external' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('/usr/local/lib/libtmpidl.so', $
                      'tmpidl_LambertW', x, n, result)

    ; The output has been stored in result, so return this.
    RETURN, result
END

; Function for computing the Bessel I0 function via the library libtmpl.
FUNCTION FRESNEL_COS, x

    ; libtmpl wants a double, so convert if necessary.
    x = DOUBLE(x)

    ; Get the number of elements in the input array.
    n = LONG(N_ELEMENTS(x))

    ; Create an empty array to store the values.
    result = DBLARR(n)

    ; Use 'call_external' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('/usr/local/lib/libtmpidl.so', $
                      'tmpidl_Fresnel_Cos', x, n, result)

    ; The output has been stored in result, so return this.
    RETURN, result
END

; Function for computing the Bessel I0 function via the library libtmpl.
FUNCTION FRESNEL_SIN, x

    ; libtmpl wants a double, so convert if necessary.
    x = DOUBLE(x)

    ; Get the number of elements in the input array.
    n = LONG(N_ELEMENTS(x))

    ; Create an empty array to store the values.
    result = DBLARR(n)

    ; Use 'call_external' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('/usr/local/lib/libtmpidl.so', $
                      'tmpidl_Fresnel_Sin', x, n, result)

    ; The output has been stored in result, so return this.
    RETURN, result
END
