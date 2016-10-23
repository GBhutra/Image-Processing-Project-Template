#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "pixel.hpp"

class cImage	{
	//friend class cHistogram;
    int m_iHeight, m_iWidth, m_iNumChannels;
	vector<vector<cPixel>>m_arrCPixels;
public:
	cImage(): m_iWidth(0), m_iHeight(0)	{};
	cImage(int x, int y): m_iWidth(x), m_iHeight(y)	{
		m_arrCPixels.resize(m_iHeight,vector<cPixel>(m_iWidth,cPixel(0,0,0)));
	};
    cImage(int x, int y, RGB color): m_iWidth(x), m_iHeight(y)	{
        m_arrCPixels.resize(m_iHeight,vector<cPixel>(m_iWidth,cPixel(get<0>(color),get<1>(color),get<2>(color))));
    };
	cImage(string);

	//getter and setters
	inline int getHeight()  {       return m_iHeight;	};
	inline int getWidth()   {       return m_iWidth;	};
	cPixel getPixelAtXY(int x,int y);

	void readPPMFile(string filename);
	void setPixelAtXY(int x,int y, RGB color);
    void setPixelAtXY(int x,int y, cPixel);
	void writeToPPMFile(string filename);
    friend void imgToArray(cImage& img, char* ptr);
};

#endif
