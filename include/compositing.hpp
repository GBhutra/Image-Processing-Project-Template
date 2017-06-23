//
//  compositing.hpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 11/14/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef compositing_h
#define compositing_h

#include <functional>
#include "utility.hpp"
#include "cImage.hpp"
#include "cPixel.hpp"



namespace compositing {
    RGB WHITE{255,255,255};
    RGB BLACK{0,0,0};
    RGB GRAY{128,128,128};
    
    auto max = [](cPixel<RGB>& a, cPixel<RGB>& b) { return RGB{
        (a.getRed()     > b.getRed()    ? a.getRed() : b.getRed()),
        (a.getGreen()   > b.getGreen()  ? a.getGreen() : b.getGreen()),
        (a.getBlue()    > b.getBlue()   ? a.getBlue() : b.getBlue())};
    };
    auto min = [](cPixel<RGB>& a, cPixel<RGB>& b) { return RGB {
        (a.getRed() < b.getRed() ? a.getRed() : b.getRed()),
        (a.getGreen() < b.getGreen() ? a.getGreen() : b.getGreen()),
        (a.getBlue() < b.getBlue() ? a.getBlue() : b.getBlue()) };
    };
    auto subtract = [](cPixel<RGB>& a, cPixel<RGB>& b) { return clamp({
        (a.getRed() - b.getRed()),
        (a.getGreen() - b.getGreen()),
        (a.getBlue() - b.getBlue()) });
    };
    auto multiply = [](cPixel<RGB>& a, cPixel<RGB>& b) { return RGB {
        (a.getRed()*b.getRed()/255),
        (a.getGreen()*b.getGreen()/255),
        (a.getBlue()*b.getBlue()/255) };
    };

    template <typename functor>
    void compose(cImage& im1, cImage& im2, functor func ,cImage& out )  {
        for (int i = 0;i<im1.getWidth(); i++)   {
            for(int j=0;j<im2.getHeight();j++)  {
                auto p1 = im1.getPixelAtXY(i, j);
                auto p2 = im2.getPixelAtXY(i, j);
                RGB col = func(p1,p2);
                out.setPixelAtXY(i, j, col);
            }
        }
    }
    
    template <typename functor>
    void genAlphaMask(cImage& inputImg, cImage& outPutImg, functor func)   {
        for(int i = 0; i<inputImg.getWidth();i++)   {
            for (int j=0;j<inputImg.getHeight();j++)    {
                auto p = inputImg.getPixelAtXY(i, j);
                short val = func(p);
                RGB col{val,val,val};
                outPutImg.setPixelAtXY(i, j, col);
            }
        }
    }
    
    void composeFromMask(cImage& fImg, cImage& mask, cImage& bImg, cImage& outPutImg)   {
        for(int i = 0; i<outPutImg.getWidth();i++)   {
            for (int j=0;j<outPutImg.getHeight();j++)    {
                auto p = mask.getPixelAtXY(i, j);
                auto pBI = bImg.getPixelAtXY(i, j);
                double mask = p.getRed();
                mask = mask/255;
                if (mask>0)   {
                    auto pFI = fImg.getPixelAtXY(i, j);
                    RGB col;
                        get<0>(col) = static_cast<short>((double)pFI.getRed()*mask+(double)pBI.getRed()*(1-mask));
                        get<1>(col) = static_cast<short>((double)pFI.getGreen()*mask+(double)pBI.getGreen()*(1-mask));
                        get<2>(col) = static_cast<short>((double)pFI.getBlue()*mask+(double)pBI.getBlue()*(1-mask));
                    //RGB col = compose(pFI.getColor(),pBI.getColor(),mask);
                    outPutImg.setPixelAtXY(i, j, col);
                }
                else
                    outPutImg.setPixelAtXY(i, j, pBI);
            }
        }
    }
}

#endif /* compositing_h */
