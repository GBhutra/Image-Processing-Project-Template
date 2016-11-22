//
//  main.cpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include <iostream>
//#include "manipulation.hpp"
#include "dithering.hpp"
#include "filters.hpp"
//#include "2dShapes.hpp"
#include "glFunctions.hpp"
//#include "compositing.hpp"
//#include "transforms.hpp"
#include "cImage.hpp"
#include <map>

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


int main(int argc, char* argv[])	{
    /*map<string,string> g_mapOptions={{"-output",""}, {"-input",""}, {"-dither",""}};
    int numOpts = argc;
    while(numOpts-->0)	{
        auto option = g_mapOptions.find(string(argv[numOpts]));
        if(option!=g_mapOptions.end())
            g_mapOptions[string(argv[numOpts])]=string(argv[numOpts+1]);
    }*/
    MATRIX::mat m4 {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    cout << "Determinant :"<<MATRIX::det(m4)<<endl;
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(canvas.getWidth(), canvas.getHeight());
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project 8");
    init();
    glutReshapeFunc(windowResize);
    glutDisplayFunc(windowDisplay);
    glutMouseFunc(processMouse);
    glutKeyboardFunc(processKeyBoard);
    glutMainLoop();

    return 0;
}
