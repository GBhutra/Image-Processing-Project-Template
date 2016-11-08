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
#include "transforms.hpp"
using namespace std;

namespace COLORS {
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

void project7(int argc, char* argv[]) {
    
}

void project2(int argc, char* argv[]) {
    double w = 640,h=480;
    canvas = cImage(w,h,COLORS::YELLOW);
    vector<vector2D> quad{{256, 20},{420, 128},{375, 420},{128, 375},{100, 160}};
    vector<vector2D> pent{{200,200},{320,160},{420,200},{390,300},{260,300}};
    vector<circle> circ{circle({w/4,4*h/5},60),
                      circle({w/2,h/3},150),
                      circle({3*w/4,3*h/5},100)};
    vector2D center{320,240};
    vector2D centerShade{400,300};
    bool antiAlias = false;
    
    convex poly = convex(quad);
    blob b = blob(circ);
    star st = star(pent);
    circle cir = circle(center, 200);
    circle sha = circle(centerShade, 120);
    func fu = func();
    
    
    string op="";
    
    if (2>argc) {
        std::cout<<"Usage : ./pr02 <option> <anti aliasing> -output"<<std::endl;
        std::cout<<"Options : convex(co), star, function, blobby, shaded"<<std::endl;
        std::cout<<"anti aliasing : true or false. deafult=false"<<std::endl;
        std::cout<<"The options could be used using the first two letters for example st for star"<<std::endl;
        exit(0);
    }
    
    if (2<argc)
        if("true"==string(argv[2]))
            antiAlias = true;
    
    if(4<=argc)
        if ("-output"==string(argv[3]))
            op = string(argv[4]);
    
    string option(argv[1]);
    if ("co"==option || "convex"==option)   {
        drawShape(poly, canvas, COLORS::RED, antiAlias);
    }
    else if("star"==option || "st"==option)   {
        drawShape(st, canvas, COLORS::BLUE, antiAlias);
    }
    else if("fu"==option || "function"==option)   {
        drawShape(fu, canvas, COLORS::ORANGE, antiAlias);
    }
    else if("blobby"==option || "bl"==option)   {
        drawShape(b, canvas, COLORS::GREEN);
    }
    else if("sh"==option || "shaded"==option)   {
        canvas = cImage(640,480,COLORS::RED, COLORS::ORANGE);
        drawShape(cir, canvas, COLORS::VIOLET,antiAlias);
        drawCircularShade(sha, canvas, COLORS::WHITE);
    }
    else{
        std::cout<<"Unrecognized option : "<<option<<std::endl;
        std::cout<<"Usage : ./pr02 <option> <anti aliasing>"<<std::endl;
        std::cout<<"Options : convex(co), star, function, blobby, shaded"<<std::endl;
        std::cout<<"anti aliasing : true or false. deafult=false"<<std::endl;
        std::cout<<"The options could be used using the first two letters for example st for star"<<std::endl;
        exit(0);
    }
    if (""!=op)
        canvas.writeToPPMFile(op);
}

int main(int argc, char* argv[])	{
    cImage inp("/Users/Ghanshyam/Documents/MS Courses/CSCE 646 Digital Image processing/ProjectTemplate/test/test3.pbm");
    canvas = cImage(inp.getWidth(),inp.getHeight(),COLORS::BLACK);
    mat tm = rotationMat(60);
    //mat m{{1,0,50},{0,1,60},{0,0,1}};
    inverseTransform(inp,canvas,tm);
    //bilinear(inp,canvas);
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0); // Where the window will display on-screen.
    glutInitWindowSize(canvas.getWidth(), canvas.getHeight());
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project 2");
    init();
    glutReshapeFunc(windowResize);
    glutDisplayFunc(windowDisplay);
    glutMouseFunc(processMouse);
    glutKeyboardFunc(processKeyBoard);
    glutMainLoop();
    return 0;
}
