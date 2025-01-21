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
#ifndef TMPL_H
#define TMPL_H

#include <libtmpl/include/types/tmpl_complex_double.h>
#include <libtmpl/include/types/tmpl_complex_float.h>
#include <libtmpl/include/types/tmpl_complex_function_double.h>
#include <libtmpl/include/types/tmpl_complex_function_float.h>
#include <libtmpl/include/types/tmpl_complex_function_ldouble.h>
#include <libtmpl/include/types/tmpl_complex_functional_double.h>
#include <libtmpl/include/types/tmpl_complex_functional_float.h>
#include <libtmpl/include/types/tmpl_complex_functional_ldouble.h>
#include <libtmpl/include/types/tmpl_complex_ldouble.h>
#include <libtmpl/include/types/tmpl_complex_path_double.h>
#include <libtmpl/include/types/tmpl_complex_path_float.h>
#include <libtmpl/include/types/tmpl_complex_path_ldouble.h>
#include <libtmpl/include/types/tmpl_doubledouble_double.h>
#include <libtmpl/include/types/tmpl_doubledouble_ldouble.h>
#include <libtmpl/include/types/tmpl_floatint_double.h>
#include <libtmpl/include/types/tmpl_floatint_float.h>
#include <libtmpl/include/types/tmpl_floatint_ldouble.h>
#include <libtmpl/include/types/tmpl_function_double.h>
#include <libtmpl/include/types/tmpl_function_float.h>
#include <libtmpl/include/types/tmpl_function_ldouble.h>
#include <libtmpl/include/types/tmpl_ieee754_double.h>
#include <libtmpl/include/types/tmpl_ieee754_float.h>
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>
#include <libtmpl/include/types/tmpl_integer_function_types.h>
#include <libtmpl/include/types/tmpl_mat3x3_double.h>
#include <libtmpl/include/types/tmpl_mat3x3_float.h>
#include <libtmpl/include/types/tmpl_mat3x3_ldouble.h>
#include <libtmpl/include/types/tmpl_rgb.h>
#include <libtmpl/include/types/tmpl_rgb24.h>
#include <libtmpl/include/types/tmpl_rgb30.h>
#include <libtmpl/include/types/tmpl_rgb48.h>
#include <libtmpl/include/types/tmpl_rgba.h>
#include <libtmpl/include/types/tmpl_rgba24.h>
#include <libtmpl/include/types/tmpl_rgba30.h>
#include <libtmpl/include/types/tmpl_rgba48.h>
#include <libtmpl/include/types/tmpl_vec3_double.h>
#include <libtmpl/include/types/tmpl_vec3_float.h>
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>
#include <libtmpl/include/tmpl.h>
#include <libtmpl/include/tmpl_array_integer.h>
#include <libtmpl/include/tmpl_astro.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_bytes.h>
#include <libtmpl/include/tmpl_calendar.h>
#include <libtmpl/include/tmpl_color.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>
#include <libtmpl/include/tmpl_differentiation_real.h>
#include <libtmpl/include/tmpl_doubledouble.h>
#include <libtmpl/include/tmpl_fft.h>
#include <libtmpl/include/tmpl_float.h>
#include <libtmpl/include/tmpl_fraunhofer_diffraction.h>
#include <libtmpl/include/tmpl_fresnel_diffraction.h>
#include <libtmpl/include/tmpl_graph_theory.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_integration.h>
#include <libtmpl/include/tmpl_interpolate.h>
#include <libtmpl/include/tmpl_inttype.h>
#include <libtmpl/include/tmpl_knots.h>
#include <libtmpl/include/tmpl_limits.h>
#include <libtmpl/include/tmpl_mat3x3.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_matrix.h>
#include <libtmpl/include/tmpl_optics.h>
#include <libtmpl/include/tmpl_orthogonal_polynomial_real.h>
#include <libtmpl/include/tmpl_polynomial.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <libtmpl/include/tmpl_polynomial_matrix_integer.h>
#include <libtmpl/include/tmpl_ppm.h>
#include <libtmpl/include/tmpl_quadruple.h>
#include <libtmpl/include/tmpl_quaternion.h>
#include <libtmpl/include/tmpl_random.h>
#include <libtmpl/include/tmpl_rational.h>
#include <libtmpl/include/tmpl_root_finding_complex.h>
#include <libtmpl/include/tmpl_root_finding_real.h>
#include <libtmpl/include/tmpl_sort.h>
#include <libtmpl/include/tmpl_sparse_polynomial_integer.h>
#include <libtmpl/include/tmpl_special_functions_complex.h>
#include <libtmpl/include/tmpl_special_functions_real.h>
#include <libtmpl/include/tmpl_spherical_geometry.h>
#include <libtmpl/include/tmpl_split.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_svg.h>
#include <libtmpl/include/tmpl_two_prod.h>
#include <libtmpl/include/tmpl_two_sum.h>
#include <libtmpl/include/tmpl_utility.h>
#include <libtmpl/include/tmpl_vec2.h>
#include <libtmpl/include/tmpl_vec3.h>
#include <libtmpl/include/tmpl_vector_complex.h>
#include <libtmpl/include/tmpl_vector_integer.h>
#include <libtmpl/include/tmpl_vector_real.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <libtmpl/include/tmpl_where.h>
#include <libtmpl/include/tmpl_window_functions.h>


#endif
