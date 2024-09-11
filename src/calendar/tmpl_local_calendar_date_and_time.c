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
 *                     tmpl_local_calendar_date_and_time                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Gets the current date and time as a string.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Local_Calendar_Date_And_Time                                     *
 *  Purpose:                                                                  *
 *      Returns the current date as a string.                                 *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      username (const char *):                                              *
 *          A pointer to a char array, the string for the date.               *
 *  Called Functions:                                                         *
 *      time.h:                                                               *
 *          time:                                                             *
 *              Retrieves the current time.                                   *
 *          localtime:                                                        *
 *              Computes the local time from a given time.                    *
 *          strftime:                                                         *
 *              Computes the date string from a given local time.             *
 *  Method:                                                                   *
 *      Use the time, localtime, and strftime functions to extract the date.  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) time.h:                                                               *
 *          Standard library header providing time functions.                 *
 *  2.) tmpl_utility.h:                                                       *
 *          Header file where the function prototype is provided.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 11, 2024                                            *
 ******************************************************************************/

/*  Time routines provided here.                                              */
#include <time.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_calendar.h>

/*  Global variable for storing the date at the time of the function call.    */
static char tmpl_global_local_date_and_time_string[128];

const char *tmpl_Local_Calendar_Date_And_Time(void)
{
    /*  Total size of the array for the date and time string.                 */
    const size_t arr_len = sizeof(tmpl_global_local_date_and_time_string);

    /*  Current time.                                                         */
    const time_t current_time = time(NULL);

    /*  Convert to local time.                                                */
    const struct tm * const current_local_time = localtime(&current_time);

    /*  Create a string from the current local time with date info on it.     */
    const size_t string_length = strftime(
        tmpl_global_local_date_and_time_string,
        arr_len, "%c", current_local_time
    );

    /*  Check if this failed. If so, return "Unknown" as a fallback.          */
    if (string_length == 0)
        return "Unknown";

    return tmpl_global_local_date_and_time_string;
}
/*  End of tmpl_Local_Calendar_Date_And_Time.                                 */
