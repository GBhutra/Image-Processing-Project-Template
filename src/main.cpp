//
//  main.cpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include "manipulation.hpp"
#include "dithering.hpp"
#include "filters.hpp"
//#include "2dShapes.hpp"
#include "glFunctions.hpp"
#include "compositing.hpp"
#include "transforms.hpp"
#include "cImage.hpp"
#include "stich-carving.hpp"
#include <map>
#include <fstream>
#include <stack>
#include <string>

namespace COLOR {
    //some common colors
    RGB WHITE{255,255,255};
    RGB BLACK{0,0,0};
    RGB RED{255,0,0};
    RGB BLUE{0,0,255};
    RGB GREEN{0,255,0};
    RGB YELLOW{255,255,0};
    RGB INDIGO{75,0,130};
    RGB VIOLET{238,130,238};
    RGB ORANGE{255,165,0};
}
using namespace std;

void project8(map<string,string>& options)	{
    cImage inputImg;
    
    if (""==options["-input"])	{
        cout<<" No input file provided !!"<<endl;
        exit(0);
    }
    inputImg.readPPMFile(options["-input"]);
    DITHER::toGrayScaleAVG(inputImg, inputImg);
    if(""!=options["-dither"])	{
        if("FS"==options["-dither"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            DITHER::FloydSteinbergMethod(inputImg, canvas);
        }
        else if("ordered"==options["-dither"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            DITHER::Ordered(inputImg, canvas);
        }
        else if("dotDif"==options["-dither"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            DITHER::dotDiffusion(inputImg, canvas);
        }
        else if("HF"==options["-dither"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            DITHER::halfToning(inputImg, canvas);
        }
        else    {
            cout<<"Unsupported Algorithm !!"<<endl;
            cout<<"Dithering algorithms supported :"<<endl;
            cout<<"1. FS"<<endl;
            cout<<"2. ordered"<<endl;
            exit(0);
        }
    }
    else    {
        cout<<"Algorithm needs to be specified !"<<endl;
        cout<<"Dithering algorithm supported :"<<endl;
        cout<<"1. HF : Half Toning Algorithm"<<endl;
        cout<<"1. FS : Floyd-Steinberg Algorithm"<<endl;
        cout<<"2. ordered : using bayer matrix"<<endl;
        cout<<"3. dotDif : using dot diffusion by D.E. Knuth"<<endl;
        exit(0);
    }
    if(""!=options["-output"])	{
        canvas.writeToPPMFile(options["-output"]);
    }
}

int timeConverter(string s) {
    s[0]=' ';
    s[s.length()-1]=' ';
    stringstream iss(s);
    string str;
    stack<double> time;
    while(getline(iss,str,':'))   {
        time.push(stod(str));
    }
    int millsec=0, factor=1;
    while(!time.empty())    {
        millsec+=(time.top()*1000*factor);
        factor*=60;
        time.pop();
    }
    return millsec;
}

int main(int argc, char* argv[])	{
    ifstream input( "/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/samples.csv" );
    string line, time, val1, val2;
    getline(input, line);
    getline(input, line);
    for (int i=0;i<100)
    while(getline(input, line)){
       stringstream iss(line);
        string s;
        if (getline(iss,s,',')) {
            cout<<" Time: "<<timeConverter(s)<<" ";
        }
        if (getline(iss,s,',')) {
            cout<<" voltage: "<<stod(s)*500<<" ";
        }
        cout<<endl;
    }
    /*
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(canvas.getWidth(), canvas.getHeight());
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project 11");
    init();
    glutReshapeFunc(windowResize);
    glutDisplayFunc(windowDisplay);
    glutMouseFunc(processMouse);
    glutKeyboardFunc(processKeyBoard);
    glutMainLoop();
     */
    return 0;
}
