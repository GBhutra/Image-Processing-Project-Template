#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>
#include "pixel.hpp"
#include "image.hpp"

using namespace std;
const double pi = std::acos(-1);


class cVector2D {
    double m_dX, m_dY;
public:
    cVector2D(double xp, double yp): m_dX(xp), m_dY(yp) {};
    cVector2D(double degrees);
    cVector2D(): m_dX(0), m_dY(0) {};
    
    inline double mod() { return sqrt(pow(m_dX,2.0)+pow(m_dY,2.0));    };
    inline void norm()  {   m_dX=m_dX/this->mod(); m_dY=m_dY/this->mod();   };
    
    double operator*(const cVector2D& vec);
    cVector2D 	operator* 	(double);
    cVector2D 	operator/ 	(double);
    cVector2D 	operator+	(const cVector2D&);
    void 		operator+= 	(const cVector2D&);
    cVector2D 	operator- 	(const cVector2D&);
    void 		operator-= 	(const cVector2D&);
    cVector2D perpendicular();
    friend void connectVector2DByLine(cVector2D,cVector2D, cImage&, RGB);
};


#endif
