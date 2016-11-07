//
//  utility.hpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/23/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef utility_h
#define utility_h

//constants
const double PI = acos(-1);
const double RAD = PI/180;
const double numSubPixels = 3;

#define MOD(x) ((x)<0?(-(x)):(x))
#define POS(x) ((x)<0?(0):(x))
#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))


/*Debugging Definitions*/
#define DBG_LVL 3

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
