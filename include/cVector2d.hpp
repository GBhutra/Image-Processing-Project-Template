#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>
#include "cPixel.hpp"
#include "cImage.hpp"
#include "utility.hpp"

using namespace std;

typedef pair<double,double> vector2D;

double magnitude(const vector2D&);
vector2D unitVector(const vector2D&);
vector2D normalVector(const vector2D&);
vector2D createVectorFromDeg(double deg);

vector2D operator+(const vector2D&, const vector2D&);
vector2D operator-(const vector2D&, const vector2D&);
void operator+=(vector2D&, const vector2D&);
void operator-=(vector2D&, const vector2D&);
void operator*(vector2D&, double);
void operator/(vector2D&, double);

double dot(const vector2D&, const vector2D&);

#endif
