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
    vector<vector2D> vertices{{200,175},{300,175},{350,300},{250,350},{150,300}};
    //convexPolygon convex(vertices);
    RGB backGroundCol{170,120,150};
    RGB ShapeCol{30,20,50};
    canvas = cImage(500,500,backGroundCol);
    star poly(vertices);
    drawPolygon(poly, canvas, ShapeCol);
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
