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


void cHistogram::genHistogram(cImage& img)    {
    for (int i=0;i<img.getWidth();++i) {
        for (int j=0;j<img.getHeight();++j) {
            cPixel p = img.getPixelAtXY(i,j);
            arrRed[p.getRed()]++;
            arrGreen[p.getGreen()]++;
            arrBlue[p.getBlue()]++;
        }
    }
    int maxr,maxg,maxb;
    maxr=maxb=maxg;
    for (int i=0;i<256;i++)    {
        maxr=maxr<arrRed[i] ? arrRed[i] : maxr;
        maxg=maxg<arrGreen[i] ? arrGreen[i] : maxb;
        maxb=maxb<arrBlue[i] ? arrBlue[i] : maxg;
    }
    RGB red{255,0,0};
    RGB green{0,255,0};
    RGB blue{0,0,255};
    double tempY=0.9*iHeight;
    double tempX=iWidth/256;
    vector2D currR={1,(arrRed[1]/(double)maxr)*tempY},nextR;
    for (int i=2;i<arrRed.size()-1;i++)    {
        nextR = {((i+1)*tempX),(arrRed[i]/(double)maxr)*tempY};
        drawLineSegment(currR, nextR, *this, red);
        currR = nextR;
    }
    vector2D currG={1,(arrGreen[1]/(double)maxg)*tempY},nextG;
    for (int i=2;i<arrGreen.size()-1;i++)    {
        nextG = {((i+1)*tempX),(arrGreen[i+1]/(double)maxg)*tempY};
        drawLineSegment(currG, nextG, *this, green);
        currG = nextG;
    }
    vector2D currB={1,(arrBlue[1]/(double)maxb)*tempY},nextB;
    for (int i=2;i<arrBlue.size()-1;i++)    {
        nextB = {((i+1)*tempX),(arrBlue[i+1]/(double)maxb)*tempY};
        drawLineSegment(currB, nextB, *this, blue);
        currB = nextB;
    }
}
