#include "histogram.hpp"

void cHistogram::genHistogram(cImage& img)    {
    for (int i=0;i<img.getHeight();++i) {
        for (int j=0;j<img.getWidth();++j) {
            cPixel p = img.getPixelAtXY(i,j);
            m_iArrRed[p.getRed()]++;
            m_iArrGreen[p.getGreen()]++;
            m_iArrBlue[p.getBlue()]++;
        }
    }
}

cImage cHistogram::drawHist()   {
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
};
