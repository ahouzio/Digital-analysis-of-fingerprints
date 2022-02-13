#pragma once
#ifndef loss3_h
#define loss3_h
#include "img3.h"

/**
 * @brief 
 * 
 * @param objective The image that we want to reach after alignment
 * @param src The image we want to align
 * @param data_path The path of text file where translation parameter tx and loss function values are stored
 * @param loss_function The adress of the loss function to use
 * @return float The optimal translation parameter with respect to x-axis
 */
float loss_translation_x(img objective,img src,string data_path,float (*loss_function)(Mat,Mat) );
/**
 * @brief Caclulates the loss function for different translation parameters (tx,ty).
 * 
 * @param objective The image that we want to reach after alignment
 * @param src The image we want to align
 * @param data_path The path of text file where translation parameters tx and ty and loss function values are stored
 * @param loss_function The adress of the loss function to use
 * @return tuple<float,float> The optimal translation parameters with respect to x and y axis
 */
tuple<float,float> loss_translation_xy(img objective,img src,string data_path,float (*loss_function)(Mat,Mat));
/**
 * @brief Calculates the loss function for several rotation parameter values
 * 
 * @param objective The image that we want to reach after alignment
 * @param src The image we want to align
 * @param data_path The path of text file where rotation parameter and loss function values are stored
 * @param loss_function The adress of the loss function to use
 * @return float 
 */
float loss_rot(img objective,img src,string data_path,float (*loss_function)(Mat,Mat));
/**
 * @brief 
 * 
 * @param M 
 * @param N 
 * @return float 
 */
float loss_fct_1(Mat M,Mat N);
/**
 * @brief 
 * 
 * @param M 
 * @param N 
 * @return float 
 */
float loss_fct_2(Mat M,Mat N);
/**
 * @brief 
 * 
 * @param p_x 
 * @param p_y 
 * @param src 
 * @return Mat 
 */
Mat translate_xy(float p_x,float p_y,img src);
/**
 * @brief 
 * 
 * @param angle 
 * @param src 
 * @return Mat 
 */
Mat rotation(float angle,img src);
/**
 * @brief 
 * 
 * @param objective 
 * @param src 
 * @param optimal_tx 
 * @param optimal_ty 
 * @param optimal_angle 
 * @return img 
 */
img pixel_diff(img objective,img src,float optimal_tx,float optimal_ty,float optimal_angle);
/**
 * @brief 
 * 
 * @param objective : 
 * @param src : 
 * @param p0 :
 * @param data_path : 
 * @param loss_function :
 */
void gradient_descent(img objective,img src,float p0,string data_path,float (*loss_function)(Mat,Mat));
/**
 * @brief Calculate the mean of the pixek intensities of an image
 * 
 * @param M : image
 * @return mean 
 */
float mean(Mat M);


#endif