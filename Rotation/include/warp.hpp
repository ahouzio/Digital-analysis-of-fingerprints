/*
 * =====================================================================================
 *
 *       Filename:  warp.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/09/22 23:17:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Basile Dubois Bonnaire (), bdbonnaires@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <opencv2/opencv.hpp>

using namespace cv;

Mat image_warp(Point_<float> o, Mat &angle, Mat &img);
