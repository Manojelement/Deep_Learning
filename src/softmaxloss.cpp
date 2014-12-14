/*
 * softmaxloss.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: manoj
 */

#include <opencv/highgui.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <softmaxloss.h>
#include<opencv/cv.h>
using namespace std;
using namespace cv;

double softmaxloss(Mat prob, int type)
{

 double maxVal=0;
 minMaxLoc(prob, 0, &maxVal);
 subtract(prob, maxVal, prob);
 exp(prob,prob);
 Scalar total = sum(prob);
 return log(total[0]) ;  
 
}

