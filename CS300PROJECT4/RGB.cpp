//
//  RGB.cpp
//  CS300PROJECT4
//
//  Created by Pratistha Bhandari on 12/1/15.
//  Copyright © 2015 The College of Wooster. All rights reserved.
//

#include <stdio.h>
#include "RGB.h"
#include <cmath>

RGB::RGB (double r, double g, double b){
        this->r = r;
        this->g = g;
        this->b = b;
}

RGB::RGB(){};
RGB RGB::add(RGB rgb){
        return RGB (r + rgb.r, g + rgb.g, b + rgb.b);
}
    
RGB RGB::subtract (RGB rgb){
        return RGB (r - rgb.r, g - rgb.g, b - rgb.b);
}
    
RGB RGB::scale (double scale){
        return RGB (r * scale, g * scale, b * scale);
}

int RGB::toInt (double value){
    return (value < 0.0) ? 0 : (value > 1.0) ? 255 : (int) (value * 255.0);
}

int RGB::toRGB (){
        return (0xff << 24) | (toInt (r) << 16) | (toInt (g) << 8) | toInt (b);
}


double RGB::getRed()
{
    return r;
}
double RGB::getGreen()
{
    return g;
}
double RGB::getBlue()
{
    return b;
}

