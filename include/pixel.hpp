#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include <tuple>

using namespace std;

#define maximum(x, y, z) ((x) > (y)? ((x) > (z)? (x) : (z)) : ((y) > (z)? (y) : (z)))
#define minimum(x, y, z) ((x) < (y)? ((x) < (z)? (x) : (z)) : ((y) < (z)? (y) : (z)))

typedef tuple<int,int,int>RGB;
typedef tuple<double, double, double>HSV;


class cPixel	{
    int m_iR, m_iG, m_iB;
public:
    // constructors
    cPixel() : m_iR(0),m_iG(0),m_iB(0) {};
    cPixel(unsigned int x, unsigned int y, unsigned int z) : m_iR(x),m_iG(y),m_iB(z) {};
    
    //assignment operator overload
    void operator=(const cPixel& rhs);
    
    //getters and setters
    inline int getRed()	{	return m_iR;	};
    inline int getGreen()	{	return m_iG;	};
    inline int getBlue()	{	return m_iB;	};
    inline void setRed(int r) {	m_iR = r;	};
    inline void setGreen(int g) {	m_iG = g;	};
    inline void setBlue(int b) {	m_iB = b;	};
    
    //function that returns the HSV value of the pixel
    HSV toHSV();
    
    //arithmetic operator overload
    friend cPixel operator+(const cPixel& lhs, const cPixel& rhs);
    friend cPixel operator-(const cPixel& lhs, const cPixel& rhs);
};

RGB HSVtoRGB(HSV pixel);

#endif
