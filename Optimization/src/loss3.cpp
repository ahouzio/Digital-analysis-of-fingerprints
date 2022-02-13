#include "loss3.h"
#include <fstream>

float loss_translation_x(img objective,img src,string data_path,float (*loss_function)(Mat,Mat)){
    ofstream file;
    file.open(data_path);
    file << "tx" << "," << "loss" << endl;

    Mat source = src.get_matrix();
    int d = 1;
    if (loss_function == &loss_fct_2){
        d = -1;
    }
    float extremum_loss = d* pow(2,32);
    float loss = 0;
    float optimal_tx = 0; 
    int nbr_of_points  = 100;
    float a = -50;
    float b = 50;
    // Choosing a discrete step for translation
    int step = (b-a)/(nbr_of_points);
    int tx = a;
    for (int i= 0;i < nbr_of_points;++i){
        Mat g = translate_xy(tx,0,src);                        
        // img(dst).display("s");
        loss = loss_function(g,objective.get_matrix());
        if (d*loss <= d*extremum_loss ){
            extremum_loss = loss;
            optimal_tx = tx;
        }
        file << tx << "," << loss << endl;
        tx += step;
        
    }
    file.close();
    return optimal_tx;
}

tuple<float,float> loss_translation_xy(img objective,img src,string data_path,float (*loss_function)(Mat,Mat) ){
    ofstream file;
    file.open(data_path);
    Mat source = src.get_matrix();
    int d = 1;
    if (loss_function == &loss_fct_2){
        d = -1;
    }
    float extremum_loss = d * pow(2,32);
    float loss = 0;
    float optimal_tx = 0;
    float optimal_ty = 0;
    
    int nbr_of_points  = 90;
    float a = (float)-30;
    float b = (float)30;
    // Choosing a discrete step for translation
    float step = (float)(b-a)/(nbr_of_points);
    float tx = a;
    float ty;
    for (int i= 0;i < nbr_of_points;++i){
        tx += step;
        ty = a;
        for (int j= 0;j < nbr_of_points;++j){
            ty += step;
            // create the translated image 
            Mat g = translate_xy(tx,ty,src);                             
            loss = loss_function(g,objective.get_matrix());
            if (d * loss <= d * extremum_loss ){
                extremum_loss = loss;
                optimal_tx = tx;
                optimal_ty = ty;
            }
            file << tx << " " << ty << " " << loss << " \n";
        }
    }
    file.close();
    return make_tuple(optimal_tx,optimal_ty);
}

float loss_rot(img objective,img src,string data_path,float (*loss_function)(Mat,Mat)){
    // open the file and name the colons
    ofstream file;
    file.open(data_path);
    file << "r" << "," << "loss" << endl;
    Mat source = src.get_matrix();
    int d = 1;
    if (loss_function == &loss_fct_2){
        d = -1;
    }
    float extremum_loss = d * pow(2,32);
    float loss = 0;
    float optimal_angle = 0;

    int nbr_of_points  = 200;
    float a = (float)-4;
    float b = (float)4;
    // Choosing a discrete step for translation
    float step = (float)(b-a)/(nbr_of_points);
    float angle = a;
    for (int i= 0;i < nbr_of_points;++i){
        Mat g = rotation(angle,src);              
        // img(dst).display("s");
        loss = loss_function(g,objective.get_matrix());
        if (d * loss <= d * extremum_loss ){
            extremum_loss = loss;
            optimal_angle = angle;
        }
        file << angle << "," << loss << " \n";
        angle += step;
    }

    file.close();
    return optimal_angle;
}

// Loss function as the mean squared error between two images
float loss_fct_1(Mat M,Mat N){
    
    float error = 0;
    int width = M.cols;
    int height = M.rows;
    for (int i = 0; i < width;++i){
        for (int j = 0;j < height;++j){
            error += pow(M.at<uchar>(j, i) - N.at<uchar>(j, i),2);
        }
    }
    return error;
}

// Second version of the loss function
float loss_fct_2(Mat D,Mat S){
    
    float error = 0;
    float mean_f = mean(S);
    float mean_g = mean(D);
    float norm_f = 0;
    float norm_g = 0;
    float product_fg = 0;
    int width = S.cols;
    int height = S.rows;
    for (int i = 0; i < width;++i){
        for (int j = 0;j < height;++j){
            norm_f += pow(S.at<uchar>(j, i) - mean_f,2);
            norm_g += pow(D.at<uchar>(j, i) - mean_g,2);
            
            product_fg += (S.at<uchar>(j, i) - mean_f) * (D.at<uchar>(j, i) - mean_g);
            
        }
    }
    
    error = product_fg/(sqrt(norm_f) * sqrt(norm_g));

    return error;
}

Mat translate_xy(float p_x,float p_y,img src){
    Mat g;
    Mat source = src.get_matrix();
    // Translation matrix
    float x[6] = {1,0,p_x,0,1,p_y};
    Mat M(2, 3, CV_32FC1, x);
    // Apply a translation along the x and y axis to the starting image,we also remove the black background
    Mat S = 255 - source;
    warpAffine(S, g, M, Size(src.get_width(), src.get_height()), INTER_CUBIC, BORDER_CONSTANT);
    g = 255 - g;
    return g;
}

Mat rotation(float angle,img src){
    Mat g;
    Mat source = src.get_matrix();
    // Rotation matrix
    Point center = Point( src.get_width()/2, src.get_height()/2 );
    double scale = 1;
    Mat rot_mat = getRotationMatrix2D( center, angle, scale );
    // Apply a rotation on the starting image S and save the rotated image in g,we also remove the black background
    Mat S = 255 - source;
    warpAffine(S, g, rot_mat, Size(src.get_width(), src.get_height()), INTER_CUBIC, BORDER_CONSTANT);
    g = 255 - g;  
    return g;
}

img pixel_diff(img objective,img src,float optimal_tx,float optimal_ty,float optimal_angle){
    
    int width = src.get_width();
    int height = src.get_height();
    Mat obj = objective.get_matrix();
    Mat g;
    Mat source = src.get_matrix();
    Mat error;
    error.create(height,width,CV_8UC1);
    // Apply a translation along the x and y axis and a rotation to the starting image
    g = rotation(optimal_angle,src);
    g = translate_xy(optimal_tx,optimal_ty,img(g));
    // Calculating the absolute error between the transformed image and the original
    for (int i = 0; i < width;++i){
        for (int j = 0;j < height;++j){
            error.at<uchar>(j,i) = abs(obj.at<uchar>(j,i) - g.at<uchar>(j,i));
        }
    }
    return img(error);
}

float mean(Mat M){
    float mean = 0;
    int width = M.cols;
    int height = M.rows;
    for (int i = 0; i < width;++i){
        for (int j = 0;j < height;++j){
            mean += M.at<uchar>(j, i);
        }
    }
    mean = (float)mean/(width*height);
    return mean;
}

void gradient_descent(img objective,img src,float p0,string data_path,float (*loss_function)(Mat,Mat)){
    ofstream file;
    file.open(data_path);
    file << "tx" << "," << "loss" << endl;
    Mat obj = objective.get_matrix();
    int d = 1;
    if (loss_function == loss_fct_2){
        d = -1;
    }
    float alpha_p = 0.3;
    int iterations = 20;
    float loss = loss_function(translate_xy(p0,0,src),obj);
    float up_loss;
    float down_loss;
    for (int i = 0;i<iterations;++i){
        // Calculate the translated matrix by our new parameters    
        down_loss = loss_fct_2(translate_xy(p0*(1-alpha_p),0,src),obj);
        up_loss = loss_fct_2(translate_xy(p0*(1+alpha_p),0,src),obj);
        if (d* down_loss <= d* loss || d*up_loss <= d*loss){
            if (d * up_loss < d * down_loss){
                loss = up_loss;
                p0 = p0*(1+alpha_p);   
            }
            else{
                loss = down_loss;
                p0 = p0*(1-alpha_p);      
            }
            alpha_p = alpha_p*1.1;
        }
        else{
            alpha_p = alpha_p/2;         
        }
        file << p0 << "," << loss << endl;
    }
}