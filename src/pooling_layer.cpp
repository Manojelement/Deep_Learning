/*
 * pooling_layer.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: manoj
 */

#include <opencv/highgui.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pooling_layer.h>
using namespace std;
using namespace cv;

vector<Mat> max_pooler(vector<Mat> input, vector<double>pad, vector<double>stride, vector<double> window)
{
  //Mat ret(input.rows/stride, input.cols/stride, CV_64FC(input.channels()));
  vector<Mat> ret;

  //vector<Mat> ret_split;
  //split(ret, ret_split);
  //Mat max_mat(ret.rows, ret.cols, CV_64FC1);
  int rows = (input[0].rows - (int)window[0] + (int)pad[0] + (int)pad[1])/(int)stride[0]+1;
  int cols = (input[0].cols - (int)window[1] + (int)pad[2] + (int)pad[3])/(int)stride[1]+1;
  int channels = input.size();
 
  for(int k = 0; k < channels; k++)
  {
    Mat max_mat(rows, cols, CV_64FC1);
   for(int i = 0; i < rows; i++)
   {
	  for(int j = 0; j < cols; j++)
	  {
		  int r = (int)stride[0] * i;
		  int c = (int)stride[1] * j;
		  Mat patch = input[k](Range(r,r + (int)window[0]), Range(c,c + (int)window[1]));
		  //cout << patch;
		  double maxVal;
		  minMaxLoc(patch, 0, &maxVal);
		  max_mat.at<double>(i,j) = maxVal;
	}
   }
   ret.push_back(max_mat);   

 }
  return ret;
}

