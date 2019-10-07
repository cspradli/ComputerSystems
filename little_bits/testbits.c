#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
    int x = rand();
    int y = rand();
    int z = rand();
    unsigned ux = (unsigned) x;
    unsigned uy = (unsigned) y;
    double dx = (double) x;
    double dy = (double) y;
    double dz = (double) z;

    assert((x<y) == (-x > -y)); //true
    assert(((x+y)<<4) + y-x == 17*y+15*x); //true
    assert((x >= 0) || (x < ux)); //true
    assert(((x >> 1) << 1) <= x); //true
    assert(dx + dy + dz == dz + dy + dx);//true
    assert(dx * dy * dz == dz * dy * dx);
    assert(dx+dy == (double) (y+x)); //false
    assert((double)(float) x == (double) x); //false
    assert(ux-uy == -(x+y)); //false
    assert((~x+~y+1) == ~(x+1)); //false
    return 0;
}
