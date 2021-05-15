
#include <stdio.h>
#include <stdlib.h>

struct pair {
    double x, y;
};

static struct pair add_pairs(struct pair p, struct pair q)
{
    struct pair sum;
    sum.x = p.x + q.x;
    sum.y = p.y + q.y;
    return sum;
}

static struct pair random_pair(void)
{
    double rreal = (double)rand() / (double)RAND_MAX;
    int rint = (int)(6.0 * rreal);
    struct pair out;

    if (rint == 0)
    {
        out.x = 1.0;
        out.y = 0.0;
    }
    else if (rint == 1)
    {
        out.y = 0.86602540378443864;
        out.x = 0.5;
    }
    else if (rint == 2)
    {
        out.y =  0.86602540378443864;
        out.x = -0.5;
    }
    else if (rint == 3)
    {
        out.x = -1.0;
        out.y =  0.0;
    }
    else if (rint == 4)
    {
        out.y = -0.86602540378443864;
        out.x = -0.5;
    }
    else
    {
        out.y = -0.86602540378443864;
        out.x =  0.5;
    }
    return out;
}

int main(void)
{
    unsigned int size = 1000U;
    unsigned int walk_size = 900000U;
    double xmin, xmax, ymin, ymax, xscale, yscale, val;
    struct pair *A = malloc(sizeof(*A) * walk_size);
    unsigned int n;
    unsigned char red, green, blue;
    FILE *fp = fopen("tmpl_random_walk_hexagonal.svg", "w");
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
                "<!DOCTYPE svg PUBLIC "
                "\"-//W3C//DTD SVG 1.1//EN\" "
                "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n "
                "<svg viewBox=\"0 0 %u %u\" "
                "xmlns=\"http://www.w3.org/2000/svg\" "
                "xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
                "<rect fill=\"#000000\" stroke=\"#000\" "
                "x=\"0\" y=\"0\" "
                "width=\"%u\" height=\"%u\"/>\n"
                "<g opacity=\"1.0\">\n",
                size, size, size, size);

    A[0].x = 0.0;
    A[0].y = 0.0;
    xmin = xmax = ymin = ymax = 0.0;
    for (n = 1U; n < walk_size; ++n)
    {
        A[n] = add_pairs(A[n-1], random_pair());
        if (A[n].x > xmax)
            xmax = A[n].x;
        if (A[n].x < xmin)
            xmin = A[n].x;
        if (A[n].y > ymax)
            ymax = A[n].y;
        if (A[n].y < ymin)
            ymin = A[n].y;
    }

    xscale = (double)size / (xmax - xmin);
    yscale = (double)size / (ymax - ymin);

    for (n = 0U; n < walk_size - 1U; ++n)
    {
        val = 1024.0*(double)n / (double)(walk_size - 1U);

        if (val < 256.0)
        {
            red   = (unsigned char)0;
            green = (unsigned char)(val);
            blue  = (unsigned char)255;
        }
        else if (val < 512.0)
        {
            val  -= 256.0;
            red   = (unsigned char)0;
            green = (unsigned char)255;
            blue  = (unsigned char)(256.0 - val);
        }
        else if (val < 768.0)
        {
            val  -= 512.0;
            red   = (unsigned char)(val);
            green = (unsigned char)255;
            blue  = (unsigned char)0;
        }
        else
        {
            val  -= 768.0;
            red   = (unsigned char)255;
            green = (unsigned char)(256.0 - val);
            blue  = (unsigned char)0;
        }

        fprintf(fp, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" "
                    "stroke=\"#%02x%02x%02x\" stroke-width=\"0.5\" />\n",
                    xscale * (A[n].x - xmin),
                    yscale * (A[n].y - ymin),
                    xscale * (A[n+1].x - xmin),
                    yscale * (A[n+1].y - ymin),
                    red, green, blue);
    }
    free(A);
    fprintf(fp, "</g>\n</svg>\n");
    return 0;
}

