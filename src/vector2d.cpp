#include "vector2d.hpp"

#define PT_DIST 0.9

cVector2D::cVector2D(double deg)  {
    m_dX = cos((deg/360)*2*pi);
    m_dY = sin((deg/360)*2*pi);
}

double cVector2D::operator* (const cVector2D& vec)  {
    return m_dX*vec.m_dX + m_dY*vec.m_dY;
}

cVector2D cVector2D::operator* (double l)  {
    return cVector2D(m_dX*l, m_dY*l);
}

cVector2D cVector2D::operator/ (double l)  {
    return cVector2D(m_dX/l, m_dY/l);
}

cVector2D cVector2D::operator+ (const cVector2D& vec)  {
    return cVector2D(m_dX+vec.m_dX, m_dY+vec.m_dY);
}

void cVector2D::operator+= (const cVector2D& vec)   {
    m_dX += vec.m_dX;
    m_dY += vec.m_dY;
}

cVector2D cVector2D::operator- (const cVector2D& vec)  {
    return cVector2D(m_dX-vec.m_dX, m_dY-vec.m_dY);
}

void cVector2D::operator-= (const cVector2D& vec)   {
    m_dX -= vec.m_dX;
    m_dY -= vec.m_dY;
}

cVector2D cVector2D::perpendicular() {
    return cVector2D(-m_dY, m_dX);
}

void connectVector2DByLine(cVector2D p1, cVector2D p2,cImage& pixels, RGB color)  {
    int line_pts = ((p2-p1).mod())/PT_DIST;
    cVector2D slope = (p2-p1)*(1.0/line_pts);
    cVector2D curr = p1;
    for(int i=0;i<line_pts;i++){
        pixels.setPixelAtXY((int)(curr.m_dY+0.5),(int)(curr.m_dX+0.5) ,color);
        curr+=slope;
    }
}
