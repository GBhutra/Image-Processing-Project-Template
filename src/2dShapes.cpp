//
//  2dShapes.cpp
//  Digital Image Processing
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "2dShapes.hpp"

const double numSubPixels = 3;

line::line(const vector2D& p1, const vector2D& p2) {
    normalUnitVector = normalVector(p2-p1);
    distFromOrigin = dot(normalUnitVector,p1);
};

//returns +ve dist for the point on the right and negative dist for point on the left of the line
double line::isPointIn(const vector2D& p)  {
    double norm = dot(normalUnitVector,p);
    return (norm-distFromOrigin);;
}

void drawLine(line &l,cImage& img, RGB color)   {
    for (int i=0;i<img.getWidth();i++)  {
        double y = (l.distFromOrigin/l.normalUnitVector.second)-((l.normalUnitVector.first/l.normalUnitVector.second)*i);
        int j = static_cast<int>(y);
        if(0<=y && y<img.getHeight())
            img.setPixelAtXY(i, j, color);
    }
}

convex::convex(vector<vector2D>& vertices) {
    for (int i=0;i<vertices.size()-1;i++) {
        line l(vertices[i],vertices[i+1]);
        edges.push_back(l);
    }
    line l(vertices[vertices.size()-1],vertices[0]);
    edges.push_back(l);
}

double circle::isPointIn(const vector2D& p)   {
    return (radius-magnitude(center-p));
}

double convex::isPointIn(const vector2D& p)  {
    int count=0;
    for (auto edge : edges) {
        if (0<edge.isPointIn(p))
            count++;
    }
    if (0==count)
        return 5;
    else
        return -5;
}

double star::isPointIn(const vector2D& p)  {
    int count=0;
    for (auto edge : edges) {
        if (0<edge.isPointIn(p))
            count++;
    }
    if (1<count)
        return -5;
    else
        return 0;
}

double func::isPointIn(const vector2D& p)    {
   // y=50e^(-(x-250)/100)sin((x-250)/10)+250
    if (5>(p.second-(60*exp((250-p.first)/200)*sin((p.first-250)/10))-250))
        return 5;
    else
        return -5;
}

void drawPolygon(polygon& poly, cImage& img, RGB color, bool antiAlias)   {
    double in=0,r,g,b;
    RGB col;
    for (int i=0;i<img.getWidth();i++)  {
        for(int j=0;j<img.getHeight();j++)  {
            if (-2>poly.isPointIn({i,j}) && 0>=poly.isPointIn({i,j}))    {
                if (antiAlias)  {
                    in = 0;
                    for(double X=0;X<1;X+=(1/numSubPixels)) {
                        for(double Y=0;Y<1;Y+=(1/numSubPixels)) {
                            if (0<=poly.isPointIn({X+i,Y+j}))    {
                                in+=(1/(numSubPixels*numSubPixels));
                            }
                        }
                    }
                    if (0<in)   {
                        auto p = img.getPixelAtXY(i, j);
                        r = double(get<0>(color))*(1-in)+(p.getRed()*in);
                        g = double(get<1>(color))*(1-in)+(p.getGreen()*in);
                        b = double(get<2>(color))*(1-in)+(p.getBlue()*in);
                        col=make_tuple(static_cast<int>(r),static_cast<int>(g),static_cast<int>(b));
                        img.setPixelAtXY(i, j, col);
                    }
                }
            }
            else if (0<=poly.isPointIn({i,j}))
               img.setPixelAtXY(i, j, color);
        }
    }
}



/*
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
        Shape2D::drawLineSegment(currR, nextR, *this, red);
        currR = nextR;
    }
    vector2D currG={1,(arrGreen[1]/(double)maxg)*tempY},nextG;
    for (int i=2;i<arrGreen.size()-1;i++)    {
        nextG = {((i+1)*tempX),(arrGreen[i+1]/(double)maxg)*tempY};
        Shape2D::drawLineSegment(currG, nextG, *this, green);
        currG = nextG;
    }
    vector2D currB={1,(arrBlue[1]/(double)maxb)*tempY},nextB;
    for (int i=2;i<arrBlue.size()-1;i++)    {
        nextB = {((i+1)*tempX),(arrBlue[i+1]/(double)maxb)*tempY};
        Shape2D::drawLineSegment(currB, nextB, *this, blue);
        currB = nextB;
    }
}*/
