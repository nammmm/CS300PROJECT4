//
//  FractalTerrain.h
//  CS300PROJECT4
//
//  Created by Xiangyu on 12/1/15.
//  Copyright © 2015 The College of Wooster. All rights reserved.
//

#ifndef FractalTerrain_h
#define FractalTerrain_h

class FractalTerrain : Terrain{
private:
    double** terrain;
    double roughnesss, min, max;
    int divisions;
    RGB blue = *new RGB (0.0, 0.0, 1.0);
    RGB green = *new RGB (0.0, 1.0, 0.0);
    RGB white = *new RGB (1.0, 1.0, 1.0);
    void diamond(int x, int y, int side, double scale);
    void square(int x, int y, int side, double scale);
    double rnd();
public:
    FractalTerrain(int lod, double roughness);
    
    double getAltitude(double i, double j);
    
    RGB getColor(double i, double j);
};
#endif /* FractalTerrain_h */
