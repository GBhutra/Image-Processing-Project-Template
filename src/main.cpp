//
//  main.cpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include <cstdlib>
#include <iostream>
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
#include "2dShapes.hpp"
#include "glFunctions.h"


using namespace std;

int main(int argc, char* argv[])	{
    //cImage img("/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/guitar.ppm");
    //img.writeToPPMFile("/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/guitar2.ppm");
    //cImage cont("/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/test3.ppm");
    //canvas = cImage(img.getWidth(),img.getHeight());
    //localFilter::motionBlur(img, canvas, cont);
    //canvas.readPPMFile("/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/cube.pbm");
    RGB white{255,255,255};
    canvas = cImage(400,300,{0,0,0});
    vector2D p1(10,10);
    vector2D p2(100,100);
    drawLineSegment(p1, p2, canvas, white);
    //canvas.writeToPPMFile("/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/aa.pbm");
    //line(p2, p1, canvas, white);
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0); // Where the window will display on-screen.
    glutInitWindowSize(canvas.getWidth(), canvas.getHeight());
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project");
    init();
    glutReshapeFunc(windowResize);
    glutDisplayFunc(windowDisplay);
    glutMouseFunc(processMouse);
    glutKeyboardFunc(processKeyBoard);
    glutMainLoop();
    
    return 0;
}
