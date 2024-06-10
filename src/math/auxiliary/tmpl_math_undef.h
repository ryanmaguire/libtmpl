/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
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
 ******************************************************************************/

/*  No include guard needed. A user may wish to include this file twice in    *
 *  the same file to repeat its functionality.                                */

/*  "A" coefficients, usually present in all helper functions that use        *
 *  polynomial expansions or rational approximations.                         */
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef A12
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef A20
#undef A21
#undef A22
#undef A23
#undef A24
#undef A25
#undef A26
#undef A27
#undef A28
#undef A29
#undef A30

/*  "B" coefficients, common in rational expansions that use two polynomials. */
#undef B00
#undef B01
#undef B02
#undef B03
#undef B04
#undef B05
#undef B06
#undef B07
#undef B08
#undef B09
#undef B10
#undef B11
#undef B12
#undef B13
#undef B14
#undef B15
#undef B16
#undef B17
#undef B18
#undef B19
#undef B20
#undef B21
#undef B22
#undef B23
#undef B24
#undef B25
#undef B26
#undef B27
#undef B28
#undef B29
#undef B30

/*  "C" coefficients may appear in a function that uses several polynomials   *
 *  in different windows. Erf is an example of this.                          */
#undef C00
#undef C01
#undef C02
#undef C03
#undef C04
#undef C05
#undef C06
#undef C07
#undef C08
#undef C09
#undef C10
#undef C11
#undef C12
#undef C13
#undef C14
#undef C15
#undef C16
#undef C17
#undef C18
#undef C19
#undef C20
#undef C21
#undef C22
#undef C23
#undef C24
#undef C25
#undef C26
#undef C27
#undef C28
#undef C29
#undef C30

/*  "D" coefficients, for functions using two rational approximations or      *
 *  multiple polynomial expansions.                                           */
#undef D00
#undef D01
#undef D02
#undef D03
#undef D04
#undef D05
#undef D06
#undef D07
#undef D08
#undef D09
#undef D10
#undef D11
#undef D12
#undef D13
#undef D14
#undef D15
#undef D16
#undef D17
#undef D18
#undef D19
#undef D20
#undef D21
#undef D22
#undef D23
#undef D24
#undef D25
#undef D26
#undef D27
#undef D28
#undef D29
#undef D30

/*  "E" coefficients, usually for functions split into many windows.          */
#undef E00
#undef E01
#undef E02
#undef E03
#undef E04
#undef E05
#undef E06
#undef E07
#undef E08
#undef E09
#undef E10
#undef E11
#undef E12
#undef E13
#undef E14
#undef E15
#undef E16
#undef E17
#undef E18
#undef E19
#undef E20
#undef E21
#undef E22
#undef E23
#undef E24
#undef E25
#undef E26
#undef E27
#undef E28
#undef E29
#undef E30

/*  "F" coefficients, for functions split into many windows or using three    *
 *  rational approximations, usually Pade or Remez.                           */
#undef F00
#undef F01
#undef F02
#undef F03
#undef F04
#undef F05
#undef F06
#undef F07
#undef F08
#undef F09
#undef F10
#undef F11
#undef F12
#undef F13
#undef F14
#undef F15
#undef F16
#undef F17
#undef F18
#undef F19
#undef F20
#undef F21
#undef F22
#undef F23
#undef F24
#undef F25
#undef F26
#undef F27
#undef F28
#undef F29
#undef F30

/*  "G" coefficients, for functions needing many windows, like Erf.           */
#undef G00
#undef G01
#undef G02
#undef G03
#undef G04
#undef G05
#undef G06
#undef G07
#undef G08
#undef G09
#undef G10
#undef G11
#undef G12
#undef G13
#undef G14
#undef G15
#undef G16
#undef G17
#undef G18
#undef G19
#undef G20
#undef G21
#undef G22
#undef G23
#undef G24
#undef G25
#undef G26
#undef G27
#undef G28
#undef G29
#undef G30

/*  "H" coefficients, for functions needing many windows, like Erf.           */
#undef H00
#undef H01
#undef H02
#undef H03
#undef H04
#undef H05
#undef H06
#undef H07
#undef H08
#undef H09
#undef H10
#undef H11
#undef H12
#undef H13
#undef H14
#undef H15
#undef H16
#undef H17
#undef H18
#undef H19
#undef H20
#undef H21
#undef H22
#undef H23
#undef H24
#undef H25
#undef H26
#undef H27
#undef H28
#undef H29
#undef H30

/*  "I" and up coefficients are for quadruple and double-double functions     *
 *  needing many windows, like Erf, lambertW, etc.                            */
#undef I00
#undef I01
#undef I02
#undef I03
#undef I04
#undef I05
#undef I06
#undef I07
#undef I08
#undef I09
#undef I10
#undef I11
#undef I12
#undef I13
#undef I14
#undef I15
#undef I16
#undef I17
#undef I18
#undef I19
#undef I20
#undef I21
#undef I22
#undef I23
#undef I24
#undef I25
#undef I26
#undef I27
#undef I28
#undef I29
#undef I30
#undef J00
#undef J01
#undef J02
#undef J03
#undef J04
#undef J05
#undef J06
#undef J07
#undef J08
#undef J09
#undef J10
#undef J11
#undef J12
#undef J13
#undef J14
#undef J15
#undef J16
#undef J17
#undef J18
#undef J19
#undef J20
#undef J21
#undef J22
#undef J23
#undef J24
#undef J25
#undef J26
#undef J27
#undef J28
#undef J29
#undef J30
#undef K00
#undef K01
#undef K02
#undef K03
#undef K04
#undef K05
#undef K06
#undef K07
#undef K08
#undef K09
#undef K10
#undef K11
#undef K12
#undef K13
#undef K14
#undef K15
#undef K16
#undef K17
#undef K18
#undef K19
#undef K20
#undef K21
#undef K22
#undef K23
#undef K24
#undef K25
#undef K26
#undef K27
#undef K28
#undef K29
#undef K30
#undef L00
#undef L01
#undef L02
#undef L03
#undef L04
#undef L05
#undef L06
#undef L07
#undef L08
#undef L09
#undef L10
#undef L11
#undef L12
#undef L13
#undef L14
#undef L15
#undef L16
#undef L17
#undef L18
#undef L19
#undef L20
#undef L21
#undef L22
#undef L23
#undef L24
#undef L25
#undef L26
#undef L27
#undef L28
#undef L29
#undef L30
#undef M00
#undef M01
#undef M02
#undef M03
#undef M04
#undef M05
#undef M06
#undef M07
#undef M08
#undef M09
#undef M10
#undef M11
#undef M12
#undef M13
#undef M14
#undef M15
#undef M16
#undef M17
#undef M18
#undef M19
#undef M20
#undef M21
#undef M22
#undef M23
#undef M24
#undef M25
#undef M26
#undef M27
#undef M28
#undef M29
#undef M30
#undef N00
#undef N01
#undef N02
#undef N03
#undef N04
#undef N05
#undef N06
#undef N07
#undef N08
#undef N09
#undef N10
#undef N11
#undef N12
#undef N13
#undef N14
#undef N15
#undef N16
#undef N17
#undef N18
#undef N19
#undef N20
#undef N21
#undef N22
#undef N23
#undef N24
#undef N25
#undef N26
#undef N27
#undef N28
#undef N29
#undef N30
#undef O00
#undef O01
#undef O02
#undef O03
#undef O04
#undef O05
#undef O06
#undef O07
#undef O08
#undef O09
#undef O10
#undef O11
#undef O12
#undef O13
#undef O14
#undef O15
#undef O16
#undef O17
#undef O18
#undef O19
#undef O20
#undef O21
#undef O22
#undef O23
#undef O24
#undef O25
#undef O26
#undef O27
#undef O28
#undef O29
#undef O30

/*  Helper macros that are often defined to implement Horner's method.        */
#undef TMPL_POLY_EVAL
#undef TMPL_POLYA_EVAL
#undef TMPL_POLYB_EVAL
#undef TMPL_POLYC_EVAL
#undef TMPL_POLYD_EVAL
#undef TMPL_POLYE_EVAL
#undef TMPL_POLYF_EVAL
#undef TMPL_POLYG_EVAL
#undef TMPL_POLYH_EVAL
#undef TMPL_POLYI_EVAL
#undef TMPL_POLYJ_EVAL
#undef TMPL_POLYK_EVAL
#undef TMPL_POLYL_EVAL
#undef TMPL_POLYM_EVAL
#undef TMPL_POLYN_EVAL
#undef TMPL_POLYO_EVAL
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

/*  Constant macros that occur in several functions.                          */
#undef TMPL_PI_BY_TWO

/*  No include guard needed, so no #endif is needed either.                   */