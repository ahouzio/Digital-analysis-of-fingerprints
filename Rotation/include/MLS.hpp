/*
 * =====================================================================================
 *
 *       Filename:  MLS.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/12/22 14:54:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

///parent class for a Moving Least Square deformation
/**
 * The MLS works thusly : we specify a certain square grid that we
 * superpose with the image then apply the MLS algorithm on this
 * grid. We then use a bilinear interpolation to get the value of each
 * pixel.
 * Note : to help with interpolation, the grid goes beyond the
 * img frame. If a point has no value it will be given 255 (white).
 * In the following, \f$n\f$ will be the number of control points
 * and \f$m\f$ will be the total number of vertices in the grid.
 */
class MLS {
	protected:
		/// the image we wish to use MLS on.
		Mat_<uchar> img;

		/// A vector containing the n control points.
		std::vector<Point2f> ctrl_pts;
		/// An attribute containing the number of control points.
		unsigned int nbr_cpts;

		/// grid info. 
		unsigned int grid_spacing, grid_cols, grid_rows;
		unsigned int nbr_grid_pts;

		/// A matrix containing the least square weights.
		/** The Matrix is nxm. Each line has the precalculated value
		 * for each vertice of the grid.
		 */
		Mat_<float> weights;
		/// useful points for calculations
		/**
		 * one is needed for each vertices in the grid. So m elements
		 */
		std::vector<Point2f> weighted_fixed;

		Mat diff_fixed; 

		/// Matrix containing pre-computed data
		/** The Matrix is nxm. Each line has the precalculated value
		 * for each vertice of the grid.
		 */
		Mat_<float> A;
	public:
		///basic constructor
		/** \param img the image to be deformed
		 * \param grid the grid spacing
		 * \param c the control points, 2xn matrix
		 */
		MLS(Mat &img,unsigned int grid, std::vector<Point2f> &c);
		virtual Mat update(Mat moved_points) = 0;
};

/// Class for an MLS affine deformation
class MLS_affine : public MLS {
	
	public:
	MLS_affine(Mat &i,unsigned int grid, Mat &c);
	Mat update(Mat moved_points);

};
/// Class for an MLS similarity deformation
class MLS_similarity : public MLS {
	
	public:
	MLS_similarity(Mat &i,unsigned int grid, Mat &c);
	Mat update(Mat moved_points);

};
/// Class for an MLS rigid deformation
class MLS_rigid : public MLS {
	
	public:
	MLS_rigid(Mat &i,unsigned int grid, Mat &c);
	Mat update(Mat moved_points);

};
