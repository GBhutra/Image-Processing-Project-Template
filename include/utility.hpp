//
//  utility.hpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/23/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef utility_h
#define utility_h
#include <cmath>
#include <tuple>

typedef std::tuple<short,short,short>        RGB;
typedef std::tuple<short, double, double>    HSV;
typedef short GS;

//constants
const double PI = acos(-1);
const double numSubPixels = 3;


//Macro functions
#define MOD(x) ((x)<0?(-(x)):(x))
#define POS(x) ((x)<0?(0):(x))
#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))
#define DEGToRAD(x) (x*PI/180)
#define RADToDEG(x) (x*180/PI)

#define maximum(x, y, z) ((x) > (y)? ((x) > (z)? (x) : (z)) : ((y) > (z)? (y) : (z)))
#define minimum(x, y, z) ((x) < (y)? ((x) < (z)? (x) : (z)) : ((y) < (z)? (y) : (z)))

#endif /* utility_h */
