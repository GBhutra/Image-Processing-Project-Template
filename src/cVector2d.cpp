//
//  cVector2d.cpp
//  Digital Image Processing
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "cVector2d.hpp"

namespace VECTOR    {
    double vec2D::getX()   {   return x;   }
    double vec2D::getY()   {   return y;   }
    
    void vec2D::setX(double val)   {   x=val;   }
    void vec2D::setY(double val)   {   y=val;   }
    
    double vec2D::magnitude()   {
        return (sqrt(pow((x),2)+pow((y),2)));
    }
    
    double vec2D::direction()   {
        return acos((x)/this->magnitude());
    }
    
    vec2D vec2D::normalized()   {
        return vec2D((x)/this->magnitude(), (y)/this->magnitude());
    }
    
    double vec2D::dot(const vec2D& v2)    {
        double temp1 = (x)*(v2.x);
        double temp2 = (y)*(v2.y);
        return (temp1+temp2);
    }
    
    vec2D vec2D::cross(const vec2D& v2) {
        return vec2D(((x)*(v2.y)), ((y)*(v2.x)));
    }
    
    vec2D operator+(const vec2D& v1, const vec2D& v2) {
        return vec2D(((v1.x)+(v2.x)), ((v1.y)+(v2.y)));
    }
    
    vec2D operator-(const vec2D& v1, const vec2D& v2) {
        return vec2D(((v1.x)-(v2.x)), ((v1.y)-(v2.y)));
    }
    
    vec2D operator*(const vec2D& v, double val)   {
        return vec2D(v.x*val, v.y*val);
    }
    
    vec2D operator/(const vec2D& v, double val){
        return vec2D(v.x/val, v.y/val);
    }
}

namespace MATRIX {
    //returns an identity matrix
    mat identityMat(int size)   {
        mat m(size,vector<double>(size,0));
        for (int i=0;i<size;i++)
            m[i][i] = 1;
        return m;
    }
    
    //returns transpose of a matrix
    mat transpose(const mat& m) {
        mat res(m[0].size(),vector<double>(m.size(),0));
        for (int i=0;i<m.size();i++)    {
            for (int j=0;j<m[0].size();j++) {
                res[i][j] = m[j][i];
            }
        }
        return res;
    }
    
    //inverse of a matrix :: only 3x3 supported
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
    
    double det(const mat& m)    {
        if (2==m.size())
            return ((m[1][1]*m[0][0]) - (m[1][0]*m[0][1]));
        double res=0;
        for (int i=0;i<m.size();i++)    {
            mat subM(m.size()-1,(vector<double>(m[0].size()-1,0)));
            double val = (i%2 == 0) ? 1 : -1;
            for (int u=0;u<subM.size();u++) {
                for (int v=0;v<subM[0].size();v++)  {
                    subM[u][v] = m[u+1][i+v+1];
                }
            }
            val*=m[0][i]*det(subM);
            res+=val;
        }
        return res;
    }
    
    //Arithmentic operations
    mat operator+(const mat&, double);
    mat operator-(const mat&, double);
    mat operator*(const mat& m, double val)   {
        mat op(m);
        for (auto& row : op)    {
            for (auto& col : row)
                col = col*val;
        }
        return op;
    }
    
    //matrix division
    mat operator/(const mat& m, double val)   {
        mat out=m;
        for (auto& row:out)  {
            for (auto& col : row)    {
                col = col/val;
            }
        }
        return out;
    }
    
    //Matrix operations
    
    //Addition
    mat operator+(const mat& lhs, const mat& rhs)   {
        if (lhs.size()!=rhs.size() && lhs[0].size()!=rhs[0].size())
            return identityMat(0);
        mat out = lhs;
        for (int i=0;i<lhs.size();i++) {
            for (int j=0;j<lhs[0].size();j++)   {
                out[i][j]+=rhs[i][j];
            }
        }
        return out;
    }
    //Subtraction
    mat operator-(const mat& lhs, const mat& rhs)   {
        if (lhs.size()!=rhs.size() && lhs[0].size()!=rhs[0].size())
            return identityMat(0);
        mat out = lhs;
        for (int i=0;i<lhs.size();i++) {
            for (int j=0;j<lhs[0].size();j++)   {
                out[i][j]-=rhs[i][j];
            }
        }
        return out;
    }
    //Matrix multiplication
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
    
    //print the matrix
    void showMatrix(mat& m) {
        for (auto row : m)  {
            cout<<endl;
            for(auto col:row)
                cout<<col<<" ";
        }
    }
}


/*


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
mat makeMatrix(const vector2D& v) { return {{v.first},{v.second},{1}};   }*/


