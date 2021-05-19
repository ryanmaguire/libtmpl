import settings;
import palette;
import three;
import tube;
import graph3;

if (settings.render < 0)
    settings.render = 8;

settings.outformat = "pdf";
size(1024, 1024);

int max = 1000;
int n;
triple A = (0.0, 0.0, 0.0);
triple B = (0.0, 0.0, 0.0);
pen[] mypen = Rainbow(max);

triple Rtrip()
{
    int n = (int)floor(6.0 * (rand() / randMax));
    if (n == 0)
        return (1.0, 0.0, 0.0);
    else if (n == 1)
        return (-1.0, 0.0, 0.0);
    else if (n == 2)
        return (0.0, 1.0, 0.0);
    else if (n == 3)
        return (0.0, -1.0, 0.0);
    else if (n == 4)
        return (0.0, 0.0, 1.0);
    else
        return (0.0, 0.0, -1.0);
}

for (n=0; n<max; ++n)
{
    B = A + Rtrip();
    draw(A--B, mypen[n]);
    A = B;
}

xaxis3(XZ()*"$x$", Bounds, red, InTicks(Label,2,2));
yaxis3(YZ()*"$y$", Bounds, red, InTicks(beginlabel=false,Label,2,2));
zaxis3(XZ()*"$z$", Bounds, red, InTicks);

