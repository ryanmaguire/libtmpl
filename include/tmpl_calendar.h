#ifndef TMPL_CALENDAR_H
#define TMPL_CALENDAR_H

#include <libtmpl/include/tmpl_bool.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    tmpl_January = 1,
    tmpl_February,
    tmpl_March,
    tmpl_April,
    tmpl_May,
    tmpl_June,
    tmpl_July,
    tmpl_August,
    tmpl_September,
    tmpl_October,
    tmpl_November,
    tmpl_December
} tmpl_Month;

typedef enum {
    tmpl_Monday = 1,
    tmpl_Tuesday,
    tmpl_Wednesday,
    tmpl_Thursday,
    tmpl_Friday,
    tmpl_Saturday,
    tmpl_Sunday
} tmpl_Weekday;

extern signed long int
tmpl_Gregorian_Date_To_Julian_Day_Number(signed long int year,
                                         signed long int month,
                                         signed long int day);

extern double
tmpl_Double_Gregorian_Date_To_Julian_Date(signed long int year,
                                          signed long int month,
                                          signed long int day,
                                          signed long int hour,
                                          signed long int minute,
                                          double second);

extern double
tmpl_Double_UTC_To_Julian_Date(double year, double month, double day,
                               double hour, double minute, double second);

extern const char *tmpl_Local_Calendar_Date_And_Time(void);

extern tmpl_Bool tmpl_Year_Is_Leap(int year);

extern int tmpl_Day_Of_Year(int year, int month, int day);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
