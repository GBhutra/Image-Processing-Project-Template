#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>
#include "cPixel.hpp"
#include "cImage.hpp"

using namespace std;
const double pi = std::acos(-1);


class cVector2D {
    double dX, dY;
public:
    cVector2D(): dX(0), dY(0) {};
    cVector2D(double xp, double yp): dX(xp), dY(yp) {
        dX = xp;
        dY=yp;
    };
    
    inline double mod() { return sqrt(pow(dX,2.0)+pow(dY,2.0));    };
    inline void norm()  {   dX=dX/this->mod(); dY=dY/this->mod();   };
    
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
