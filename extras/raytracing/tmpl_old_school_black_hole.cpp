#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct vector {
    float x, y, z;
    vector operator + (vector r)
    {
        return vector(x+r.x, y+r.y, z+r.z);
    }

    vector operator * (float r)
    {
        return vector(x*r,y*r,z*r);
    }

    float operator % (vector r)
    {
        return x*r.x+y*r.y+z*r.z;
    }

    vector(){}vector

    operator ^ (vector r)
    {
        return vector(y*r.z - z*r.y, z*r.x - x*r.z, x*r.y - y*r.x);
    }

    vector(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }

    vector operator ! (void)
    {
        return *this*(1/sqrt(*this%*this));
    }

    float norm(void)
    {
        return sqrt(*this%*this);
    }


    float normsq(void)
    {
        return *this%*this;
    }
};

vector acc(vector p)
{
    float factor = 1.0 / (p.normsq() * p.norm());
    return vector(-p.x*factor, -p.y*factor, -p.z*factor);
}

vector Path(vector p, vector v, float dt)
{
    while ((p.z > -10.0))
    {
        if (p.norm() <= 1.0)
            return vector(0, 0, 0);

        v = v + acc(p) * dt;
        p = p + v * dt;
    }
    return p;
}

void color_red(FILE *fp)
{
    fputc(255, fp);
    fputc(0, fp);
    fputc(0, fp);
}

void color_black(FILE *fp)
{
    fputc(0, fp);
    fputc(0, fp);
    fputc(0, fp);
}

void color_white(FILE *fp)
{
    fputc(255, fp);
    fputc(255, fp);
    fputc(255, fp);
}

void color_gray(FILE *fp)
{
    fputc(128, fp);
    fputc(128, fp);
    fputc(128, fp);
}

int main(void)
{
    vector v = vector(0.0, 0.0, -1.0);
    vector p;
    unsigned int x, y, size;
    float factor, start, end;
    start = -10.0;
    end = 10.0;
    size = 2048;
    factor = (end - start) / (float)size;
    FILE *fp = fopen("black.ppm", "w");

    fprintf(fp, "P6 %u %u 255\n", size, size);

    for (y=0; y<size; ++y)
    {
        for (x=0; x<size; ++x)
        {
            p = vector(start + factor*x, start + factor*y, 10);

            p = Path(p, v, 0.01);

            if (p.norm() < 2.0)
                color_black(fp);

            else if ((int)(ceil(p.x) + ceil(p.y)) & 1)
                color_white(fp);

            else
                color_red(fp);
        }
    }

    fclose(fp);
    return 0;
}

