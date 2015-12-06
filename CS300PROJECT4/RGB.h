//
//  RGB.h
//  CS300PROJECT4
//
//  Created by Pratistha Bhandari on 12/1/15.
//  Copyright © 2015 The College of Wooster. All rights reserved.
//

#ifndef RGB_h
#define RGB_h

class RGB{
public:
    RGB (double r, double g, double b);
    double getRed();
    double getGreen();
    double getBlue();
    RGB add (RGB rgb);
    RGB subtract (RGB rgb);
    RGB scale (double scale);
    int toRGB ();
    
private:
    double r, g, b;
    int toInt (double value);
};

#endif /* RGB_h */