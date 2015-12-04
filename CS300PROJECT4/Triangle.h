//
//  Triangle.h
//  CS300PROJECT4
//
//  Created by Pratistha Bhandari on 12/1/15.
//  Copyright © 2015 The College of Wooster. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

class Triangle{
public:
    Triangle (int i0, int j0, int i1, int j1, int i2, int j2);
    
private:
    int i[3], j[3];
    Triple n;
    RGB rgb[3];
    Color color;
};

#endif /* Triangle_h */
