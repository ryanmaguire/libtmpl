#include <libtmpl/include/tmpl_calendar.h>

signed long int
tmpl_Gregorian_Date_To_Julian_Day_Number(signed long int year,
                                         signed long int month,
                                         signed long int day)
{
    const signed long int factor = (7L*(year + 5001L + (month - 9L)/7L)) / 4L;
    const signed long int scaled_month = (275L * month) / 9L;
    return 367L * year - factor + scaled_month + day + 1729777L;
}
