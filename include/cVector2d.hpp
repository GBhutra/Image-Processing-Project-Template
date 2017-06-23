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
    class vec2D   {
        double x, y;
    public:
        vec2D(double i, double j) : x(i), y(j) {};
        vec2D(double angle) : x(cos(angle)), y(sin(angle)) {};
        
        //Getters
        double getX();
        double getY();
        
        //Setters
        void setX(double);
        void setY(double);
        
        double magnitude();
        double direction();
        vec2D normalized();
        
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
