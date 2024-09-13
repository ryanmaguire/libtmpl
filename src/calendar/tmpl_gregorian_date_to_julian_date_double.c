#include <libtmpl/include/tmpl_calendar.h>

double
tmpl_Double_Gregorian_Date_To_Julian_Date(signed long int year,
                                          signed long int month,
                                          signed long int day,
                                          signed long int hour,
                                          signed long int minute,
                                          double second)
{
    const signed long int j_day =
        tmpl_Gregorian_Date_To_Julian_Day_Number(year, month, day);

    const double j_hour = (double)(hour - 12L) / 24.0;
    const double j_minute = (double)(minute) / (1440.0);
    const double j_second = (double)(second) / 86400.0;

    return (double)(j_day) + j_hour + j_minute + j_second;
}
