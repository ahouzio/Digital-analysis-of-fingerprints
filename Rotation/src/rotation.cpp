/*
 * =====================================================================================
 *
 *       Filename:  rotation.cpp
 *
 *    Description: implementation of a rotation algorithm 
 *
 *        Version:  1.0
 *        Created:  01/06/22 21:29:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <opencv2/opencv.hpp>
#include <cmath> // cos

using namespace cv;
using namespace std;

/// Rotation with respect to a point supposing infinitesimal space (no raster)
/**
 * We use the Point_<float> object of opencv. 
 * \param[in] p the point we wish to rotate, 
 * \param[in] o the pole of rotation
 * \param[in] angle the angle of rotation in radian
 *
 * \return a point_<float> opencv object, the rotated point
 */
Point_<float> rotation(Point_<float> p, Point_<float> o, float angle)
{
	// translation to a vector space
	Point_<float> rotated = p - o;
	float x(rotated.x), y(rotated.y);
	//the rotation
	rotated.x = cos(angle)*x - sin(angle)*y;
	rotated.y = sin(angle)*x + cos(angle)*y;

	// back to affine space
	rotated += o;

	return rotated;
}

/// Gets the RAM (raster by area mapping) contrast value.
/** 
 * Gets a floating point in [0,1]² which is fitted into a 16x16
 * subgrid to avoid floating point calculation.
 * Then the calculation is done according to RAM.
 * \param p the normalized point, where the UL pixel is seen as (0,0)
 * \param UL, UR, LL, RR contrast of the neighbor pixels
 * \return the contrast of the given point
 */
uchar RAMweighted(Point_<float> p, uchar UL, uchar UR, uchar LL, uchar RR)
{
	float x(p.x), y(p.y);
	//conversion to the 16x16 grid
	int xgrid, ygrid;
	for(float i=0; i<16; i++)
	{
		if(i/16 <= x < (i+1)/16)
		{
			xgrid = i;
		}

		if(i/16 <= y < (i+1)/16)
		{
			ygrid = i;
		}
	}
	uchar val = ((16-xgrid)*(16-ygrid)*UL +
		xgrid*(16-ygrid)* UR +
		(16-xgrid)*ygrid*LL +
		xgrid*ygrid*RR) / 256;
	
	return val;
}
/// Rotation of pixel using area mapping
/** 
 * Rasterization is achieved by area mapping (RAM). It consists in traslating the 
 * destination pixel to the source (found by inverse rotation) ; the destination
 * pixel's contrast is calculated by the weighted average of the four closest
 * source pixels.
 * If one of the source pixels is not in the frame we give it a 255 (white) value.
 * \param[in] p the pixel we calculate the contrast of
* \param[in] o the pole of rotation (cv::Point_<float>)
* \param[in] angle the angle of rotation in radian
 * \param[in] img a cv::Mat object of the image to rotate
 *
 * \return the contrast of the pixel p
 */
uchar pixel_rotation(Point_<int> p, Point_<float> o, float angle, Mat &img)
{
	//floating point source
	Point_<float> source = rotation(p, o, -angle);
	//source pixel
	Point_<int> sourcePix = source;

	int ncol(img.cols), nrow(img.rows);
	int x(sourcePix.x), y(sourcePix.y);
	uchar UL, UR, LL, RR;
	
	/// if source is off-(or directly on)frame give 255 value
	if( 0 > x || x > ncol - 2 || y < 0 || y > nrow -2 )
		return 255;
	else
	{
		UL = img.at<uchar>(y, x);
		UR = img.at<uchar>(y, x+1);
		LL = img.at<uchar>(y+1, x);
		RR = img.at<uchar>(y+1, x+1);
	}

	return RAMweighted(Point_<float>(source.x - x, source.y - y), UL, UR, LL, RR);
}

/// rotates an image by the given angle.
/**
 * \param[in] o the pole of rotation (cv::Point_<float>)
 * \param[in] angle the angle of rotation in radian
 * \param[in] img a cv::Mat object of the image to rotate
 * \return rotated image
 * */
Mat image_rotation(Point_<float> o, float angle, Mat &img)
{
	int ncol(img.cols), nrow(img.rows);
	Mat rotated(nrow, ncol, CV_8UC1);
	uchar *p = rotated.ptr<uchar>(0,0);

	for(int i=0; i < ncol*nrow; i++)
	{
		int x = i % ncol;
		int y = (i - x) / ncol;
		*p = pixel_rotation(Point(x,y), o, angle, img);
		p++;
	}

	return rotated;
}
