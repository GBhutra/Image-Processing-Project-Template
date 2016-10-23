#include "image.hpp"

using namespace std;

cImage::cImage(string filename)	{
	readPPMFile(filename);
}

void cImage::readPPMFile(string filename)	{
	int tmpint;
    std::string str;
    std::ifstream inFile(filename);
    if (!std::getline(inFile, str))	{
        std::cout<<"Can't open PPM file "<<filename<<". Exiting.\n"<<std::endl;
        exit (1);
    }
    tmpint = std::stoi(str.substr(1));
    if (tmpint != 6) {
        std::cout<<"Input file is not ppm. Exiting.\n"<<std::endl;
        exit (1);
    }
    std::getline(inFile, str);
    while('#'==str[0] )  {
        std::getline(inFile,str);
    }
    std::istringstream ss(str);
    ss>>m_iWidth>>m_iHeight;
    std::getline(inFile,str);
    m_iNumChannels = 3;
    m_arrCPixels.resize(m_iHeight,vector<cPixel>(m_iWidth,cPixel(0,0,0)));
    for (int i=m_iHeight-1;i>=0;i--)	{
    	for (int j=0;j<m_iWidth;++j)	{
            m_arrCPixels[i][j].setRed(inFile.get());
            m_arrCPixels[i][j].setGreen(inFile.get());
            m_arrCPixels[i][j].setBlue(inFile.get());
    	}
    }
    if ((m_iWidth*m_iHeight) != (m_arrCPixels.size()*m_arrCPixels[0].size()))	{
        std::cout<<"PixelCount= "<<((m_iNumChannels*m_iWidth)*m_iHeight)<<" and mPixel.size= "<<m_arrCPixels.size()<<"x"<<m_arrCPixels[0].size()<<std::endl;
        std::cout<<"Can't allocate image of size "<<m_iWidth<<"x"<<m_iHeight<<". Exiting\n"<<std::endl;
        exit (1);
    }

}

void cImage::writeToPPMFile(string filename)	{
	std::ofstream output;
    output.open (filename);
    output<<"P6\n";
    output<<"#This is file is created by gbhutra\n";
    output<<m_iWidth<<" "<<m_iHeight<<"\n";
    output<<"255\n";
    for (int i=0;i<m_iHeight;++i)	{
    	for (int j=0;j<m_iWidth;++j)	{
    		output<<static_cast<unsigned char>(m_arrCPixels[i][j].getRed());
    		output<<static_cast<unsigned char>(m_arrCPixels[i][j].getGreen());
    		output<<static_cast<unsigned char>(m_arrCPixels[i][j].getBlue());
    	}
    }
    output.close();
}

cPixel cImage::getPixelAtXY(int x,int y)    {
    return m_arrCPixels[x][y];
}
void cImage::setPixelAtXY(int x, int y, RGB col)    {
    m_arrCPixels[x][y].setRed(get<0>(col));
    m_arrCPixels[x][y].setGreen(get<1>(col));
    m_arrCPixels[x][y].setBlue(get<2>(col));
}

void cImage::setPixelAtXY(int x, int y, cPixel p)    {
    m_arrCPixels[x][y] = p;
}

void imgToArray(cImage& img, char* ptr)    {
    int iterator =0;
    for (int i=0;i<img.m_iHeight;++i)	{
        for (int j=0;j<img.m_iWidth;++j)	{
            ptr[iterator++]=img.m_arrCPixels[i][j].getRed();
            ptr[iterator++]=img.m_arrCPixels[i][j].getGreen();
            ptr[iterator++]=img.m_arrCPixels[i][j].getBlue();
        }
    }
};

