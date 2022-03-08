#include <libtmpl/include/tmpl_ppm.h>
#include <stdio.h>

void
tmpl_Text_PGM_From_Data(const char *filename,
                        unsigned char *data,
                        unsigned int width,
                        unsigned int height)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  The file the PPM is being written to.                                 */
    FILE *fp;

    /*  Check for NULL pointers before proceeding.                            */
    if (!data)
        return;

    /*  Open the file and give it write permissions.                          */
    fp = fopen(filename, "w");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!fp)
        return;

    /*  Print the preamble to the PPM file.                                   */
    fprintf(fp, "P2\n%u %u\n255\n", width, height);

    /*  Write all of the data to the file.                                    */
    for (n = 0U; n < width*height; ++n)
        fprintf(fp, "%u\n", data[n]);

    /*  Close the file since we're done with it.                              */
    fclose(fp);
}
/*  End of tmpl_Binary_PPM_From_Data.                                         */
