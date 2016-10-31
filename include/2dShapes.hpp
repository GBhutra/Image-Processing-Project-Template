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
#include <cstdarg>
#include "cVector2d.hpp"
#include "cImage.hpp"

// This data structure defines a line
struct line {
    //normal vector
    vector2D normalUnitVector;
    double distFromOrigin;
    
    line() = delete;
    //Line from 2 points
    line(const vector2D&, const vector2D&);
    
    double isPointIn(const vector2D&);
};


class polygon  {
public:
    virtual double isPointIn(const vector2D&) = 0;
};

//This data structure defines a plane
class plane: public polygon    {
    line l;
public:
    plane() = delete;
    /*The edges need to be declared anti-clock wise*/
    plane(line& l);
    double isPointIn(const vector2D&);
};

//This data structure defines a polygon
class convex: public polygon    {
protected:
    vector<line> edges;
public:
    convex() = delete;
    /*The edges need to be declared anti-clock wise*/
    convex(vector<vector2D>&);
    double isPointIn(const vector2D&);
    double numSides;
};

//This data structure defines a circle
class circle: public polygon    {
    vector2D center;
    double radius;
public:
    circle() = delete;
    circle(vector2D p, double r) : center(p), radius(r) {};
    double isPointIn(const vector2D&);
};

//This data structure defines a star
class star: public convex    {
    double isPointIn(const vector2D&);
public:
    star(vector<vector2D>& v) : convex(v) {};
};

//This data structure defines a decaying sin function
class func: public polygon    {
public:
    func() {};
    double isPointIn(const vector2D&);
};

void drawLine(line &l,cImage& img, RGB color);
void drawPolygon(polygon& poly, cImage& img, RGB color, bool antiAlias=false);

#endif /* _dShapes_hpp */
