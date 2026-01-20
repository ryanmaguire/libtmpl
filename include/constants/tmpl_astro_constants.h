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
 ******************************************************************************
 *                            tmpl_astro_constants                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides common constants in astronomy.                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 20, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ASTRO_CONSTANTS_H
#define TMPL_ASTRO_CONSTANTS_H

/******************************************************************************
 *                               Speed of Light                               *
 ******************************************************************************/

/*  Speed of light in meters per second.                                      */
#define TMPL_DOUBLE_SPEED_OF_LIGHT_MPS (2.99792458E+08)
#define TMPL_FLOAT_SPEED_OF_LIGHT_MPS (2.99792458E+08F)
#define TMPL_LDOUBLE_SPEED_OF_LIGHT_MPS (2.99792458E+08L)

/*  Speed of light in kilometers per second.                                  */
#define TMPL_DOUBLE_SPEED_OF_LIGHT_KMPS (2.99792458E+05)
#define TMPL_FLOAT_SPEED_OF_LIGHT_KMPS (2.99792458E+05F)
#define TMPL_LDOUBLE_SPEED_OF_LIGHT_KMPS (2.99792458E+05L)

/******************************************************************************
 *                            Calendar Conversions                            *
 ******************************************************************************/

/*  Number of seconds in an SI day.                                           */
#define TMPL_DOUBLE_SECONDS_PER_DAY (8.64E+04)
#define TMPL_FLOAT_SECONDS_PER_DAY (8.64E+04F)
#define TMPL_LDOUBLE_SECONDS_PER_DAY (8.64E+04L)

/*  Number of SI days (86,400 seconds) in a Julian year.                      */
#define TMPL_DOUBLE_DAYS_PER_JULIAN_YEAR (3.6525E+02)
#define TMPL_FLOAT_DAYS_PER_JULIAN_YEAR (3.6525E+02F)
#define TMPL_LDOUBLE_DAYS_PER_JULIAN_YEAR (3.6525E+02L)

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                               Speed of Light                               *
 ******************************************************************************/

/*  Speed of light in meters per second.                                      */
extern const double tmpl_double_speed_of_light_mps;
extern const float tmpl_float_speed_of_light_mps;
extern const long double tmpl_ldouble_speed_of_light_mps;

/*  Speed of light in kilometers per second.                                  */
extern const double tmpl_double_speed_of_light_kmps;
extern const float tmpl_float_speed_of_light_kmps;
extern const long double tmpl_ldouble_speed_of_light_kmps;

/******************************************************************************
 *                            Calendar Conversions                            *
 ******************************************************************************/

/*  Number of seconds in an SI day.                                           */
extern const double tmpl_double_seconds_per_day;
extern const float tmpl_float_seconds_per_day;
extern const long double tmpl_ldouble_seconds_per_day;

/*  Number of SI days (86,400 seconds) in a Julian year.                      */
extern const double tmpl_double_days_per_julian_year;
extern const float tmpl_float_days_per_julian_year;
extern const long double tmpl_ldouble_days_per_julian_year;

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
