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
#include "glFunctions.cpp"
#include "2dShapes.hpp"

using namespace std;

int main(int argc, char* argv[])	{
    cImage img("/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/test2.pbm");
    canvas = cImage(img.getWidth(),img.getHeight());
    localFilter::gussianBlur(img, canvas, 5);
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
