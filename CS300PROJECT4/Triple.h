/********************************************************************
 *  Triple.h
 *
 *  Operations:
 *      -
 *
 ********************************************************************/

#ifndef Triple_h
#define Triple_h

class Triple
{
public:
    Triple(double x, double y, double z);
    Triple();
    Triple add(Triple t);
    Triple subtract(Triple t);
    Triple cross(Triple t);
    double dot(Triple t);
    double length2();
    Triple normalize();
    Triple scale(double scale);
    double getHeight();
    double getX();
    double getZ();
    static double testNorm(Triple vec);
private:
    double x, y, z;
};

#endif /* Triple_h */
