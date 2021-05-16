import settings;

if (settings.render < 0)
    settings.render = 8;

settings.outformat   = "pdf";

size(512, 512);

int n;
pair A, B;

for (n=0; n<10; ++n)
{
    if ((n % 2) == 0)
    	A = expi(2*pi*n / 5.0);
    else
    	A = expi(2*pi*(n+1) / 5.0);

    B = 0.5*expi((2*n+1)*pi / 5.0);
    draw(A--B);
}

