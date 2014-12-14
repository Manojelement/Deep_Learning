/*
 * cnntrain.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: manoj
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<training_data_read.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <convolution_layer.h>
#include <pooling_layer.h>
#include <norm_layer.h>
#include <softmax.h>
#include <relu_layer.h>
#include <softmaxloss.h>
#include <softmaxloss_bp.h>
#include <convolution_layer_bp.h>
#include <pooling_layer_bp.h>
#include <norm_layer_bp.h>
using namespace std;
using namespace cv;
#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(int argc, char **argv) {

	char * normalize_image_data = "data/normalize.bin";
	Mat normalize(227, 227, CV_64FC3);
	read_normalize(normalize_image_data, normalize, 227, 227, 3);

	//cout << normalize.at<Vec<double, 3> >(199,49)(0);
	conv_layers layer1, layer5, layer9, layer11, layer13, layer16, layer18, layer20;
	pool_layers layer3, layer7, layer15;
	norm_layers layer4, layer8;
	read_conv_layer("data/conv_1.bin", &layer1);
	read_conv_layer("data/conv_5.bin", &layer5);
	read_conv_layer("data/conv_9.bin", &layer9);
	read_conv_layer("data/conv_11.bin", &layer11);
	read_conv_layer("data/conv_13.bin", &layer13);
	read_conv_layer("data/conv_16.bin", &layer16);
	read_conv_layer("data/conv_18.bin", &layer18);
	read_conv_layer("data/conv_20.bin", &layer20);

	//Read pooling layers
	read_pool_layer("data/pool_3.bin", &layer3);
	read_pool_layer("data/pool_7.bin", &layer7);
	read_pool_layer("data/pool_15.bin", &layer15);

	//Read pooling layers
	read_norm_layer("data/normalize_4.bin", &layer4);
	read_norm_layer("data/normalize_8.bin", &layer8);

	Mat x1(227, 227, CV_64FC3);
	read_normalize("data/cat.bin", x1, 227, 227, 3);
	subtract(x1, normalize, x1);
	vector<Mat> x;
 	split(x1, x);
        
	//cout << x[0]; 		
	double t = (double)getTickCount();
	//Conv
	//printf("\nConv\n");
	 vector<Mat> x2 = CNN_FP(x, layer1.filters, layer1.baises, layer1.stride, layer1.pad);

	//relu
	//printf("\nrelu\n");
	 vector<Mat> x3 = relu(x2);
	
	//pool
	//printf("\npool\n");
	 vector<Mat> x4 = max_pooler(x3, layer3.pad, layer3.stride, layer3.pool);

	//norm	
	//printf("\nnorm\n");
	
	vector<Mat> x5 = norm(x4, layer4.param);
        
	//conv 
	//printf("\nConv\n");
        vector<Mat> x6 =  CNN_FP(x5, layer5.filters, layer5.baises, layer5.stride, layer5.pad);
	
	//relu
	//printf("\nrelu\n");
        vector<Mat> x7 =  relu(x6);
	
	//pool
	//printf("\npool\n");
	vector<Mat> x8 = max_pooler(x7, layer7.pad, layer7.stride, layer7.pool);
	
	//norm
	//printf("\nnorm\n");
	vector<Mat> x9 = norm(x8,layer8.param);
	
	//printf("\nConv\n");
	vector<Mat> x10 =  CNN_FP(x9, layer9.filters, layer9.baises, layer9.stride, layer9.pad);

	//printf("\nrelu\n");
	vector<Mat> x11 = relu(x10);

	//printf("\nConv\n");
	vector<Mat> x12 =  CNN_FP(x11, layer11.filters, layer11.baises, layer11.stride, layer11.pad);

	//printf("\nrelu\n");
	vector<Mat> x13 = relu(x12);

 	//printf("\nConv\n");
	vector<Mat> x14 =  CNN_FP(x13, layer13.filters, layer13.baises, layer13.stride, layer13.pad);

	//printf("\nrelu\n");
	vector<Mat> x15 = relu(x14);

	//printf("\npool\n");
	vector<Mat> x16 = max_pooler(x15, layer15.pad, layer15.stride, layer15.pool);
		
	//printf("\nConv\n");	
	vector<Mat> x17 = CNN_FP(x16, layer16.filters, layer16.baises, layer16.stride, layer16.pad);

	//printf("\nrelu\n");
	vector<Mat> x18 = relu(x17);

	//printf("\nConv\n");
	vector<Mat> x19 = CNN_FP(x18, layer18.filters, layer18.baises, layer18.stride, layer18.pad);

	//printf("\nrelu\n");
	vector<Mat> x20 = relu(x19);

	//printf("\nConv\n");
	vector<Mat> x21 = CNN_FP(x20, layer20.filters, layer20.baises, layer20.stride, layer20.pad);
		
	 	
	/*Mat prob = Mat::zeros(1, x21.size(), CV_64FC1);
	for(int i = 0; i < x21.size(); i++)
	   prob.at<double>(0,i) = x21[i].at<double>(0,0);

	double loss = softmaxloss(prob, 282);
	t = ((double)getTickCount() - t);*/

	//printf("\nbp: softmax loss\n");
	vector<Mat> x21_dzdx = softmaxloss_bp(x21, 281, (float)1);

//	printf("\nbp: Conv\n");
	vector<Mat> x20_dzdx = CNN_BP(x20, layer20.filters, x21_dzdx, layer20.baises, layer20.stride, layer20.pad);
	
	//for(int i = 0; i < x20_dzdx.size(); i++)
	 //cout << x20_dzdx[i];

	//printf("\nbp: relu\n");	
	vector<Mat> x19_dzdx = relu_bp(x20_dzdx, x19);

	//printf("\nbp: Conv\n");
	vector<Mat> x18_dzdx = CNN_BP(x18, layer18.filters, x19_dzdx, layer18.baises, layer18.stride, layer18.pad);


	//printf("\nbp: relu\n");
	vector<Mat> x17_dzdx = relu_bp(x18_dzdx, x17);

	//printf("\nbp: conv\n");
	vector<Mat> x16_dzdx = CNN_BP(x16, layer16.filters, x17_dzdx, layer16.baises, layer16.stride, layer16.pad);

	//printf("\nbp: pool\n");
	vector<Mat> x15_dzdx = max_pooler_bp(x15, x16_dzdx, layer15.pad, layer15.stride, layer15.pool);
	
	//printf("\nbp: relu\n");	
	vector<Mat> x14_dzdx = relu_bp(x15_dzdx, x14);

	//printf("\nbp: Conv\n");
	vector<Mat> x13_dzdx =  CNN_BP(x13, layer13.filters, x14_dzdx, layer13.baises, layer13.stride, layer13.pad);

	//printf("\nbp: Relu\n");
	vector<Mat> x12_dzdx = relu_bp(x13_dzdx, x12);


	//printf("\nbp: Conv\n");
	vector<Mat> x11_dzdx =  CNN_BP(x11, layer11.filters, x12_dzdx, layer11.baises, layer11.stride, layer11.pad);

	//printf("\nbp: Relu\n");
	vector<Mat> x10_dzdx = relu_bp(x11_dzdx, x10);	

	//printf("\nbp: Conv\n");
	vector<Mat> x9_dzdx =  CNN_BP(x9, layer9.filters, x10_dzdx, layer9.baises, layer9.stride, layer9.pad);

	//printf("\nbp: norm\n");
	vector<Mat> x8_dzdx = norm_bp(x8, layer8.param, x9_dzdx);	

	//pool
	//printf("\nbp: pool\n");
	vector<Mat> x7_dzdx = max_pooler_bp(x7, x8_dzdx, layer7.pad, layer7.stride, layer7.pool);
	
	//relu
	//printf("\nbp: relu\n");
        vector<Mat> x6_dzdx =  relu_bp(x7_dzdx, x6);

	//conv 
	//printf("\nbp: Conv\n");
        vector<Mat> x5_dzdx =  CNN_BP(x5, layer5.filters, x6_dzdx, layer5.baises, layer5.stride, layer5.pad);	
	
	//norm	
	//printf("\nbp: norm\n");
	vector<Mat> x4_dzdx = norm_bp(x4, layer4.param, x5_dzdx);

	//pool
	//printf("\nbp: pool\n");
	 vector<Mat> x3_dzdx = max_pooler_bp(x3, x4_dzdx, layer3.pad, layer3.stride, layer3.pool);

        //relu
	//printf("\nbp: relu\n");
	 vector<Mat> x2_dzdx = relu_bp(x3_dzdx, x2);
	
	//Conv
	//printf("\nbp: Conv\n");
	 vector<Mat> x1_dzdx = CNN_BP(x, layer1.filters, x2_dzdx, layer1.baises, layer1.stride, layer1.pad);
	

	//for(int i = 0; i < x1_dzdx.size(); i++)
	  // cout << x1_dzdx[i];
 	
	t = ((double)getTickCount() - t);
	cout << "\n timetaken="<< t/getTickFrequency();	
	//cout << "\n"<<x1_dzdx.size() << " "<<x1_dzdx[0].rows <<" "<< x1_dzdx[0].cols;
		
	//for(int i = 0; i < x1_dzdx.size(); i++)
	  cout << x2_dzdx[10];
	//cout << "\n" << loss;	        
	/*double maxVal=0;
	Point max_loc;
	minMaxLoc(prob, 0, &maxVal, 0, &max_loc);
        cout << "\n maxval"<<maxVal << " index " << max_loc.x;	
	*/
	cout << "\nfinished\n";

}
			
