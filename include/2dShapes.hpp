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
#include "cPixel.hpp"
#include "utility.hpp"
#include "cVector2d.hpp"
#include "cImage.hpp"

using namespace VECTOR;
// This data structure defines a line
struct line {
    //normal vector
    vec2D normalUnitVector;
    double distFromOrigin;
    
    line() = delete;
    //Line from 2 points
    line(const vec2D&, const vec2D&);
    
    double isPointIn(const vec2D&);
};


class shape  {
public:
    //virtual double distanceFromPoint(const vec2D&);
    virtual bool isPointIn(const vec2D&) = 0;
};

//This data structure defines a plane
class plane: public shape    {
    line l;
public:
    plane() = delete;
    /*The edges need to be declared anti-clock wise*/
    plane(line& l);
    bool isPointIn(const vec2D&);
};

//This data structure defines a polygon
class convex: public shape    {
protected:
    vector<line> edges;
public:
    convex() = delete;
    /*The edges need to be declared anti-clock wise*/
    convex(vector<vec2D>&);
    bool isPointIn(const vec2D&);
    double numSides;
};

class blob;

//This data structure defines a circle
class circle: public shape    {
    friend blob;
    vec2D center;
    double radius;
public:
    circle() = delete;
    circle(vec2D p, double r) : center(p), radius(r) {};
    bool isPointIn(const vec2D&);
    friend void drawCircularShade(circle& c, cImage& img, RGB color);
    friend void drawCircle(circle& c, cImage& img, RGB color , bool antiAlias);
};

//This data structure defines a star
class star: public convex    {
    bool isPointIn(const vec2D&);
public:
    star(vector<vec2D>& v) : convex(v) {};
};

//This data structure defines a decaying sin function
class func: public shape    {
public:
    func() {};
    bool isPointIn(const vec2D&);
};

class blob : public shape {
    vector<circle> circles;
public:
    blob(vector<circle>& cir) : circles(cir) {};
    bool isPointIn(const vec2D&);
};

void drawLine(line &l,cImage& img, RGB color, bool antiAlias=false);
void drawShape(shape& poly, cImage& img, RGB color, bool antiAlias=false);
void drawCircularShade(circle& c, cImage& img, RGB color);
void drawCircle(circle& c, cImage& img, RGB color , bool antiAlias);
#endif /* _dShapes_hpp */
