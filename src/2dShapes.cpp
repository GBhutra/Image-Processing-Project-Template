//
//  2dShapes.cpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "2dShapes.hpp"
#define PT_DIST 0.9

cCircle::cCircle () {
    x=0;
    y=0;
    r=1;
}

bool cCircle::inCircle(int i, int j) {
    return (pow(r,2)-(pow((i-x),2)+pow((j-y),2)))>0;
}

void line(cVector2D& p1, cVector2D& p2, cImage& img, RGB color) {
    int line_pts = ((p2-p1).mod())/PT_DIST;
    cVector2D slope = (p2-p1)*(1.0/line_pts);
    for(int i=0;i<line_pts;i++){
        img.setPixelAtXY((int)(p1.getY()+0.5),(int)(p1.getX()+0.5) ,color);
        p1+=slope;
    }
}

