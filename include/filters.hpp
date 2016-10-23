//
//  filters.h
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef filters_h
#define filters_h


#include "pixel.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "vector2d.hpp"
#include "2dShapes.hpp"

typedef vector<vector<double>> kernel;

double gaussian (double x, double mu, double sigma) {
    return std::exp( -(((x-mu)/(sigma))*((x-mu)/(sigma)))/2.0 );
}

namespace globalFilter {
    void normalizeImg(cImage& inputImg, cImage& outImg)   {
        int rMin=255,rMax=0;
        int gMin=255,gMax=0;
        int bMin=255,bMax=0;
        cPixel p;
        for (int x=0;x<inputImg.getHeight();++x) {
            for (int y=0;y<inputImg.getWidth();y++) {
                p = inputImg.getPixelAtXY(x,y);
                rMax = p.getRed()   > rMax ? p.getRed()     : rMax;
                gMax = p.getGreen() > gMax ? p.getGreen()   : gMax;
                bMax = p.getBlue()  > bMax ? p.getBlue()    : bMax;
                rMin = p.getRed()   < rMin ? p.getRed()     : rMin;
                gMin = p.getGreen() < gMin ? p.getGreen()   : gMin;
                bMin = p.getBlue()  < bMin ? p.getBlue()    : bMin;
            }
        }
        double r=0,g=0,b=0;
        int rDiff = rMax-rMin;
        int gDiff = gMax-gMin;
        int bDiff = bMax-bMin;
        for (int x=0;x<inputImg.getHeight();++x) {
            for (int y=0;y<inputImg.getWidth();y++) {
                p = inputImg.getPixelAtXY(x,y);
                r = p.getRed();
                g = p.getGreen();
                b = p.getBlue();
                r = ((r-rMin)/rDiff)*255;
                g = ((g-gMin)/gDiff)*255;
                b = ((b-bMin)/bDiff)*255;
                RGB col = {static_cast<int>(r),static_cast<int>(g),static_cast<int>(b)};
                outImg.setPixelAtXY(x,y,col);
            }
        }
    }
}

namespace localFilter {
    void radialFilter(cImage& img,int numCircles)  {
        int cenX =img.getWidth()/2,cenY=img.getHeight()/2;
        float maxRadius = cenX > cenY ? cenY : cenX;
        vector<cCircle> rings;
        double radius = maxRadius;
        for (int i=0;i<numCircles;i++)  {
            rings.push_back(cCircle(cenY,cenX,radius));
            radius = radius/numCircles;
        }
        cPixel p;
        int rSum=0,gSum=0,bSum=0,numPixels=0;
        for (int x=0;x<img.getHeight();++x) {
            for (int y=0;y<img.getWidth();y++) {
                for (int i=rings.size()-2;i>=0;i--) {
                    if(!rings[i].inCircle(x,y))  {
                        int kSize = rings.size()-1-i;
                        int kernelDimension = 2*kSize+1;
                        p = img.getPixelAtXY(x,y);
                        rSum=0,gSum=0,bSum=0,numPixels=0;
                        for (int i=0;i<kernelDimension;i++) {
                            for (int j=0;j<kernelDimension;j++) {
                                int h = x-kSize+i;
                                int w = y-kSize+j;
                                if (0<=w && img.getWidth()>w && 0<=h && img.getHeight()>h)    {
                                    cPixel pTemp = img.getPixelAtXY(h,w);
                                    rSum+=pTemp.getRed();
                                    bSum+=pTemp.getBlue();
                                    gSum+=pTemp.getGreen();
                                    numPixels++;
                                }
                            }
                        }
                        rSum = rSum/numPixels;
                        bSum = bSum/numPixels;
                        gSum = gSum/numPixels;
                        RGB col = {rSum,gSum,bSum};
                        img.setPixelAtXY(x,y,col);
                    }
                }
            }
        }
    }
    
    void applyConvolutionFilter(cImage& inputImg, cImage& outImg, kernel k, bool normalizedKernel = false)   {
        if (0==k.size() || 0==(k.size()%2))
            return;
        if (0==k[0].size() || 0==(k[0].size()%2))
            return;
        if (inputImg.getHeight()!=outImg.getHeight() || inputImg.getWidth()!=inputImg.getWidth())
            return;
        double sum=0;
        //normalized
        if (!normalizedKernel)  {
            for (int i=0;i<k.size();i++) {
                for (int j=0;j<k[0].size();j++) {
                    sum+=k[i][j];
                }
            }
            for (int i=0;i<k.size();i++) {
                for (int j=0;j<k[0].size();j++) {
                    k[i][j]/=sum;
                }
            }
        }
        cPixel p;
        double rSum=0,gSum=0,bSum=0;
        for (int x=0;x<inputImg.getHeight();++x) {
            for (int y=0;y<inputImg.getWidth();y++) {
                p = inputImg.getPixelAtXY(x, y);
                rSum=0,gSum=0,bSum=0;
                for (int i=0;i<k.size();i++) {
                    for (int j=0;j<k[0].size();j++) {
                        int h = x-(k.size()%2)+i;
                        int w = y-(k[0].size()%2)+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            cPixel pTemp = inputImg.getPixelAtXY(h,w);
                            rSum+=pTemp.getRed()*k[i][j];
                            bSum+=pTemp.getBlue()*k[i][j];;
                            gSum+=pTemp.getGreen()*k[i][j];;
                        }
                    }
                }
                RGB col = {static_cast<int>(rSum),static_cast<int>(gSum),static_cast<int>(bSum)};
                outImg.setPixelAtXY(x, y,col);
            }
        }
    }
    
    void boxBlur(cImage& inputImg, cImage& outImg, int kSize)   {
        kernel k(2*kSize+1,vector<double>(2*kSize+1,1));
        applyConvolutionFilter(inputImg,outImg,k);
    }
    
    void gussianBlur(cImage& inputImg, cImage& outImg, int kSize)   {
        if (1>=kSize)
            return;
        double sigma = kSize/2;
        kernel k(2*kSize+1,vector<double>(2*kSize+1,1));
        for (int row = 0; row < k.size(); row++)    {
            for (int col = 0; col < k[row].size(); col++) {
                double x = gaussian(row, kSize, sigma) * gaussian(col, kSize, sigma);
                k[row][col] = x;
            }
        }
        applyConvolutionFilter(inputImg,outImg,k);
    }
    
    void derivativeFilter(cImage& inputImg, cImage& outImg, int kSize)   {
        kernel k(2*kSize+1,vector<double>(2*kSize+1,0));
        for (int i=0;i<k.size();i++) {
            for (int j=0;j<k[i].size();j++) {
                if (i==j)   {
                    if (i<k.size()/2)
                        k[i][j] = -1;
                    else if (i>k.size()/2)
                        k[i][j] = 1;
                    else
                        k[i][j] = 0;
                }
                else if(j==(k.size()-1-i))  {
                    if (i>j)
                        k[i][j] = -1;
                    else
                        k[i][j] = 1;
                }
            }
        }
        k[k.size()/2][0]=-1;
        k[k.size()/2][k.size()-1]=1;
        for (auto row: k)   {
            for(auto col:row)
                cout<<col<<" ";
            cout<<endl;
        }
        cImage temp(inputImg.getWidth(), inputImg.getHeight());
        applyConvolutionFilter(inputImg, temp, k,true);
        globalFilter::normalizeImg(temp,outImg);
    }
    
    void erosionFilter(cImage& inputImg, cImage& outImg, int kSize)   {
        kernel k(2*kSize+1,vector<double>(2*kSize+1,1));
        int rMin=255,bMin=255,gMin=255;
        cPixel p;
        for (int x=0;x<inputImg.getHeight();++x) {
            for (int y=0;y<inputImg.getWidth();++y) {
                rMin=bMin=gMin=255;
               for (int i=0;i<(2*kSize+1);i++) {
                   for (int j=0;j<(2*kSize+1);j++) {
                       int h = x-kSize+i;
                       int w = y-kSize+j;
                       if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                           p = inputImg.getPixelAtXY(h, w);
                           rMin = rMin > p.getRed()     ?   p.getRed()  :   rMin;
                           gMin = gMin > p.getGreen()   ?   p.getGreen():   gMin;
                           bMin = bMin > p.getBlue()    ?   p.getBlue() :   bMin;
                       }
                   }
               }
               RGB col = {rMin,gMin,bMin};
               outImg.setPixelAtXY(x, y, col);
            }
        }
    }
    void dilationFilter(cImage& inputImg, cImage& outImg, int kSize)   {
        kernel k(2*kSize+1,vector<double>(2*kSize+1,1));
        int rMax=255,bMax=255,gMax=255;
        cPixel p;
        for (int x=0;x<inputImg.getHeight();++x) {
            for (int y=0;y<inputImg.getWidth();y++) {
                rMax=bMax=gMax=0;
                for (int i=0;i<(2*kSize+1);i++) {
                    for (int j=0;j<(2*kSize+1);j++) {
                        int h = x-kSize+i;
                        int w = y-kSize+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            p = inputImg.getPixelAtXY(h,w);
                            rMax = rMax < p.getRed()     ?   p.getRed()  :   rMax;
                            gMax = gMax < p.getGreen()   ?   p.getGreen():   gMax;
                            bMax = bMax < p.getBlue()    ?   p.getBlue() :   bMax;
                        }
                    }
                }
                RGB col = {rMax,gMax,bMax};
                outImg.setPixelAtXY(x, y, col);
            }
        }
    }

}

#endif /* filters_h */
