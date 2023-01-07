#ifndef TMPL_ASTRO_H
#define TMPL_ASTRO_H

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

TMPL_EXPORT extern double
tmpl_Double_Gregorian_Date_To_Julian_Date(unsigned long int year,
                                          tmpl_Month month,
                                          unsigned char day,
                                          double hour);

TMPL_EXPORT extern double
tmpl_Double_UTC_To_Julian_Date(double year, double month, double day,
                               double hour, double minute, double second);

#endif
