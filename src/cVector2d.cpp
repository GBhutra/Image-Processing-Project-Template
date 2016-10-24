//
//  cVector2d.cpp
//  Digital Image Processing
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "cVector2d.hpp"

double magnitude(const vector2D& v)   {   return (sqrt(pow(v.first,2)+pow(v.second,2)));  }
vector2D unitVector(const vector2D& v)    {
    double mag = magnitude(v);
    return {v.first/mag,v.second/mag};
}
vector2D createVectorFromDeg(double deg)    {
    return {cos(deg*RAD), sin(deg*RAD)};
}
vector2D operator+(const vector2D& v1, const vector2D& v2)  {   return {v1.first+v2.first,v1.second+v2.second}; }
vector2D operator-(const vector2D& v1, const vector2D& v2)  {   return {v1.first-v2.first,v1.second-v2.second}; }
void operator+=(vector2D& v1, const vector2D& v2) {
    v1.first+=v2.first;
    v1.second+=v2.second;
}
void operator-=(vector2D& v1, const vector2D& v2){
    v1.first-=v2.first;
    v1.second-=v2.second;
}

void operator*(vector2D& v, double val) {
    v.first*=val;
    v.second*=val;
}
void operator/(vector2D& v, double val){
    v.first/=val;
    v.second/=val;
}

double dot(const vector2D& v1, const vector2D& v2)  {
    return (v1.first*v2.first+v1.second*v2.second);
}

vector2D normalVector(const vector2D& v)  {
    double mag = magnitude(v);
    return {-v.first/mag,v.second/mag};
}
