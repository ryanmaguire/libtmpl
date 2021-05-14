import settings;
import palette;

if (settings.render < 0)
    settings.render = 8;

settings.outformat   = "pdf";

int max = 32765;

size(max + 100, max + 100);

int n;
pair A = (0.0, 0.0);
pair B = (0.0, 0.0);
pen[] mypen = Rainbow(max);

pair Rpair()
{
    real x = (real)(rand()/randMax);
    return (cos(x*2.0*pi), sin(x*2.0*pi));
}

for (n=0; n<max; ++n)
{
    B = A + Rpair();
    draw(A--B, mypen[n]);
    A = B;
}

shipout(bbox(currentpicture, Black, Fill));

