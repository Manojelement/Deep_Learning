/*
 * norm_layer.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: manoj
 */
#include <opencv/highgui.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <norm_layer.h>
using namespace std;
using namespace cv;

vector<Mat> norm(vector<Mat> input, vector<double> param)
{

	vector<Mat> ret;
	int rows = input[0].rows;
	int cols = input[0].cols;
	int channels = input.size();
	int depth = param[0];
	double k = param[1];
	double alpha = param[2];
	double beta = param[3];
	int tap = depth - (depth-1)/2;

	for(int ch = 0; ch < channels; ch++)
        {		
	  Mat norm(rows, cols, CV_64FC1);		
	  for(int row = 0; row < rows; row++)
	  {
		for(int col = 0; col < cols; col++)
		{
			double s = 0;
			for(int d = 0; d < depth; d++)
			{
				int idx = ch - tap + d + 1;
				if(idx >= 0 && idx < channels)
					s = s + pow(input[idx].at<double>(row,col), 2);
			}
			norm.at<double>(row,col) = input[ch].at<double>(row,col)/(pow((k + alpha*s),beta));
		}
	  }
	  
	  ret.push_back(norm);
	}

	return ret;

}



