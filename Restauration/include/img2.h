#pragma once
#ifndef img2_h
#define img2_h

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
#include "utils2.h"
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

/**
 * @brief Function to collect a number of random squares of the same size called patches.
 *
 * @param patch_size : The size of the patch
 * @param patch_number : the number of patches to collect
 * @param register : boolean to tell whether or not we want to save the patches somewhere
 * @param path : if register is true saves the patches to the path specified here.
 * @return a vector of the patches that were created
 */
vector<Mat> collect(int patch_size,int patch_number,bool reg,string path);

/**
 * @brief Erodes the image making it look smaller
 * 
 * @param erosion_type types of the kernel used (rectangular,elliptical or cross shaped)
 * @param erosion_size the size of the kernel matrix
 * @return eroded image 
 */

img ero(int erosion_type,int erosion_size);

/**
 * @brief Dilates an image making it look bigger
 * 
 * @param erosion_type types of the kernel used (rectangular,elliptical or cross shaped)
 * @param erosion_size the size of the kernel matrix
 * @return dilated image
 */
img dil(int erosion_type,int erosion_size);

/**
 * @brief Makes the image binary according to a threshold 
 * 
 * @param max threshold for that each pixel intensity inferior to it is 0 and 255 if it's greater
 * @return img 
 */
img threshold(int max);

/**
 * @brief Creates a rectangular mask for the image
 * 
 * @param x abscissa of the top left point of the rectangle
 * @param y ordinate of the top left point of the rectangle
 * @param w the width of the rectangle
 * @param h height of the image rectangle
 * @return Binary image of the rectangular mask
 */
Mat rectangle_mask(int x,int y,int w,int h);

/**
 * @brief Creates a ring shaped mask around the fingerprint image
 * 
 * @param patch_size size of the patch used to 
 * @param size controls the size of the ring created
 * @return Binary image of the ring shaped mask 
 */
Mat ring_mask(int patch_size,int size);

/**
 * @brief determines the point for which the restauration will start according to the amount of information(sum of pixel intensities of the original image) surrounding it
 * 
 * @param vect vector containing the points of the mask
 * @param patch_size size of a patch
 * @return Point with highest priority
 */
Point priority_pixel_1(vector<Point> vect,int patch_size,Mat &msk);

/**
 * @brief determines the point for which the restauration will start according to the confidence matrix C_p and data values(parameters defined in the inpainting algorithm)
 * 
 * @param contours contours of the mask
 * @param patch_size size of a patch
 * @param C_p matrix of confidence values that depends on the amount of pixels that are already filled and around the pixel
 * @return Point with highest priority 
 */
Point priority_pixel_2(vector <vector<Point>> &contours,int patch_size,Mat &C_p,Mat &msk);

/** 
 * @brief complete the image with the patches we have using the first prority function.
 *
 * @param im : image to complete
 * @param patch_size : size of patch
 * @param patch_number : number of patches
 */
void complete_1(img source,int patch_size,int patch_number,Mat &mask);

/** 
 * @brief complete the image with the patches we have using the inpainting algorithm.
 *
 * @param im : image to complete
 * @param patch_size : size of our patches
 * @param patch_number : number of patches
 */
void complete_2(img source,int patch_size,int patch_number,Mat &mask);
};

/**
 * @brief show patches(rectangle of pixels) inside a window separated by black lines
 * 
 * @param patches patches to stick together
 */
void show_patches(vector<Mat> patches);

/**
 * @brief Computes point in patch with maximum gradient magnitude using the x and y sobel kernels.
 * 
 * @param M image
 * @param patch_size size of the patch
 * @param x abscissa of the top left point of the point
 * @param y ordinate of the top left point of the point
 * @return pointof the maximum gradient magnitude 
 */
Point2f compute_max_grad(Mat &M,int patch_size,int x,int y);

/**
 * @brief Return the closest patch from our collection to the patch M using the fisrt euclidian norm so it's the closest patch in terms of pixel intensity.
 *
 * @param M Our patch
 * @param v The collection of the patches that will be used to complete the image.
 * @return patch with the minimal distance to patch M.
 */
Mat compute_min_patch(Mat M,vector<Mat> v,int patch_size,Mat &mask,int m,int n);

/**
 * @brief Computes the sum of all pixels intensities of an image
 * 
 * @param patch image
 * @return sum of intensities 
 */

int count(Mat patch);

/**
 * @brief removes the corners of the window(turns them in white pixels)
 * 
 * @param res image
 * @param patch_size size of the image frame
 */
void clean(Mat res,int patch_size);


#endif
