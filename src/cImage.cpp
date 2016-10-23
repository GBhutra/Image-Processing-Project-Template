//
//  cImage.cpp
//  ImageProcessingProjects
//
//  Created by Ghanshyam Bhutra on 10/22/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "cImage.hpp"
using namespace std;

cImage::cImage(string filename)	{
	readPPMFile(filename);
}

void cImage::readPPMFile(string filename)	{
	int tmpint;
    std::string str;
    std::ifstream inFile(filename);
    if (!std::getline(inFile, str))	{
        DBG_LOG("Can't open PPM file "<<filename<<". Exiting.\n"<<std::endl);
        exit (1);
    }
    tmpint = std::stoi(str.substr(1));
    if (tmpint != 6) {
        DBG_LOG("Input file is not ppm. Exiting.\n"<<std::endl);
        exit (1);
    }
    std::getline(inFile, str);
    while('#'==str[0] )  {
        std::getline(inFile,str);
    }
    std::istringstream ss(str);
    ss>>iWidth>>iHeight;
    std::getline(inFile,str);
    iNumChannels = 3;
    cPixMap.resize(iWidth,vector<cPixel>(iHeight,cPixel(0,0,0)));
    for (int i=iWidth-1;i>=0;i--)	{
    	for (int j=0;j<iHeight;j++)	{
            cPixMap[i][j].setRed(inFile.get());
            cPixMap[i][j].setGreen(inFile.get());
            cPixMap[i][j].setBlue(inFile.get());
    	}
    }
    if ((iWidth*iHeight) != (cPixMap.size()*cPixMap[0].size()))	{
        DBG_LOG("PixelCount= "<<((iNumChannels*iWidth)*iHeight)<<" and mPixel.size= "<<cPixMap.size()<<"x"<<cPixMap[0].size()<<std::endl);
        DBG_LOG("Can't allocate image of size "<<iWidth<<"x"<<iHeight<<". Exiting\n"<<std::endl);
        exit (1);
    }

}

void cImage::writeToPPMFile(string filename)	{
	std::ofstream output;
    output.open (filename);
    output<<"P6\n";
    output<<"#This is file is created by gbhutra\n";
    output<<iWidth<<" "<<iHeight<<"\n";
    output<<"255\n";
    for (int i=iWidth-1;i>=0;--i)	{
    	for (int j=0;j<iHeight;++j)	{
    		output<<static_cast<unsigned char>(cPixMap[i][j].getRed());
    		output<<static_cast<unsigned char>(cPixMap[i][j].getGreen());
    		output<<static_cast<unsigned char>(cPixMap[i][j].getBlue());
    	}
    }
    output.close();
}

cPixel cImage::getPixelAtXY(int x,int y)    {
    return cPixMap[x][y];
}
void cImage::setPixelAtXY(int x, int y, RGB col)    {
    cPixMap[x][y].setRed(get<0>(col));
    cPixMap[x][y].setGreen(get<1>(col));
    cPixMap[x][y].setBlue(get<2>(col));
}

void cImage::setPixelAtXY(int x, int y, cPixel p)    {
    cPixMap[x][y] = p;
}

void cHistogram::genHistogram(cImage& img)    {
    for (int i=0;i<img.getHeight();++i) {
        for (int j=0;j<img.getWidth();++j) {
            cPixel p = img.getPixelAtXY(i,j);
            arrRed[p.getRed()]++;
            arrGreen[p.getGreen()]++;
            arrBlue[p.getBlue()]++;
        }
    }
    int max=0;
    for (int i=0;i<256;i++)    {
        max=max<arrRed[i] ? arrRed[i] : max;
        max=max<arrGreen[i] ? arrGreen[i] : max;
        max=max<arrBlue[i] ? arrBlue[i] : max;
    }
    int x=0,y=0;
    double temp=0.8*iHeight;
    double normVal = 0;
    RGB red = {255,0,0};
    RGB green = {0,255,0};
    RGB blue = {0,0,255};
    for (int i=0;i<256;i++)   {
        normVal = arrRed[i]/max;
        y = static_cast<int>(temp*normVal);
        setPixelAtXY(x,y,red);
        normVal = arrGreen[i]/max;
        y = static_cast<int>(temp*normVal);
        setPixelAtXY(x,y,green);
        normVal = arrBlue[i]/max;
        y = static_cast<int>(temp*normVal);
        setPixelAtXY(x,y,blue);
        x+=iWidth/256;
    }
}

/*cImage cHistogram::drawHist()   {
    int max=0;
    for (int i=0;i<m_iArrRed.size();i++)    {
        max=max<m_iArrRed[i] ? m_iArrRed[i] : max;
        max=max<m_iArrGreen[i] ? m_iArrGreen[i] : max;
        max=max<m_iArrBlue[i] ? m_iArrBlue[i] : max;
    }
    
    cVector2D currR = cVector2D(1,(m_iArrRed[0]/(double)max)*280);
    cVector2D nextR;
    for (int i=1;i<m_iArrRed.size();i++)    {
        nextR = cVector2D(i*2+1,(m_iArrRed[i]/(double)max)*280);
        connectVector2DByLine(currR,nextR,pixels,{255,0,0});
        currR = nextR;
    }
    cVector2D currG = cVector2D(1,(m_iArrGreen[0]/(double)max)*280);
    cVector2D nextG;
    for (int i=1;i<m_iArrGreen.size();i++)    {
        nextG = cVector2D(i*2+1,(m_iArrGreen[i]/(double)max)*280);
        connectVector2DByLine(currG,nextG,pixels,{0,255,0});
        currG = nextG;
    }
    cVector2D currB = cVector2D(1,(m_iArrBlue[0]/(double)max)*280);
    cVector2D nextB;
    for (int i=1;i<m_iArrGreen.size();i++)    {
        nextB = cVector2D(i*2+1,(m_iArrBlue[i]/(double)max)*280);
        connectVector2DByLine(currB,nextB,pixels,{0,0,255});
        currB = nextB;
    }
    return pixels;
};*/


void imgToArray(cImage& img, char* ptr)    {
    int iterator =0;
    for (int i=0;i<img.iWidth;++i)	{
        for (int j=0;j<img.iHeight;++j)	{
            ptr[iterator++]=img.cPixMap[i][j].getRed();
            ptr[iterator++]=img.cPixMap[i][j].getGreen();
            ptr[iterator++]=img.cPixMap[i][j].getBlue();
        }
    }
};

