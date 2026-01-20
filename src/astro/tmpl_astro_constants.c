/******************************************************************************
 *                                 LICENSE                                    *
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
 *      Provides common constants that occur in astronomy.                    *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_astro_constants.h:                                               *
 *      Header file where all of these constants are declared.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 20, 2026                                              *
 ******************************************************************************/

/*  All constants are declared in this header file.                           */
#include <libtmpl/include/constants/tmpl_astro_constants.h>

/******************************************************************************
 *                               Speed of Light                               *
 ******************************************************************************/

/*  Speed of light in meters per second.                                      */
const double
tmpl_double_speed_of_light_mps = TMPL_DOUBLE_SPEED_OF_LIGHT_MPS;

const float
tmpl_float_speed_of_light_mps = TMPL_FLOAT_SPEED_OF_LIGHT_MPS;

const long double
tmpl_ldouble_speed_of_light_mps = TMPL_LDOUBLE_SPEED_OF_LIGHT_MPS;

/*  Speed of light in kilometers per second.                                  */
const double
tmpl_double_speed_of_light_kmps = TMPL_DOUBLE_SPEED_OF_LIGHT_KMPS;

const float
tmpl_float_speed_of_light_kmps = TMPL_FLOAT_SPEED_OF_LIGHT_KMPS;

const long double
tmpl_ldouble_speed_of_light_kmps = TMPL_LDOUBLE_SPEED_OF_LIGHT_KMPS;

/******************************************************************************
 *                            Calendar Conversions                            *
 ******************************************************************************/

/*  Number of seconds in an SI day.                                           */
const double
tmpl_double_seconds_per_day = TMPL_DOUBLE_SECONDS_PER_DAY;

const float
tmpl_float_seconds_per_day = TMPL_FLOAT_SECONDS_PER_DAY;

const long double
tmpl_ldouble_seconds_per_day = TMPL_LDOUBLE_SECONDS_PER_DAY;

/*  Number of SI days (86,400 seconds) in a Julian year.                      */
const double
tmpl_double_days_per_julian_year = TMPL_DOUBLE_DAYS_PER_JULIAN_YEAR;

const float
tmpl_float_days_per_julian_year = TMPL_FLOAT_DAYS_PER_JULIAN_YEAR;

const long double
tmpl_ldouble_days_per_julian_year = TMPL_LDOUBLE_DAYS_PER_JULIAN_YEAR;
