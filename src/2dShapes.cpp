//
//  2dShapes.cpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "2dShapes.hpp"

cCircle::cCircle () {
    x=0;
    y=0;
    r=1;
}

bool cCircle::inCircle(int i, int j) {
    return (pow(r,2)-(pow((i-x),2)+pow((j-y),2)))>0;
}
