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
    deg = DEGToRAD(deg);
    return {cos(deg), sin(deg)};
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
    vector2D unit = unitVector(v);
    return {unit.second,-unit.first};
}

//Matrix definitions
mat transpose(const mat& m) {
    mat op(m[0].size(),vector<double>(m.size(),0));
    for (int i=0;i<m.size();i++)    {
        for (int j=0;j<m[0].size();j++)
            op[j][i] = m[i][j];
    }
    return op;
}

mat inverse(const mat& m)    {
    mat mT = transpose(m);
    double det = mT[0][0]*(mT[1][1]*mT[2][2]-mT[2][1]*mT[1][2]) -
    mT[0][1]*(mT[1][0]*mT[2][2]-mT[2][0]*mT[1][2]) +
    mT[0][2]*(mT[1][0]*mT[2][1]-mT[2][0]*mT[1][1]);
    mat op(m);
    op[0][0] = (mT[1][1]*mT[2][2]-mT[2][1]*mT[1][2])/det;
    op[0][1] = -(mT[1][0]*mT[2][2]-mT[2][0]*mT[1][2])/det;
    op[0][2] = (mT[1][0]*mT[2][1]-mT[2][0]*mT[1][1])/det;
    op[1][0] = -(mT[0][1]*mT[2][2]-mT[2][1]*mT[0][2])/det;
    op[1][1] = (mT[0][0]*mT[2][2]-mT[2][0]*mT[0][2])/det;
    op[1][2] = -(mT[0][0]*mT[2][1]-mT[2][0]*mT[0][1])/det;
    op[2][0] = (mT[0][1]*mT[1][2]-mT[1][1]*mT[0][2])/det;
    op[2][1] = -(mT[0][0]*mT[1][2]-mT[1][0]*mT[0][2])/det;
    op[2][2] = (mT[0][0]*mT[1][1]-mT[1][0]*mT[0][1])/det;
    
    return op;
}

mat identityMat(int size){
    mat m(size,vector<double>(size,0));
    for (int i=0;i<size;i++)
        m[i][i] = 1;
    return m;
}

mat rotation(double ang);
mat scaling(double x, double y);
mat shear(double x, double y);
mat translation(double x, double y);
mat perspective(double x, double y);


mat operator*(const mat& lhs, const mat& rhs)   {
    if (lhs[0].size()!=rhs.size())
        return identityMat(0);
    mat op(lhs.size(),vector<double>(rhs[0].size(),0));
    for (int i=0;i<lhs.size();i++) {
        for (int j=0;j<rhs[0].size();j++)   {
            for (int k=0;k<lhs[0].size();k++)
                op[i][j] += lhs[i][k] * rhs[k][j];
        }
    }
    return op;
}

template<typename T>
mat operator*(const mat& m, T val)    {
    mat op(m);
    for (auto& row : op)    {
        for (auto& col : row)
            col = col*val;
    }
    return op;
}

mat operator+(const mat& lhs, const mat& rhs)   {
    if (lhs.size()!=rhs.size() && lhs[0].size()!=rhs[0].size())
        return identityMat(0);
    mat op(lhs);
    for (int i=0;i<lhs.size();i++)    {
        for (int j=0;j<lhs[0].size();j++)
            op[i][j] +=rhs[i][j];
    }
    return op;
}

template<typename T>
mat operator+(const mat& m, T val)    {
    mat op(m);
    for (auto& row : op)    {
        for (auto& col : row)
            col = col+val;
    }
    return op;
}
mat operator-(const mat& lhs, const mat& rhs)   {
    if (lhs.size()!=rhs.size() && lhs[0].size()!=rhs[0].size())
        return identityMat(0);
    mat op(lhs);
    for (int i=0;i<lhs.size();i++)    {
        for (int j=0;j<lhs[0].size();j++)
            op[i][j] -=rhs[i][j];
    }
    return op;
}
template<typename T>
mat operator-(const mat& m, T val)    {
    mat op(m);
    for (auto& row : op)    {
        for (auto& col : row)
            col = col+val;
    }
    return op;
}

void showMatrix(mat& m) {
    for (auto row : m)  {
        cout<<endl;
        for(auto col:row)
            cout<<col<<" ";
    }
}

// Matrix and vector2d operations
mat makeMatrix(const vector2D& v) { return {{v.first},{v.second},{1}};   }


