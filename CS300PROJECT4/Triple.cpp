/********************************************************************
 * Triple.cpp
 *
 *  Data representation of a point or vector in space. Functions of
 *  various mathematical operations are provided.
 *
 ********************************************************************/

#include "Triple.h"
#include <cmath>

Triple::Triple(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Triple::Triple(){};

Triple Triple::add(Triple t)
{
    return Triple(x + t.x, y + t.y, z + t.z);
}

Triple Triple::subtract(Triple t)
{
    return Triple(x - t.x, y - t.y, z - t.z);
}

Triple Triple::cross(Triple t)
{
    return Triple(y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x);
}

double Triple::dot(Triple t)
{
    return x * t.x + y * t.y + z * t.z;
}

double Triple::length2()
{
    return dot(*this);
}

Triple Triple::normalize()
{
    return scale(1.0 / sqrt(length2()));
}

Triple Triple::scale(double scale)
{
    return Triple(x * scale, y * scale, z * scale);
}

double Triple::getHeight()
{
    return y;
}

double Triple::getX()
{
    return x;
}

double Triple::getZ()
{
    return z;
}

ostream& operator<<(ostream& os, const Triple& vec)
{
    os << "x: " << vec.x << "  y: " << vec.y << "  z: " << vec.z;
    return os;
}

double Triple::testNorm(Triple vec)
{
    double length = pow(vec.normalize().getX(), 2) + pow(vec.normalize().getHeight(), 2) + pow(vec.normalize().getZ(), 2);
    return (length == 1) ? length : 0;
}