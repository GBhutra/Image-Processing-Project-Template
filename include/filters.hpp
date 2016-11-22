//
//  filters.h
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef filters_h
#define filters_h


#include "cPixel.hpp"
#include "cImage.hpp"
#include "cVector2d.hpp"
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
        cPixel<RGB> p(RGB{0,0,0});
        for (int x=0;x<inputImg.getWidth();++x) {
            for (int y=0;y<inputImg.getHeight();y++) {
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
        for (int x=0;x<inputImg.getWidth();++x) {
            for (int y=0;y<inputImg.getHeight();y++) {
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
    void normalizeImg(cImage& inputImg, cImage& outImg)   {
        short color=0;
        for (int x=0;x<inputImg.getWidth();++x) {
            for (int y=0;y<inputImg.getHeight();y++) {
                cPixel<RGB> p = inputImg.getPixelAtXY(x, y);
                color+=p.getRed();
                color+=p.getBlue();
                color+=p.getGreen();
                color = color/3;
                outImg.setPixelAtXY(x, y, RGB{color,color,color});
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
        cPixel<RGB> p(RGB{0,0,0});
        double rSum=0,gSum=0,bSum=0;
        for (int x=0;x<inputImg.getWidth();x++) {
            for (int y=0;y<inputImg.getHeight();y++) {
                p = inputImg.getPixelAtXY(x, y);
                rSum=0,gSum=0,bSum=0;
                for (int i=0;i<k[0].size();i++) {
                    for (int j=0;j<k.size();j++) {
                        int w = x-(k.size()%2)+i;
                        int h = y-(k[0].size()%2)+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            cPixel<RGB> pTemp = inputImg.getPixelAtXY(w,h);
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
    
    void applyConvolutionFilter(cImage& inputImg, cImage& outImg, kernel k, int x, int y, bool normalizedKernel = false)   {
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
        cPixel<RGB> p(RGB{0,0,0});
        double rSum=0,gSum=0,bSum=0;
        p = inputImg.getPixelAtXY(x, y);
        rSum=0,gSum=0,bSum=0;
        for (int i=0;i<k[0].size();i++) {
            for (int j=0;j<k.size();j++) {
                int w = x-(k.size()%2)+i;
                int h = y-(k[0].size()%2)+j;
                if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                    cPixel<RGB> pTemp = inputImg.getPixelAtXY(w,w);
                    rSum+=pTemp.getRed()*k[i][j];
                    bSum+=pTemp.getBlue()*k[i][j];;
                    gSum+=pTemp.getGreen()*k[i][j];;
                }
            }
        }
        RGB col = {static_cast<int>(rSum),static_cast<int>(gSum),static_cast<int>(bSum)};
        outImg.setPixelAtXY(x, y,col);
    }
    
    void motionBlur(cImage& inputImg, cImage& outImg, cImage& coImg, int kSize)   {
        int rSum,bSum,gSum;
        cPixel<RGB> p(RGB{0,0,0});
        kernel k(2*kSize+1,vector<double>(2*kSize+1,0));
        for (int x=0;x<inputImg.getWidth();++x) {
            for (int y=0;y<inputImg.getHeight();++y) {
                double grayScale = 0;
                for (int i=0;i<k.size();i++) {
                    for (int j=0;j<k[i].size();j++) {
                        int h = x-(k.size()%2)+i;
                        int w = y-(k[0].size()%2)+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            cPixel<RGB> pTemp = coImg.getPixelAtXY(w,h);
                            double GS = pTemp.getRed() + pTemp.getGreen() + pTemp.getBlue();
                            GS = GS/765;
                            k[i][j] = GS;
                            grayScale += GS;
                        }
                    }
                }
                rSum=bSum=gSum=0;
                for (int i=0;i<k.size();i++) {
                    for (int j=0;j<k[0].size();j++) {
                        int w = x-(k.size()%2)+i;
                        int h = y-(k[0].size()%2)+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            cPixel<RGB> pTemp = inputImg.getPixelAtXY(w,h);
                            rSum+=pTemp.getRed()*(k[i][j]/grayScale);
                            bSum+=pTemp.getBlue()*(k[i][j]/grayScale);;
                            gSum+=pTemp.getGreen()*(k[i][j]/grayScale);;
                        }
                    }
                }
                rSum = rSum > 255 ? 255 : rSum;
                gSum = gSum > 255 ? 255 : gSum;
                bSum = bSum > 255 ? 255 : bSum;
                RGB col = {static_cast<int>(rSum),static_cast<int>(gSum),static_cast<int>(bSum)};
                outImg.setPixelAtXY(x, y,col);
            }
        }
    }
    
    
    void boxBlur(cImage& inputImg, cImage& outImg, int kSize)   {
        kernel k(2*kSize+1,vector<double>(2*kSize+1,1));
        localFilter::applyConvolutionFilter(inputImg,outImg,k);
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
        localFilter::applyConvolutionFilter(inputImg,outImg,k);
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
        localFilter::applyConvolutionFilter(inputImg, temp, k,true);
        globalFilter::normalizeImg(temp,outImg);
    }
    
    void erosionFilter(cImage& inputImg, cImage& outImg, int kSize)   {
        kernel k(2*kSize+1,vector<double>(2*kSize+1,1));
        int rMin=255,bMin=255,gMin=255;
        cPixel<RGB> p(RGB{0,0,0});
        for (int x=0;x<inputImg.getWidth();x++) {
            for (int y=0;y<inputImg.getHeight();y++) {
                rMin=bMin=gMin=255;
                for (int i=0;i<(2*kSize+1);i++) {
                    for (int j=0;j<(2*kSize+1);j++) {
                        int w = x-kSize+i;
                        int h = y-kSize+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            p = inputImg.getPixelAtXY(w,h);
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
    void erosionFilter(cImage& inputImg, cImage& outImg, cImage& coImg, int kSize)   {
        int rMin=255,bMin=255,gMin=255;
        cPixel<RGB> p(RGB{0,0,0});
        for (int x=0;x<inputImg.getWidth();++x) {
            for (int y=0;y<inputImg.getHeight();++y) {
                rMin=bMin=gMin=255;
                for (int i=0;i<(2*kSize+1);i++) {
                    for (int j=0;j<(2*kSize+1);j++) {
                        int w = x-kSize+i;
                        int h = y-kSize+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            p = coImg.getPixelAtXY(w, h);
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
        cPixel<RGB> p(RGB{0,0,0});
        for (int x=0;x<inputImg.getWidth();x++) {
            for (int y=0;y<inputImg.getHeight();y++) {
                rMax=bMax=gMax=0;
                for (int i=0;i<(2*kSize+1);i++) {
                    for (int j=0;j<(2*kSize+1);j++) {
                        int w = x-kSize+i;
                        int h = y-kSize+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            p = inputImg.getPixelAtXY(w,h);
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
    void dilationFilter(cImage& inputImg, cImage& outImg, cImage& contImg)   {
        int crMax,cgMax,cbMax,rMax,bMax,gMax;
        crMax=cgMax=cbMax=rMax=bMax=gMax=0;
        cPixel<RGB> p(RGB{0,0,0}),c(RGB{0,0,0});
        for (int x=0;x<contImg.getWidth();x++) {
            for (int y=0;y<contImg.getHeight();y++) {
                p = contImg.getPixelAtXY(x,y);
                crMax = p.getRed() > crMax ? p.getRed():crMax;
                cgMax = p.getGreen() > cgMax ? p.getGreen():cgMax;
                cbMax = p.getBlue() > cbMax ? p.getBlue():cbMax;
            }
        }
        
        for (int x=0;x<inputImg.getWidth();x++) {
            for (int y=0;y<inputImg.getHeight();y++) {
                rMax=bMax=gMax=0;
                int stx = x-(contImg.getWidth()/2);
                int sty = y-(contImg.getHeight()/2);
                for (int i=0;i<contImg.getWidth();i++) {
                    for (int j=0;j<contImg.getHeight();j++) {
                        int w = stx+i;
                        int h = sty+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            c = contImg.getPixelAtXY(i,j);
                            p = inputImg.getPixelAtXY(w,h);
                            rMax = rMax > c.getRed()*p.getRed() ? rMax : c.getRed()*p.getRed();
                            gMax = gMax > c.getGreen()*p.getGreen() ? gMax : c.getGreen()*p.getGreen();
                            bMax = bMax > c.getBlue()*p.getBlue() ? bMax : c.getBlue()*p.getBlue();
                        }
                    }
                    RGB col {crMax==0 ? 255: rMax/crMax, cgMax==0 ? 255: gMax/cgMax, cbMax==0 ? 255: bMax/cbMax};
                    outImg.setPixelAtXY(x, y, col);
                }
            }
        }
    }
}

#endif /* filters_h */
