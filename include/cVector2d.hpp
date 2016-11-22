#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>
#include "cImage.hpp"
#include "utility.hpp"

using namespace std;

namespace MATRIX {
    typedef vector<vector<double>> mat;
    
    mat identityMat(int size);
    mat inverse(const mat& m);
    mat transpose(const mat& m);
    double det(const mat& m);
    
    //Arithmentic operations
    mat operator+(const mat&, double);
    mat operator-(const mat&, double);
    mat operator*(const mat&, double);
    mat operator/(const mat&, double);
    
    //Matrix operations
    mat operator+(const mat&, const mat&);
    mat operator-(const mat&, const mat&);
    mat operator*(const mat&, const mat&);
}


namespace VECTOR    {
    typedef pair<double, double> point2D;
    
    class vec2D   {
        double x1,x0,y1,y0;
    public:
        vec2D(double i, double j) : x1(i), y1(j), x0(0), y0(0) {};
        vec2D(double angle) : x1(cos(angle)), y1(sin(angle)), x0(0), y0(0) {};
        vec2D(point2D p) : x1(get<0>(p)), y1(get<1>(p)), x0(0), y0(0) {};
        vec2D(point2D src, point2D dest) : x1(get<0>(dest)), y1(get<1>(dest)), x0(get<1>(src)), y0(get<1>(src)) {};
        
        //Getters
        double getX();
        double getY();
        
        //Setters
        void setX(double);
        void setY(double);
        
        double magnitude();
        double direction();
        vec2D normalized();
        MATRIX::mat toMatrix();
        
        double dot(const vec2D&);
        vec2D cross(const vec2D&);
        
        friend vec2D operator+(const vec2D&, const vec2D&);
        friend vec2D operator+(const vec2D&, double val);
        friend vec2D operator-(const vec2D&, const vec2D&);
        friend vec2D operator-(const vec2D&, double val);
        friend vec2D operator*(const vec2D&, double val);
        friend vec2D operator/(const vec2D&, double val);
        
    };
}

#endif
