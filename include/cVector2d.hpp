#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>
#include "cImage.hpp"
#include "utility.hpp"

using namespace std;

typedef pair<double,double> vector2D;
typedef vector<vector<double>> mat;

//Vector Operations
double magnitude(const vector2D&);
double direction(const vector2D&);
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


//Matrix peartions
mat identityMat(int size);
mat inverse(const mat& m);
mat transpose(const mat& m);

mat operator*(const mat&, const mat&);
template<typename T>
mat operator*(const mat&, T);
mat operator+(const mat&, const mat&);
template<typename T>
mat operator+(const mat&, T);
mat operator-(const mat&, const mat&);
template<typename T>
mat operator-(const mat&, T);
void showMatrix(mat& m);

// Matrix and vector2d operations
mat makeMatrix(const vector2D& v);

#endif
