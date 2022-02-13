/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/08/22 00:01:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <cmath> //atan
#include <string> // stof
#include "rotation.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argcv[])
{
	float pi = atan(1)*4;
	Mat fprint(imread(argcv[1], 0));

	float x = stof(argcv[2]);
	float y = stof(argcv[3]);
	float angle = stof(argcv[4]);

	Mat rotated = image_rotation(Point_<float>(x, y), 
			angle*2*pi,
			fprint);

	imshow("To compare :3", fprint);
	imshow("hey !", rotated);
	waitKey(0);

	return 0;
}
