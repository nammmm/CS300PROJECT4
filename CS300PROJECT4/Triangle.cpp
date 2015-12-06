//
//  Triangle.cpp
//  CS300PROJECT4
//
//  Created by Pratistha Bhandari on 12/1/15.
//  Copyright © 2015 The College of Wooster. All rights reserved.
//
#include "Triangle.h"
Triangle::Triangle (int i0, int j0, int i1, int j1, int i2, int j2) {
    i[0] = i0;
    i[1] = i1;
    i[2] = i2;
    j[0] = j0;
    j[1] = j1;
    j[2] = j2;
    color.resize(3);
}
vector<RGB> Triangle::getColor()
{
    return color;
}

void Triangle::setColor(vector<RGB> c)
{
    color = c;
}

RGB Triangle::getAvgColor()
{
    return avgColor;
}

void Triangle::setAvgColor(RGB c)
{
    avgColor = c;
}

Triple Triangle::getNormal()
{
    return n;
}

void Triangle::setNormal(Triple norm)
{
    n = norm;
}