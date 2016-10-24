#include "cVector2d.hpp"

/*cVector2D::cVector2D(double deg)  {
    dX = cos((deg/360)*2*pi);
    dY = sin((deg/360)*2*pi);
}*/

double cVector2D::operator* (const cVector2D& vec)  {
    return dX*vec.dX + dY*vec.dY;
}

cVector2D cVector2D::operator* (double l)  {
    return cVector2D(dX*l, dY*l);
}

cVector2D cVector2D::operator/ (double l)  {
    return cVector2D(dX/l, dY/l);
}

cVector2D cVector2D::operator+ (const cVector2D& vec)  {
    return cVector2D(dX+vec.dX, dY+vec.dY);
}

void cVector2D::operator+= (const cVector2D& vec)   {
    dX += vec.dX;
    dY += vec.dY;
}

cVector2D cVector2D::operator- (const cVector2D& vec)  {
    return cVector2D(dX-vec.dX, dY-vec.dY);
}

void cVector2D::operator-= (const cVector2D& vec)   {
    dX -= vec.dX;
    dY -= vec.dY;
}

cVector2D cVector2D::perpendicular() {
    return cVector2D(-dY, dX);
}
