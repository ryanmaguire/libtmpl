#ifndef TMPL_MINMAX_H
#define TMPL_MINMAX_H

#define TMPL_MAX(x, y) ((x) < (y) ? (y) : (x))
#define TMPL_MIN(x, y) ((x) < (y) ? (x) : (y))

#define TMPL_MAX3(x, y, z) ((x) < (y) ? TMPL_MAX((y), (z)) : TMPL_MAX((x), (z)))
#define TMPL_MIN3(x, y, z) ((x) < (y) ? TMPL_MIN((x), (z)) : TMPL_MIN((y), (z)))

#endif
