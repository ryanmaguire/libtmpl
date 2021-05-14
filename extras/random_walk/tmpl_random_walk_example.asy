import settings;
import palette;

if (settings.render < 0)
    settings.render = 8;

settings.outformat   = "pdf";

int max = 32765;

size(max + 100, max + 100);

int n;
int walk;
real factor;
pair A = (0.0, 0.0);
pair B = (0.0, 0.0);
pen[] mypen = Rainbow(max);

int Rint()
{
    return (int)floor(4.0 * (rand() / randMax));
}

for (n=0; n<max; ++n)
{
    walk   = Rint();
    factor = 1.0;

    if (walk == 0)
        B = A + (factor, 0);
    else if (walk == 1)
        B = A + (-factor, 0);
    else if (walk == 2)
        B = A + (0, factor);
    else
        B = A + (0, -factor);

    draw(A--B, mypen[n]);
    A = B;
}

shipout(bbox(currentpicture, Black, Fill));

