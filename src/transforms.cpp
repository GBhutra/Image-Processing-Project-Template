//
//  transforms.cpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/31/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "transforms.hpp"

mat rotationMat(double ang) {
    mat op(3,vector<double>(3,0));
    op[0][0] = cos(ang);
    op[0][1] = sin(ang);
    op[1][0] = -sin(ang);
    op[1][1] = cos(ang);
    op[2][2] = 1;
    return op;
}
mat scalingMat(double x, double y);
mat shearMat(double x, double y);
mat translationMat(double x, double y);
mat perspectiveMat(double x, double y);

/*
cImage transform(cImage& inputImg, mat& m) {
    //corners used for bilinear
    vector2D cr0, cr1, cr2, cr3;
    double a0, a1, a2, a3, b0, b1, b2, b3;
    
    vector2D ic1{0, 0};
    vector2D ic2{inputImg.getWidth(),0};
    vector2D ic3{inputImg.getWidth(), inputImg.getHeight()};
    vector2D ic4{0, inputImg.getHeight()};
    
    mat oc1 = m*makeMatrix(ic1);
    mat oc2 = m*makeMatrix(ic2);
    mat oc3 = m*makeMatrix(ic3);
    mat oc4 = m*makeMatrix(ic4);
    
    double min_w MIN(MIN(MIN(4,oc1[0][0]), MIN(oc2[0][0], oc3[0][0])), oc4[0][0]);
    double min_h MIN(MIN(MIN(4,oc1[0][1]), MIN(oc2[0][1], oc3[0][1])), oc4[0][1]);
    double max_w MAX(MAX(MAX(4,oc1[0][0]), MAX(oc2[0][0], oc3[0][0])), oc4[0][0]);
    double max_h MAX(MAX(MAX(4,oc1[0][1]), MAX(oc2[0][1], oc3[0][1])), oc4[0][1]);
    
    cImage op = cImage(MAX(inputImg.getWidth(), max_w)+MOD(MIN(0, min_w)+0.5),
                        MAX(inputImg.getHeight(), max_h)+MOD(MIN(0, min_h))+0.5);
    mat inv = inverse(m);
    /*
    //if(opts.bilinear){
        a0 = oc1[0][0];         b0 = oc1[0][1];
        a1 = oc4[0][0]-a0;      b1 = oc4[0][1]-b0;
        a2 = oc2[0][0]-a0;      b2 = oc2[0][1]-b0;
        a3 = oc3[0][0]-a0-a1;   b3 = oc3[0][1]-b0-b1;
   // }
    
    for (int i=0;i<op.getWidth();i++)  {
        for(int j=0;j<op.getHeight();j++)  {
            for(double X=0;X<1;X+=(1/numSubPixels)) {
                for(double Y=0;Y<1;Y+=(1/numSubPixels)) {
                    vector2D newPos{i+X+min_w,j+Y+min_h};
                    //if not bilinear
                    mat orig = inv*makeMatrix(newPos);
                    if(opts.own)
                        orig = (*own(newmap, *orig))*(*orig);
                    //printf("(%d, %d)->(%d, %d)\n", x, y, int(orig->x+0.5), int(orig->y+0.5));
                    resclr=resclr+pmap->getna(orig->x+sx+0.5, orig->y+sy+0.5);
                }
            }
        }
    }
}*/
