/*
 * =====================================================================================
 *
 *       Filename:  warp.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/09/22 17:49:39
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
#include "rotation.hpp"

using namespace cv;

/// rotation is applied following a matrix
/* Each pixel has an angle value found in the matrix angle. */
Mat image_rotation_warp(Point_<float> o, Mat &angle, Mat &img)
{
	int ncol(img.cols), nrow(img.rows);
	Mat rotated(nrow, ncol, CV_8UC1);
	uchar *p = rotated.ptr<uchar>(0,0);

	for(int i=0; i < ncol*nrow; i++)
	{
		int x = i % ncol;
		int y = (i - x) / ncol;
		*p = pixel_rotation(Point(x,y), o, angle.at<float>(y, x), img);
		p++;
	}

	return rotated;
}

/// linear interpolation
/*
 * \param f1,f2	known function values, f1 is before f2
 * \param d 	grid-spacing
 * \param dx	distance of the interpolated point from the smallest grid
 *
 * \return 	interpolated value
 */
float lin_interpolation(float f1, float f2, float d,float dx)
{
	return (f2 - f1)/d * dx + f1;
}

/// bilinear interpolation
/* Does a bilinear interpolation by repeated linear interpolation
 * \param UL, UR, BL, BR	values of the upper-left (UL), bottom-left (BL), etc...
 * \param d					grid-spacing
 * \param dp				difference of the interpolated point with UL
 *
 * \return interpolated values
 */
float bilin_interpolation(float UL, float UR,float BL, float BR, float d, Point_<float> dp)
{
	float val1(lin_interpolation(UL, UR, d, dp.x)), val2(lin_interpolation(BL, BR, d, dp.x));

	return lin_interpolation(val1, val2, d, dp.y);
}

//======================== Least squares deformation ====================================

