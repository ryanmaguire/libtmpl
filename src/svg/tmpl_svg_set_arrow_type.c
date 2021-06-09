
#include <libtmpl/include/tmpl_svg.h>

void tmpl_SVG_Set_Arrow_Type(tmpl_SVG_Arrow *arrow, tmpl_SVG_ArrowType type)
{
    /*  If the pointer is NULL, the arrow has not been created, or already    *
     *  been destroyed. Abort.                                                */
    if (!arrow)
        return;

    /*  If an error has occured in the arrow, abort.                          */
    if (arrow->error_occured)
        return;

    /*  Otherwise, set the arrow type to the requested value.                 */
    arrow->arrow_type = type;
    return;
}
/*  End of tmpl_SVG_Set_Arrow_Type.                                           */
