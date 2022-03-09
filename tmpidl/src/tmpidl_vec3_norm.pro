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
;                               tmpidl_vec3_norm                               ;
;******************************************************************************;
;   Purpose:                                                                   ;
;       Provide IDL wrappers for libtmpl's 3D Euclidean Norm function.         ;
;   Input:                                                                     ;
;       Real array that is 3N in size.                                         ;
;   Output:                                                                    ;
;       Real array that is N in size, y = ||x|| where ||.|| is the standard    ;
;       Euclidean norm.                                                        ;
;******************************************************************************;
;  Author:     Ryan Maguire                                                    ;
;  Date:       March 9, 2022                                                   ;
;******************************************************************************;

FUNCTION TMPIDL_VEC3_NORM, x

    ; Set error handling.
    ON_ERROR, 2

    ; Extract the number of elements from the array.
    n = ULONG(N_ELEMENTS(x))

    ; The input is expected to be three dimensional.
    IF n MOD 3UL NE 0UL THEN MESSAGE, "Input must be 3-dimensional."

    ; The number of vectors is the total number of elements divided by 3.
    n = ULONG(n / 3UL)

    ; libtmpl wants double precision, so convert if necessary.
    IF TYPENAME(x) NE "DOUBLE" THEN in = DOUBLE(x) ELSE in = x

    ; Create an empty array to store the values.
    out = DBLARR(n)

    ; Use 'CALL_EXTERNAL' to pass the IDL parameters to the C code.
    s = CALL_EXTERNAL('/usr/local/lib/libtmpidl.so', $
                      'tmpidl_Vec3_Norm', in, n, out)

    ; The output has been stored in out, so return this.
    RETURN, out
END
