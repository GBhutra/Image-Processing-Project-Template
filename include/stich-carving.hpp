//
//  stich-carving.h
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 11/23/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef stich_carving_h
#define stich_carving_h

#include "cImage.hpp"

/*
 *  Energy function : deltaX = (deltaR + deltaG + deltaB)/3
 */

double getEnergy(cImage& img, int x, int y) {
    cPixel<RGB>  p(RGB{0,0,0}), pL(RGB{0,0,0}), pR(RGB{0,0,0}), pU(RGB{0,0,0}),  pD(RGB{0,0,0});
    short rXErr, gXErr, bXErr, rYErr, gYErr, bYErr;
    rXErr=gXErr=bXErr=rYErr=gYErr=bYErr=0;
    if (0==x)   {
        if (0==y)   {
            p = img.getPixelAtXY(x, y);
            pR = img.getPixelAtXY(x+1, y);
            pU = img.getPixelAtXY(x, y+1);
            
            rXErr = (pR.getRed()-p.getRed());
            gXErr = (pR.getGreen()-p.getGreen());
            bXErr = (pR.getBlue()-p.getBlue());
            
            rYErr = (pU.getRed() - p.getRed());
            gYErr = (pU.getGreen() - p.getGreen());
            bYErr = (pU.getBlue() - p.getBlue());
        }
        else if (img.getHeight()-1 == y)    {
            p = img.getPixelAtXY(x, y);
            pR = img.getPixelAtXY(x+1, y);
            pD = img.getPixelAtXY(x, y-1);
            
            rXErr = (pR.getRed()-p.getRed());
            gXErr = (pR.getGreen()-p.getGreen());
            bXErr = (pR.getBlue()-p.getBlue());
            
            rYErr = (p.getRed() - pD.getRed());
            gYErr = (p.getGreen() - pD.getGreen());
            bYErr = (p.getBlue() - pD.getBlue());
        }
        else    {
            p = img.getPixelAtXY(x, y);
            pR = img.getPixelAtXY(x+1, y);
            pU = img.getPixelAtXY(x, y+1);
            pD = img.getPixelAtXY(x+1, y-1);
            
            rXErr = (pR.getRed()-p.getRed());
            gXErr = (pR.getGreen()-p.getGreen());
            bXErr = (pR.getBlue()-p.getBlue());
            
            rYErr = ((2*p.getRed())-pU.getRed()-pD.getRed());
            gYErr = ((2*p.getGreen())-pU.getGreen()-pD.getGreen());
            bYErr = ((2*p.getBlue())-pU.getBlue()-pD.getBlue());

        }
    }
    else if (img.getWidth()-1==x)   {
        if (0==y)   {
            p = img.getPixelAtXY(x, y);
            pL = img.getPixelAtXY(x-11, y);
            pU = img.getPixelAtXY(x, y+1);
            
            rXErr = (p.getRed() - pL.getRed());
            gXErr = (p.getGreen() - pL.getGreen());
            bXErr = (p.getBlue() - pL.getBlue());
            
            rYErr = (pU.getRed() - p.getRed());
            gYErr = (pU.getGreen() - p.getGreen());
            bYErr = (pU.getBlue() - p.getBlue());
        }
        else if (img.getHeight()-1 == y)    {
            p = img.getPixelAtXY(x, y);
            pL = img.getPixelAtXY(x-11, y);
            pD = img.getPixelAtXY(x, y-1);
            
            rXErr = (p.getRed() - pL.getRed());
            gXErr = (p.getGreen() - pL.getGreen());
            bXErr = (p.getBlue() - pL.getBlue());
            
            rYErr = (p.getRed() - pD.getRed());
            gYErr = (p.getGreen() - pD.getGreen());
            bYErr = (p.getBlue() - pD.getBlue());
        }
        else    {
            p = img.getPixelAtXY(x, y);
            pL = img.getPixelAtXY(x-1, y);
            pU = img.getPixelAtXY(x, y+1);
            pD = img.getPixelAtXY(x, y-1);
            
            rXErr = (p.getRed() - pL.getRed());
            gXErr = (p.getGreen() - pL.getGreen());
            bXErr = (p.getBlue() - pL.getBlue());
            
            rYErr = ((2*p.getRed())-pU.getRed()-pD.getRed());
            gYErr = ((2*p.getGreen())-pU.getGreen()-pD.getGreen());
            bYErr = ((2*p.getBlue())-pU.getBlue()-pD.getBlue());

        }
    }
    else if (0==y)   {
        p = img.getPixelAtXY(x, y);
        pL = img.getPixelAtXY(x-1, y);
        pR = img.getPixelAtXY(x+1, y);
        pU = img.getPixelAtXY(x, y+1);
        
        rXErr = ((2*p.getRed())-pR.getRed()-pL.getRed());
        gXErr = ((2*p.getGreen())-pR.getGreen()-pL.getGreen());
        bXErr = ((2*p.getBlue())-pR.getBlue()-pL.getBlue());
        
        rYErr = (p.getRed() - pU.getRed());
        gYErr = (p.getGreen() - pU.getGreen());
        bYErr = (p.getBlue() - pU.getBlue());
    }
    else if (img.getHeight()-1 == y)    {
        p = img.getPixelAtXY(x, y);
        pL = img.getPixelAtXY(x-1, y);
        pR = img.getPixelAtXY(x+1, y);
        pD = img.getPixelAtXY(x, y-1);
        
        rXErr = ((2*p.getRed())-pR.getRed()-pL.getRed());
        gXErr = ((2*p.getGreen())-pR.getGreen()-pL.getGreen());
        bXErr = ((2*p.getBlue())-pR.getBlue()-pL.getBlue());
        
        rYErr = (p.getRed() - pD.getRed());
        gYErr = (p.getGreen() - pD.getGreen());
        bYErr = (p.getBlue() - pD.getBlue());
    }
    else {
        p = img.getPixelAtXY(x, y);
        pL = img.getPixelAtXY(x-1, y);
        pR = img.getPixelAtXY(x+1, y);
        pD = img.getPixelAtXY(x, y-1);
        pU = img.getPixelAtXY(x, y+1);
        
        rXErr = ((2*p.getRed())-pR.getRed()-pL.getRed());
        gXErr = ((2*p.getGreen())-pR.getGreen()-pL.getGreen());
        bXErr = ((2*p.getBlue())-pR.getBlue()-pL.getBlue());
        
        rYErr = ((2*p.getRed())-pU.getRed()-pD.getRed());
        gYErr = ((2*p.getGreen())-pU.getGreen()-pD.getGreen());
        bYErr = ((2*p.getBlue())-pU.getBlue()-pD.getBlue());
        
    }
    
    double XerrAvg = (rXErr+gXErr+bXErr)/3;
    //double YerrAvg = (rYErr+gYErr+bYErr)/3;
    //return (XerrAvg+YerrAvg)/2;
    return XerrAvg;
}

void getSeam(cImage& im, RGB col = RGB{0,255,0})    {
    int minIndex=0;
    double minErr = 765.0;
    //find the min energy pixel
    for (int x=0;x<im.getWidth();x++)    {
        double errAvg = getEnergy(im, x, im.getHeight()-2);
        if (minErr>errAvg)  {
            minErr = errAvg;
            minIndex = x;
        }
    }
    for (int j=im.getHeight()-1;j>=0;j--)   {
        double er1, er0, er2;
        for (int i=0;i<im.getWidth();i++)    {
            if (i==minIndex)
                im.setPixelAtXY(i, j, col);
            else
                im.setPixelAtXY(i, j, im.getPixelAtXY(i, j));
        }
        if (0!=j)  {
            if (0==minIndex)    {
                er0 = getEnergy(im,minIndex,j-1);
                er2 = getEnergy(im,minIndex+1,j-1);
                if (er2<er0)
                    minIndex = minIndex+1;
            }
            else if (im.getWidth()-1==minIndex) {
                er1 = getEnergy(im,minIndex-1,j-1);
                er0 = getEnergy(im,minIndex,j-1);
                if (er1<er0)
                    minIndex = minIndex-1;
            }
            else    {
                er0 = getEnergy(im,minIndex,j-1);
                er1 = getEnergy(im,minIndex-1,j-1);
                er2 = getEnergy(im,minIndex+1,j-1);
                if (er2<er0)
                    minIndex = minIndex+1;
                else if (er1<er0)
                    minIndex = minIndex-1;
            }
        }
    }
}

void carveSeam(cImage& inImg, cImage& outImg)  {
    int minIndex=0;
    double minErr = 765.0;
    //find the min energy pixel
    for (int x=0;x<inImg.getWidth();x++)    {
        double errAvg = getEnergy(inImg, x, inImg.getHeight()-2);
        if (minErr>errAvg)  {
            minErr = errAvg;
            minIndex = x;
        }
    }
    for (int j=inImg.getHeight()-1;j>=0;j--)   {
        double er1, er0, er2;
        int val=0;
        for (int i=0;i<inImg.getWidth()-1;i++)    {
            if (i==minIndex)
                val=-1;
            else
                outImg.setPixelAtXY(i+val, j, inImg.getPixelAtXY(i, j));
        }
        if (0!=j)  {
            if (0==minIndex)    {
                er0 = getEnergy(inImg,minIndex,j-1);
                er2 = getEnergy(inImg,minIndex+1,j-1);
                if (er2<er0)
                    minIndex = minIndex+1;
            }
            else if (inImg.getWidth()-1==minIndex) {
                er1 = getEnergy(inImg,minIndex-1,j-1);
                er0 = getEnergy(inImg,minIndex,j-1);
                if (er1<er0)
                    minIndex = minIndex-1;
            }
            else    {
                er0 = getEnergy(inImg,minIndex,j-1);
                er1 = getEnergy(inImg,minIndex-1,j-1);
                er2 = getEnergy(inImg,minIndex+1,j-1);
                if (er2<er0)
                    minIndex = minIndex+1;
                else if (er1<er0)
                    minIndex = minIndex-1;
            }
        }
    }
}

void stich(cImage& im1, cImage& im2, cImage& out, int left, int right) {
    double minE = getEnergy(im1, left, im1.getHeight()-2) - getEnergy(im2, left, im1.getHeight()-2);
    int minIndex = left;
    for (int i=left+1;i<=right;i++)   {
        double eDiff = getEnergy(im1, i, im1.getHeight()-2) - getEnergy(im2, i, im1.getHeight()-2);
        if (minE > eDiff)   {
            minE = eDiff;
            minIndex = i;
        }
    }
    for (int i=0;i<im1.getWidth();i++)    {
        if (i<minIndex) {
            out.setPixelAtXY(i, im1.getHeight()-1, im1.getPixelAtXY(i, im1.getHeight()-1));
            out.setPixelAtXY(i, im1.getHeight()-2, im1.getPixelAtXY(i, im1.getHeight()-2));
        }
        else    {
            out.setPixelAtXY(i, im2.getHeight()-1, im2.getPixelAtXY(i, im2.getHeight()-1));
            out.setPixelAtXY(i, im2.getHeight()-2, im2.getPixelAtXY(i, im2.getHeight()-2));
        }
    }
    for (int j=im1.getHeight()-3;j>0;j--)   {
        double e1 = getEnergy(im1, minIndex-1, j) - getEnergy(im2, minIndex-1, j);
        double e2 = getEnergy(im1, minIndex, j) - getEnergy(im2, minIndex-1, j);
        double e3 = getEnergy(im1, minIndex+1, j) - getEnergy(im2, minIndex+1, j);
        if (e1 < e2 && e1 < e3)
            minIndex--;
        else if (e3 < e1 && e3 < e2)
            minIndex++;
        for (int i=0;i<im1.getWidth();i++)    {
            if (i<minIndex)
                out.setPixelAtXY(i, j, im1.getPixelAtXY(i, j));
            else
                out.setPixelAtXY(i, j, im2.getPixelAtXY(i, j));
        }
    }
}


#endif /* stich_carving_h */
