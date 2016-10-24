//
//  2dShapes.hpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef _dShapes_hpp
#define _dShapes_hpp

#include <iostream>
#include <cmath>
#include "cVector2d.hpp"
#include "cImage.hpp"

class cCircle   {
    int x,y;
    float r;
public:
    cCircle(int i, int j, float R) : x(i), y(j), r(R) {};
    cCircle();
    
    bool inCircle(int, int);
};

void line(cVector2D& p1, cVector2D& p2, cImage& img, RGB color);
void drawHist(cHistogram& img);

#endif /* _dShapes_hpp */
