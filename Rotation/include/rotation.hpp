/*
 * =====================================================================================
 *
 *       Filename:  rotation.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/08/22 00:01:55
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

Point_<float> rotation(Point_<float> p, Point_<float> o, float angle);
uchar RAMweighted(Point_<float> p, uchar UL, uchar UR, uchar LL, uchar RR);
uchar pixel_rotation(Point_<int> p, Point_<float> o, float angle, Mat &img);
Mat image_rotation(Point_<float> o, float angle, Mat &img);
