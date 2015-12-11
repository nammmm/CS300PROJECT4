//
//  RGB.h
//

#ifndef RGB_h
#define RGB_h

class RGB{
public:
    RGB (double r, double g, double b);
    RGB();
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