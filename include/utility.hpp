//
//  utility.hpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/23/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef utility_h
#define utility_h

#include <iostream>
#include <cmath>

//constants
const double PI = acos(-1);
const double RAD = PI/180;

enum{
    On,
    Left,
    Right,
}typedef PointLocation;

/*Debugging Definitions*/
#define DBG_LVL 3

#define NOR  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define WHT  "\x1B[37m"

#define BOLD "\x1B[1m"
#define UNDL "\x1B[4m"

#if (DBG_LVL==3)
#define DBG_LOG_RED(x) 			DBG_LOG(RED<<x<<NOR)
#define DBG_LOG_RED_BOLD(x) 	DBG_LOG(RED<<BOLD<<x<<NOR)
#define DBG_LOG_GREEN(x)		DBG_LOG(GRN<<x<<NOR)
#define DBG_LOG_GREEN_BOLD(x)	DBG_LOG(GRN<<BOLD<<x<<NOR)
#define DBG_LOG_YELLOW(x)		DBG_LOG(YEL<<x<<NOR)
#define DBG_LOG_YELLOW_BOLD(x)	DBG_LOG(YEL<<BOLD<<x<<NOR)
#define DBG_LOG_BLUE(x)			DBG_LOG(BLU<<x<<NOR)
#define DBG_LOG_BLUE_BOLD(x)	DBG_LOG(BLU<<BOLD<<x<<NOR)
#define DBG_LOG(x) 			std::cout<<"["<< __FUNCTION__<< "()] [Line " << __LINE__ << "] "<<x<<std::endl;
#define DBG_ERROR(x)			DBG_LOG_RED_BOLD(x)
#define DBG_WARN(x)			DBG_LOG_YELLOW_BOLD(x)
#elif (DBG_LVL==2)
#define DBG_LOG(x)
#define DBG_LOG_RED(x)
#define DBG_LOG_RED_BOLD(x)
#define DBG_LOG_GREEN(x)
#define DBG_LOG_GREEN_BOLD(x)
#define DBG_LOG_YELLOW(x)
#define DBG_LOG_YELLOW_BOLD(x)
#define DBG_LOG_BLUE(x)
#define DBG_LOG_BLUE_BOLD(x)
#define DBG_ERROR(x)			std::cout<<"["<< __FUNCTION__<< "()] [Line " << __LINE__ <<"] "<<x<<std::endl;
#define DBG_WARN(x)			DBG_ERROR(x)
#elif (DBG_LVL==1)
#define DBG_LOG(x)
#define DBG_LOG_RED(x)
#define DBG_LOG_RED_BOLD(x)
#define DBG_LOG_GREEN(x)
#define DBG_LOG_GREEN_BOLD(x)
#define DBG_LOG_YELLOW(x)
#define DBG_LOG_YELLOW_BOLD(x)
#define DBG_LOG_BLUE(x)
#define DBG_LOG_BLUE_BOLD(x)
#define DBG_WARN(x)
#define DBG_ERROR(x)			std::cout<<"["<< __FUNCTION__<< "()] [Line " << __LINE__ << "] "<<x<<std::endl;
#else
#define DBG_LOG(x)
#define DBG_LOG_RED(x)
#define DBG_LOG_RED_BOLD(x)
#define DBG_LOG_GREEN(x)
#define DBG_LOG_GREEN_BOLD(x)
#define DBG_LOG_YELLOW(x)
#define DBG_LOG_YELLOW_BOLD(x)
#define DBG_LOG_BLUE(x)
#define DBG_LOG_BLUE_BOLD(x)
#define DBG_WARN(x)
#define DBG_ERROR(x)
#endif
/**/


#endif /* utility_h */
