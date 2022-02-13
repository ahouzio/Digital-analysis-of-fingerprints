/*
 * =====================================================================================
 *
 *       Filename:  MLS.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/13/22 15:36:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <vector>
#include <cmath> // pow

#include "MLS.hpp"


using namespace cv;
//======================== MLS Class ==============================

MLS::MLS(Mat &i, unsigned int grid, std::vector<Point2f> &c) :
	img(i),
	
	ctrl_pts(c),
	nbr_cpts(ctrl_pts.size()),

	grid_spacing(grid),
	/// The grid goes beyond the img frame to help with interpolation
	grid_cols(img.cols/grid_spacing + grid_spacing),
	grid_rows(img.rows/grid_spacing + grid_spacing),
	nbr_grid_pts(grid_rows*grid_cols),

	// We initiate the size but not the value
	weights(nbr_cpts, nbr_grid_pts),
	diff_fixed(nbr_cpts, nbr_grid_pts, CV_16FC2),
	A(nbr_cpts, nbr_grid_pts)
{
	//============= weights calculation ============================
//	float *p;
//	p = weights.ptr<float>(0,0);
//	int j, pt;
//	for(j=0; j < nbr_cpts; j++)
//	{
//		for(pt=0; pt < nbr_grid_pts; pt++)
//		{
//			int x(pt % grid_cols);
//			int y( (pt - x) % grid_rows);
//
//			*p = std::pow(std::abs( std::pow(x - 
//		}

	// Calculation of the weights
	typedef float Pixel;
	int x,y;
	weights.forEach<Pixel>(
			[&](Pixel &pixel, const int * position) -> void 
			{
				// There might be a big problem with those definitions. See with testing. Will probably have to invert it.
				x = position[0];
				y = position[1];

				pixel = std::pow(
						std::pow( x*grid_spacing - ctrl_pts[y].x,2)+
						std::pow( y*grid_spacing - ctrl_pts[y].y,2),
						// alpha. To change later
						-1.1);
			}
			);

	//Calculation of the weighted centroid
	int it_cp, it_vert;
	for(it_vert=0; it_vert < nbr_grid_pts; it_vert++)
	{
		weighted_fixed.push_back(Point2f(0,0));
		//weighted sum of the control points
		for(it_cp = 0; it_cp < nbr_cpts; it_cp++)
		{
			weighted_fixed[it_vert] += 
				ctrl_pts[it_cp]*weights.at<float>(it_cp, it_vert);
		}
		weighted_fixed[it_vert] /= 
			cv::sum( weights.colRange(it_vert, it_vert+1) )[0];
	}
	
	//Calculation of the diff ctrl_i - weighted
	
	diff_fixed.forEach<Point2f>(
			[&](Point2f pixel, const int * position) -> void
			{
				// There might be a big problem with those definitions. See with testing. Will probably have to invert it.
				x = position[0];
				y = position[1];

				pixel = ctrl_pts[x] - weighted_fixed[y];
			}
			);
}


//======================= MLS_affine Class ========================

MLS_affine::MLS_affine(Mat &i, unsigned int grid, Mat &c) : MLS(i, grid, c)
{
	///weighted centroids calculations
	float pstar;

	//might be more effective with an iterator but we'll see
	int cp, j;
	for(cp = 0; cp < A.rows; cp++)
	{
		for(j = 0; j < A.cols; j++)
		{

		}
	}
}
