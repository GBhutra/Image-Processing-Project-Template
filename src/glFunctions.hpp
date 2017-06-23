//
//  glFunctions.cpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/23/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "cImage.hpp"
#include "stich-carving.hpp"
#include <vector>

cImage canvas;
std::vector<cImage> frames;
int frameIndex=0;

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRasterPos2i(0,0);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glDrawPixels(canvas.getWidth(), canvas.getHeight(), GL_RGB, GL_UNSIGNED_BYTE,arr);
    glFlush();
    glutSwapBuffers();
}
// Mouse click call back
static void processMouse(int button, int state, int x, int y) {
    if(state == GLUT_UP)
        exit(0);               // Exit on mouse click.
}
// Keyboard press callback
void processKeyBoard(unsigned char key, int x, int y)	/* called on key press */	{
    std::cout<<"Keyboard Key pressed : "<<key<<std::endl;
    if ('f'==key)   {
        if (frameIndex==frames.size())
            frameIndex = 0;
        canvas = frames[frameIndex];
        frameIndex++;
    }
    if ('b'==key)   {
        if (0==frameIndex)
            frameIndex = frames.size()-1;
        canvas = frames[frameIndex];
        frameIndex--;
    }
    glutPostRedisplay();
}
