//
//  cImage.hpp
//  ImageProcessingProjects
//
//  Created by Ghanshyam Bhutra on 10/22/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef cImage_hpp
#define cImage_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "cPixel.hpp"
#include "cVector2d.hpp"
#include "utility.hpp"


class cImage	{
protected:
    int iHeight, iWidth, iNumChannels;
	vector<vector<cPixel<RGB>>>cPixMap;
public:
	cImage(): iWidth(0), iHeight(0)	{};
	cImage(int x, int y): iWidth(x), iHeight(y)	{
        cPixMap.resize(iWidth,vector<cPixel<RGB>>(iHeight,cPixel<RGB>(RGB{0,0,0})));
	};
    cImage(int x, int y, RGB color): iWidth(x), iHeight(y)	{
        cPixMap.resize(iWidth,vector<cPixel<RGB>>(iHeight,cPixel<RGB>(color)));
    };
    cImage(int x, int y, RGB color1, RGB color2);
	cImage(string);

	//getter and setters
    int getHeight()  {       return iHeight;	};
    int getWidth()   {       return iWidth;	};
	cPixel<RGB> getPixelAtXY(int x,int y);

	void readPPMFile(string filename);
	void setPixelAtXY(int x,int y, RGB color);
    void setPixelAtXY(int x,int y, cPixel<RGB>);
    void setPixelAtXY(int x,int y, cPixel<HSV>);
    
	void writeToPPMFile(string filename);
    friend void imgToArray(cImage& img, char* ptr);
};

class cHistogram : public cImage{
private:
    vector<int> arrRed;
    vector<int> arrBlue;
    vector<int> arrGreen;
public:
    cHistogram() : arrRed(vector<int>(256,0)),arrBlue(vector<int>(256,0)),arrGreen(vector<int>(256,0)), cImage() {};
    cHistogram(int width, int height) : arrRed(vector<int>(256,0)),arrBlue(vector<int>(256,0)),arrGreen(vector<int>(256,0)), cImage(width, height) {};
    cHistogram(int width, int height, RGB bgColor) : arrRed(vector<int>(256,0)),arrBlue(vector<int>(256,0)),arrGreen(vector<int>(256,0)), cImage(width, height,bgColor) {};
    
    void genHistogram(cImage& img);
};


#endif /* cImage_hpp */
