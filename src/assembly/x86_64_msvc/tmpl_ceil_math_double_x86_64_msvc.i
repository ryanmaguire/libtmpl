;------------------------------------------------------------------------------;
;                                   LICENSE                                    ;
;------------------------------------------------------------------------------;
;   This file is part of libtmpl.                                              ;
;                                                                              ;
;   libtmpl is free software: you can redistribute it and/or modify it         ;
;   under the terms of the GNU General Public License as published by          ;
;   the Free Software Foundation, either version 3 of the License, or          ;
;   (at your option) any later version.                                        ;
;                                                                              ;
;   libtmpl is distributed in the hope that it will be useful,                 ;
;   but WITHOUT ANY WARRANTY; without even the implied warranty of             ;
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              ;
;   GNU General Public License for more details.                               ;
;                                                                              ;
;   You should have received a copy of the GNU General Public License          ;
;   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          ;
;------------------------------------------------------------------------------;
;                               tmpl_ceil_double                               ;
;------------------------------------------------------------------------------;
;   Purpose:                                                                   ;
;     	Computes the ceiling function at double precision.                     ;
;------------------------------------------------------------------------------;
;   Author:     Ryan Maguire                                                   ;
;   Date:       May 22, 2026                                                   ;
;------------------------------------------------------------------------------;
.code

PUBLIC tmpl_Double_Ceil

tmpl_Double_Ceil PROC
    roundsd xmm0, xmm0, 10
    ret
tmpl_Double_Ceil ENDP

END
