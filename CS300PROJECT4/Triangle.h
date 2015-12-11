//
//  Triangle.h
//

#ifndef Triangle_h
#define Triangle_h
#include "Triple.h"
#include "RGB.h"
#include <vector>

using namespace std;
class Triangle{
private:
    int i[3], j[3];
    Triple n = Triple(0, 0, 0);
    vector<RGB> color;
    RGB avgColor = RGB(0, 0, 0);
    
public:
    Triangle (int i0, int j0, int i1, int j1, int i2, int j2);
    Triangle ();
    vector<RGB> getColor();
    
    void setColor(vector<RGB> c);
    
    RGB getAvgColor();
    void setAvgColor(RGB c);
    
    Triple getNormal();
    
    void setNormal(Triple norm);
    
    vector<double> getVertex(int num);
};

#endif /* Triangle_h */