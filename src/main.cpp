//
//  main.cpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <fstream>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "manipulation.hpp"
#include "filters.hpp"

using namespace std;
cImage canvas;
map<string,string> g_mapOptions={{"-output",""}, {"-input",""}, {"-filter",""}, {"-kernel",""}, {"-kernelSize",""}};

void processOptions()	{
    cImage inputImg;
    cImage controlImg;
    int kSize=0;
    
    if (""==g_mapOptions["-input"])	{
        cout<<" No input file provided !!"<<endl;
        exit(0);
    }
    inputImg.readPPMFile(g_mapOptions["-input"]);
    if (""!=g_mapOptions["-control"])	{
        controlImg.readPPMFile(g_mapOptions["-control"]);
        if (controlImg.getHeight() < inputImg.getHeight() || controlImg.getWidth() < inputImg.getWidth())	{
            controlImg = inputImg;
            cout<<"control image is smaller than the input image hence not using !"<<endl;
        }
    }else{
        controlImg = inputImg;
    }
    
    if (""!=g_mapOptions["-kernelSize"])	{
        kSize = stoi(g_mapOptions["-kernelSize"]);
    }
    
    if(""!=g_mapOptions["-filter"])	{
        if("gaussianBlur"==g_mapOptions["-filter"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            if (0==kSize)   {
                cout<<" Please specify kernel size not equal to 0 "<<endl;
                exit(0);
            }
            localFilter::gussianBlur(inputImg, canvas, kSize);
        }
        else if("boxBlur"==g_mapOptions["-filter"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            if (0==kSize)   {
                cout<<" Please specify kernel size not equal to 0 "<<endl;
                exit(0);
            }
            localFilter::boxBlur(inputImg, canvas, kSize);
        }
        else if("radialBlur"==g_mapOptions["-filter"]) {
        }
        else if("derivativeFilter"==g_mapOptions["-filter"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            if (0==kSize)   {
                cout<<" Please specify kernel size not equal to 0 "<<endl;
                exit(0);
            }
            localFilter::derivativeFilter(inputImg, canvas, kSize);
        }
        else if("erosionFilter"==g_mapOptions["-filter"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            if (0==kSize)   {
                cout<<" Please specify kernel size not equal to 0 "<<endl;
                exit(0);
            }
            localFilter::erosionFilter(inputImg, canvas, kSize);
        }
        else if("dilationFilter"==g_mapOptions["-filter"]) {
            canvas = cImage(inputImg.getWidth(),inputImg.getHeight());
            if (0==kSize)   {
                cout<<" Please specify kernel size not equal to 0 "<<endl;
                exit(0);
            }
            localFilter::dilationFilter(inputImg, canvas, kSize);
        }
        else    {
            cout<<"Unsupported Filter !!"<<endl;
            exit(0);
        }
    }
    else    {
        cout<<"Filter needs to be specified !"<<endl;
        cout<<"Filters supported :"<<endl;
        cout<<"1. boxBlur"<<endl;
        cout<<"2. gaussianBlur"<<endl;
        cout<<"3. derivativeFilter"<<endl;
        cout<<"4. erosionFilter"<<endl;
        cout<<"5. dilationFilter"<<endl;
        exit(0);
    }
    if(""!=g_mapOptions["-output"])	{
        canvas.writeToPPMFile(g_mapOptions["-output"]);
    }
}

/////// Do Not Edit Functions
static void init(void)  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //Set Background Color
}
static void windowResize(int w, int h)  {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(w/2),0,(h/2),0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
static void windowDisplay(void)	{
    char *arr = new char[canvas.getWidth()*canvas.getHeight()*3];
    imgToArray(canvas,arr);
    int w = canvas.getWidth();
    int h = canvas.getHeight();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRasterPos2i(0,0);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE,arr);
    glFlush();
    glutSwapBuffers();
}
////////////////////////////////////

// Mouse click call back
static void processMouse(int button, int state, int x, int y) {
    if(state == GLUT_UP)
        exit(0);               // Exit on mouse click.
}
////////////////////////
// Keyboard press callback
void processKeyBoard(unsigned char key, int x, int y)	/* called on key press */	{
    std::cout<<"Keyboard Key pressed : "<<key<<std::endl;
    glutPostRedisplay();
}
////////////////////////

int main(int argc, char* argv[])	{
    int numOpts = argc;
    while(numOpts-->0)	{
        if(string(argv[numOpts])=="-hist")	{
            g_mapOptions["-hist"]="true";
        }
        else if (string(argv[numOpts])=="-")	{
            int nPoints = argc-1;
            string points="";
            while(nPoints>numOpts)  {
                points+=string(argv[nPoints--]);
                points+=",";
            }
            g_mapOptions["-curve"]=points;
            cout<<points<<endl;
        }
        else	{
            auto option = g_mapOptions.find(string(argv[numOpts]));
            if(option!=g_mapOptions.end())
                g_mapOptions[string(argv[numOpts])]=string(argv[numOpts+1]);
        }
    }
    processOptions();
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0); // Where the window will display on-screen.
    glutInitWindowSize(canvas.getWidth(), canvas.getHeight());
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project 04");
    init();
    glutReshapeFunc(windowResize);
    glutDisplayFunc(windowDisplay);
    glutMouseFunc(processMouse);
    glutKeyboardFunc(processKeyBoard);
    
    glutMainLoop();
    
    return 0;
}
