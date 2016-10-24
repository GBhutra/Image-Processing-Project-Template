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
#include <cstdlib>
#include <ctime>
#include "cVector2d.hpp"
#include "cImage.hpp"

struct line2D {
    vector2D n;
    double r;
    line2D() = delete;
    //Line from 2 points
    line2D(const vector2D&, const vector2D&);
    //Line from a point and an angle
    line2D(const vector2D&, const double);
    double isPointIn(const vector2D&);
};

void drawHalfPlane(line2D &l,cImage& img, RGB color, bool antiAlias=false);
void drawLine(line2D &l,cImage& img, RGB color, double lineWidth=0.4);
void drawLineSegment(vector2D& v1, vector2D& v2, cImage& img, RGB color);

//void line(cVector2D& p1, cVector2D& p2, cImage& img, RGB color);
//void drawHist(cHistogram& img);
#endif /* _dShapes_hpp */
