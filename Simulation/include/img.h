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
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "stdio.h"
#include "utils.h"
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

/**
 * @brief determine the center of the spot of a fingerprint where the intensity of the black pixels is the highest
 * 
 * @return Center of the spot 
 */
Point spot();

/**
 * @brief Types of radial functions that start at 1 in point 0 and converge towards 0.
 * 
 * @param fct : Radial function starts at 1 and decrease to 0, used for pixel intenisty decrease around the center of a fingerprint.
 * @param epsilon : parameter to tune the functions
 * @param d : 
 * @param n : 
 * @return double 
 */
double coefficients(FUNCTION_TYPE fct,double epsilon,double d,double n);

/**
 * @brief 
 * 
 * @param xRadius 
 * @param yRadius 
 * @param coeffType 
 * @param angle 
 * @param epsilon 
 * @param n 
 * @param rand 
 * @return img 
 */
img apply_coeff(int xRadius, int yRadius, FUNCTION_TYPE coeffType, double angle, float epsilon,double n,bool rand);

/**
 * @brief Function to collect a number of random squares of the same size called patches.
 *
 * @param patch_size : The size of the patch
 * @param patch_number : the number of patches to collect
 * @param register : boolean to tell whether or not we want to save the patches somewhere
 * @param path : if register is true saves the patches to the path specified here.
 * @return a vector of the patches that were created
 */
vector<Mat> collect(int patch_size,int patch_number,bool register,string path);

/**
 * @brief 
 * 
 * @param erosion_type 
 * @param erosion_size 
 * @return img 
 */
img ero(int erosion_type,int erosion_size);

/**
 * @brief 
 * 
 * @param erosion_type 
 * @param erosion_size 
 * @return img 
 */
img dil(int erosion_type,int erosion_size);

/**
 * @brief 
 * 
 * @param max 
 * @return img 
 */
img threshold(int max);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @return Mat 
 */
Mat rectangle_mask(int x,int y,int w,int h);

/**
 * @brief 
 * 
 * @param patch_size 
 * @param size 
 * @return Mat 
 */
Mat ring_mask(int patch_size,int size);

/**
 * @brief 
 * 
 * @param contours 
 * @param patch_size 
 * @param C_p 
 * @param msk 
 * @return Point 
 */
Point priority_pixel_2(vector <vector<Point>> &contours,int patch_size,Mat &C_p,Mat &msk);

/**
 * @brief 
 * 
 * @param vect 
 * @param msk 
 * @param patch_size 
 * @return Point 
 */
Point priority_pixel_1(vector<Point> vect,Mat &msk,int patch_size);

/** 
 * @brief complete the image with the patches we have using the inpainting algorithm
 *
 * @param im : image to complete
 * @param patch_size : size of our patches
 * @param patch_number : number of patches
 */
void complete_1(img source,int patch_size,int patch_number,Mat &mask);

/** 
 * @brief complete the image with the patches we have using the inpainting algorithm
 *
 * @param im : image to complete
 * @param patch_size : size of our patches
 * @param patch_number : number of patches
 */
void complete_2(img source,int patch_size,int patch_number,Mat &mask);
};

/**
 * @brief 
 * 
 * @param res 
 * @param patch_size 
 */
void clean(Mat res,int patch_size);

/**
 * @brief 
 * 
 * @param patches 
 */
void show_patches(vector<Mat> patches);

/**
 * @brief 
 * 
 * @param M 
 * @param patch_size 
 * @param x 
 * @param y 
 * @return Point2f 
 */
Point2f compute_max_grad(Mat &M,int patch_size,int x,int y);

/**
 * @brief Return the closest patch from our collection to the patch M using the fisrt euclidian norm so it's the closest patch in terms of pixel intensity.
 *
 * @param M Our patch
 * @param v The collection of the patches that will be used to complete the image.
 * @return patch with the minimal distance.
 */

Mat compute_min_patch(Mat M,vector<Mat> v,int patch_size,Mat &mask,int m,int n);

/**
 * @brief 
 * 
 * @param patch 
 * @return int 
 */
int count(Mat patch);

#endif
