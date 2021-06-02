import math, cmath;

width = 1200;
height = 960;
imax = 100;
zmax = 150;
x_min = -6.6;
x_max = -0.4;
y_min = -3.095;
y_max = 3.105;
x_factor = (x_max - x_min)/(width - 1.0);
y_factor = (y_max - y_min)/(height - 1.0);

fp = open("swipecat_fractal.ppm", "w");
fp.write("P3\n%d %d\n255\n" % (width, height));

for y in range(height):
    z_y = y_max - y_factor*y;
    for x in range(width):
        z_x = x_min + x_factor*x;
        c = complex(z_x, z_y);
        z = 0.0;
        backgnd = 0.0;
        for its in range(imax):
            z = 0.5*math.pi * (cmath.exp(z) - z) + c;
            if abs(z.real) >= zmax:
                backgnd = math.log(math.log(abs(z.real) + 1.0) * 0.33333333333);
                backgnd = math.log(abs(its - backgnd)) * 0.3076923076923077;
                break;

        val = max(0.0, 1.0 - abs(1.0 - backgnd));
        if (backgnd <= 1.0):
            r = int(255.0 * val**4);
            g = int(255.0 * val**2.5);
            b = int(255.0 * val);
        else:
            r = int(255.0 * val);
            g = int(255.0 * val**1.5);
            b = int(255.0 * val**3);

        fp.write("%u %u %u\n" % (r, g, b));
fp.close();
                 
