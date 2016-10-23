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
#include "utility.hpp"

class cImage	{
	//friend class cHistogram;
    int iHeight, iWidth, iNumChannels;
	vector<vector<cPixel>>cPixMap;
public:
	cImage(): iWidth(0), iHeight(0)	{};
	cImage(int x, int y): iWidth(x), iHeight(y)	{
		cPixMap.resize(iWidth,vector<cPixel>(iHeight,cPixel(0,0,0)));
	};
    cImage(int x, int y, RGB color): iWidth(x), iHeight(y)	{
        cPixMap.resize(iWidth,vector<cPixel>(iHeight,cPixel(get<0>(color),get<1>(color),get<2>(color))));
    };
	cImage(string);

	//getter and setters
	inline int getHeight()  {       return iHeight;	};
	inline int getWidth()   {       return iWidth;	};
	cPixel getPixelAtXY(int x,int y);

	void readPPMFile(string filename);
	void setPixelAtXY(int x,int y, RGB color);
    void setPixelAtXY(int x,int y, cPixel);
	void writeToPPMFile(string filename);
    friend void imgToArray(cImage& img, char* ptr);
};

#endif /* cImage_hpp */
