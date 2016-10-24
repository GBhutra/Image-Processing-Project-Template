//
//  2dShapes.cpp
//  Digital Image Processing
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "2dShapes.hpp"

const int numSubPixels = 5;

line2D::line2D(const vector2D& p1, const vector2D& p2) {
    vector2D d = unitVector(p2-p1);
    n = {-d.second,d.first};
    r = dot(p1, n);
};

line2D::line2D(const vector2D& point, const double deg)   {
    n = createVectorFromDeg(deg+90);
    r = dot(point,n);
}

double line2D::isPointIn(const vector2D& point)  {
    double diff = dot(point,n);
    return (diff-r);
}

void drawHalfPlane(line2D &l,cImage& img, RGB color, bool antiAlias)   {
    for (int i=0;i<img.getWidth();i++)  {
        for(int j=0;j<img.getHeight();j++)  {
            if (antiAlias && 0<l.isPointIn({i,j})) {
                int count =0;
                //srand(time(0));
                double randomX,randomY;
                randomX=randomY=(double)1/(numSubPixels*numSubPixels);
                for (int x=0;x<numSubPixels;x++)    {
                    randomY=(double)1/(numSubPixels*numSubPixels);
                    for (int y=0;y<numSubPixels;y++)    {
                        //double randomX = ((double) rand() / (RAND_MAX));
                        //double randomY = ((double) rand() / (RAND_MAX));
                        if (0<l.isPointIn({i+randomX,j+randomY}))   count++;
                        randomY+=randomY;
                    }
                    randomX+=randomX;
                }
                double factor = static_cast<double>(count)/numSubPixels;
                RGB col{static_cast<int>(factor*get<0>(color)),static_cast<int>(factor*get<1>(color)),static_cast<int>(factor*get<2>(color))};
                img.setPixelAtXY(i, j, col);
            }
            else if(!antiAlias && 0<l.isPointIn({i,j}))   {
                img.setPixelAtXY(i, j, color);
            }
        }
    }
}

void drawLine(line2D &l,cImage& img, RGB color, double lineWidth)   {
    for (int i=0;i<img.getWidth();i++)  {
        for(int j=0;j<img.getHeight();j++)  {
            if(0.4>abs(l.isPointIn({i,j})))   {
                img.setPixelAtXY(i, j, color);
            }
        }
    }
}

void drawLineSegment(vector2D& v1, vector2D& v2, cImage& img, RGB color)    {
    vector2D diff = v2-v1;
    int numPoints = static_cast<int>(magnitude(diff));
    vector2D unit = unitVector(diff);
    int w = static_cast<int>(v1.first);
    int h = static_cast<int>(v1.second);
    vector2D curr = v1;
    img.setPixelAtXY(w,h,color);
    for (int i=0;i<=numPoints;i++)  {
        curr +=unit;
        w = static_cast<int>(curr.first);
        h = static_cast<int>(curr.second);
        img.setPixelAtXY(w,h,color);
    }
}
