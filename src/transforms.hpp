//
//  transforms.hpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/31/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef transforms_hpp
#define transforms_hpp

#include <iostream>
#include "cVector2d.hpp"
#include "cImage.hpp"
#include "utility.hpp"

mat rotationMat(double ang);
mat scalingMat(double x, double y);
mat shearMat(double x, double y);
mat translationMat(double x, double y);
mat perspectiveMat(double x, double y);

cImage transform(cImage&, mat& m);


#endif /* transforms_hpp */
