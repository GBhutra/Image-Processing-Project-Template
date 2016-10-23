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

