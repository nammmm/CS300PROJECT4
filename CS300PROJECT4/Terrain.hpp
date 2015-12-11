//
//  Terrain.hpp
//

#ifndef Terrain_hpp
#define Terrain_hpp
#include <stdio.h>
#include "RGB.h"
class Terrain{
    double getAltitude(double i, double j);
    RGB getColor(double i, double j);
};
#endif /* Terrain_hpp */
