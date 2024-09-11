#ifndef TMPL_UTILITY_H
#define TMPL_UTILITY_H

#include <stdio.h>

extern size_t tmpl_Line_Count(FILE *fp);
extern size_t tmpl_CSV_Column_Count(FILE *fp);

extern const char *tmpl_Host_Name(void);
extern const char *tmpl_User_Name(void);
extern const char *tmpl_Operating_System(void);
extern const char *tmpl_Version(void);

#endif
