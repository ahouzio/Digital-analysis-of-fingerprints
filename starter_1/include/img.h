#pragma once
#ifndef img_h
#define img_h
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>
#include "stdio.h"
using namespace cv;
using namespace std;

#define PI 3.14159265

 /*! \class img
* \brief class representing an image
*
*  This class is for image manipulation.
 */
class img{
    private :
Mat M; /* Matrix of pixel values of a greyscale image*/
int height; /*Height of the image */
int width; /*Width of the image */
string pathname; /*Path to the image location */
    public :
    /*!
*  \brief Constructor
*
*  Img class constructor
*
*  \param pathname : Path of the image
*/
img(string pathname);

    /*!
*  \brief Constructor
*
*  Img class constructor
*
*  \param A :  Matrix of the image
*/
img(Mat A);

    /*!
*  \brief Copy constructor
*
*  Copies an img class attributes
*
*  \param to_copy : image to copy
*/
img(const img &to_copy);

    /*!
*  \brief Shows an image
*
*  Display an image in a window and keeps it open.
*
*  \param window_name : Window's name
*/
void display(string window_name);

    /*!
*  \brief Prints out matrix pixel intensities.
*
*
*  \param o : output stream.
*/
void print(ostream &o);

    /*!
*  \brief Saves an image in a given location
*
*
*  \param path : path of the saved image
*/
void save(string path);

    /*!
*  \brief computes the minimum pixel intensity.
*/
int minimum();

    /*!
*  \brief computes the maximal pixel intensity
*/
int maximum();

    /*!
*  \brief getter of the height attribute
*/
int get_height();

    /*!
*  \brief getter of width attribute
*/
int get_width();

    /*!
*  \brief getter of the matrix of the image
*/
Mat get_matrix();

    /*!
*  \brief cast pixel intensity values of the image to float type
*/
 void cast_float();

/**
 * @brief drawws a rectangle with a greyscale pixel intensity.
 *
 * @param p : Top left point of the rectangle
 * @param w : The width of the rectangle
 * @param h : The height of the rectangle
 * @param colour : The pixel intensity between 0 and 255.
 * @return img : the image with rectangle drawn on it.
 */
img rectangle(Point p,int w,int h,int colour);

/**
 * @brief Creates the symmmetrized image with respect to the x-axis
 *
 * @return symmetried immage
 */
img sym_x();

/**
 * @brief Creates the symmmetrized image with respect to the y-axis
 *
 * @return symmetried immage
 */
img sym_y();

/**
 * @brief Creates the symmmetrized image with respect to the diagonal axis
 *
 * @return symmetried immage
 */
img sym_diag();
};
#endif