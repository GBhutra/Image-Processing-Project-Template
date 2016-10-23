#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <vector>
#include "image.hpp"
#include "pixel.hpp"
#include "vector2d.hpp"

using namespace std;

class cHistogram {
private:
    vector<int> m_iArrRed;
    vector<int> m_iArrGreen;
    vector<int> m_iArrBlue;
    cImage pixels;
public:
    cHistogram() : m_iArrRed(vector<int>(256,0)),m_iArrBlue(vector<int>(256,0)),m_iArrGreen(vector<int>(256,0)),pixels(512,300) {};
    cHistogram(cImage& img, RGB bg=make_tuple(150,150,150)): m_iArrRed(vector<int>(256,0)),m_iArrBlue(vector<int>(256,0)),m_iArrGreen(vector<int>(256,0)),pixels(512,300,bg) {   genHistogram(img);  };
    void genHistogram(cImage& img);
    cImage drawHist();
};

#endif
