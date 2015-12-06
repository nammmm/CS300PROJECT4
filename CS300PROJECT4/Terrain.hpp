//
//  Terrain.hpp
//  CS300PROJECT4
//
//  Created by Xiangyu on 12/1/15.
//  Copyright © 2015 The College of Wooster. All rights reserved.
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
