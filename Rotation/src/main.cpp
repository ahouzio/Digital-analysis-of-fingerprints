/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/09/22 23:13:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "warp.hpp"


using namespace cv;
int main(int argc, char* argv[])
{
	Mat fprint(imread(argv[1],0)), angle(fprint.rows, fprint.cols, CV_32FC1);

	// linear progression
//	for(int y=0; y<angle.rows; y++)
//	{
//		float *p = angle.ptr<float>(y);
//		int x;
//		for(x=0; x<angle.cols; x++)
//		{
//			*p = atof(argv[2])*y*2*3.14 / angle.rows;
//			p++;
//		}
//	}

	// square progression
	for(int y=0; y<angle.rows; y++)
	{
		float *p = angle.ptr<float>(y);
		int x;
		for(x=0; x<angle.cols; x++)
		{
			*p = atof(argv[2])*y*y*2*3.14 / (angle.rows*angle.rows);
			p++;
		}
	}
	Mat warped = image_warp(Point_<float>(angle.cols/2, angle.rows/2), angle, fprint);

	cv::imshow("Look who's here ?", warped);
	cv::imshow("Look who's there ?", fprint);
	waitKey();

	return 0;
}
