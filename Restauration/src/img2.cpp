#include "img2.h"
#include "utils2.h"



img::img(string p){
    
    Mat A = imread(p,IMREAD_GRAYSCALE);
    M = A;
    height = M.rows;
    width = M.cols;
    pathname = p;

}

img::img(Mat A){
    M = A;
    width = A.cols;
    height = A.rows;
    pathname = "";

}

img::img(const img &to_copy){

    to_copy.M.copyTo(M);
    height = to_copy.height;
    width = to_copy.width;
    pathname = to_copy.pathname;
}

void img::display(string window_name){

    namedWindow(window_name);
	imshow(window_name, M);
	waitKey(0);
}

void img::print(ostream &o){
    
    for (int i = 0; i < width; ++i) {
        o << "[";
		for (int j = 0; j < height; ++j) {
            o << (int)M.data[i + j*width] << " ";
        }
        o << "]" << endl;
    }
}

    
void img::save(String path){
    imwrite(path,M);
}

int img::get_height(){
    return height;
}

int img::get_width(){
    return width;
}

Mat img::get_matrix(){
    return M;
}



int img::minimum(){
    int min = 255;
    for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
            if (M.data[i + j*width] < min){
                min = M.at<uchar>(j,i);
            }
        }
    }
    return min;
}

int img::maximum(){
    int max = 0;
    for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
            if (M.data[i + j*width] > max){
                max = M.at<uchar>(j,i);
            }
        }
    }
    return max;
}

// Patch collection
vector<Mat> img::collect(int patch_size,int patch_number,bool reg,string path){
    int counter = 0;
    Mat patch_mat;
    Mat patch;
    vector<Mat> patches;
    Mat white_patch;
    white_patch.create(9,9,M.type());
    white_patch.setTo(255);
    patches.push_back(white_patch);
    int radius = patch_size/2;
    while (counter < patch_number-1){
        // We take a point from the rectangle surrounding the weak fingerprint
        int randomx = randrange(44 - patch_size, 208 + patch_size);
        int randomy = randrange(62 - patch_size, 278);
        patch = M(Rect(randomx-radius,randomy-radius,patch_size,patch_size));          
        patches.push_back(patch);
        ++counter;
        
    }
    if (reg == true){
        int i = 0;
        for (vector<Mat>::iterator it = patches.begin();it<patches.end();++it){
            string s = path + "/patch" + to_string(i) + ".png";
            imwrite(s,*it);
            i = i+1;
        }
    }
    return patches;
}

img img::dil(int erosion_type,int erosion_size){
    Mat element = getStructuringElement( erosion_type,
                    Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                    Point( erosion_size, erosion_size ) );
    Mat res;
    res.create(height,width,M.type());
    res.setTo(255);
    erode(M,res,element);
    
    return img(res);
    }

img img::ero(int erosion_type,int erosion_size){
    Mat element = getStructuringElement( erosion_type,
                    Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                    Point( erosion_size, erosion_size ) );
    Mat res;
    res.create(height,width,M.type());
    res.setTo(255);
    dilate(M,res,element);
    
    return img(res);
}

img img::threshold(int max){
    Mat patch;
    Mat res;
    M.copyTo(res);
    for (int i = 0;i < width ;++i){
        for (int j = 0; j < height ;++j){
            if (M.at<uchar>(j,i) < max){
                 res.at<uchar>(j,i) = 0;
            }
        }
    }
    return img(res);
}

Mat img::rectangle_mask(int x,int y,int w,int h){
    Mat res;
    res.create(height,width,M.type());
    res.setTo(255);
    for (int i = x;i < x+w;++i){
        for (int j = y; j < y + h;++j){
            res.at<uchar>(j,i) = 0;
            M.at<uchar>(j,i) = 255;
        }
    }
    return res;
}

Mat img::ring_mask(int patch_size,int size){
    vector <vector<Point>> contours;
	Mat B;
    M.copyTo(B);
	B = 255 - B;
	findContours(B, contours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_NONE);
	B = 255 - B;
	drawContours(B,contours,38,0,-1);
    // Cleaning the image borders and making it binary
    clean(B,patch_size);
    img mask = (img(B).threshold(255)).ero(0,2);
    // Doing the same thing for the dilated image
    img dilated = (mask.dil(2,size)).threshold(255);
    // Defining the difference between the dilated image and the mask of our image
    Mat res;
    res.create(height, width, M.type());
    res.setTo(cv::Scalar::all(255));

    // Performing XNOR operation between the two images
    for (int i = 0;i < width;++i){
        for (int j = 0; j < height;++j){
            res.at<uchar>(j,i) = !(mask.get_matrix().at<uchar>(j,i) ^ dilated.get_matrix().at<uchar>(j,i))*255;
        }
    }
    clean(res,patch_size);
    return res;   
}

Point img::priority_pixel_1(vector<Point> vect,int patch_size,Mat &msk){
    int priority;
    int max_priority = pow(2,20);
    Point p;
    Mat patch;
    for (vector<Point>::iterator it = vect.begin();it<vect.end();++it){
        int i = (*it).x;
        int j = (*it).y;
        if (msk.at<uchar>(j,i) == 0){
            patch = M(Rect(i-patch_size/2,j-patch_size/2,patch_size,patch_size));
            int priority = count(patch);
            if (priority < max_priority){
                max_priority = priority;
                p = Point(i,j);
            }
        }
    }
    return p;
}

Point img::priority_pixel_2(vector <vector<Point>> &contours,int patch_size,Mat &C_p,Mat &msk){

    Point high_priority;
    float priority;
    float max_priority = -pow(2,20);
    float slope;
    Point2f normal;
    // We search the inner boundary points with the least points
    int index = 0;
    for (int i = 0; i < contours.size();++i){
        if (contours[i].size() < contours[index].size()){
            index = i;
        }
    }
    int size =  contours[index].size();
    for(int n = 0; n < size; ++n){
        Point p = contours[index][n];
        int i = p.x;
        int j = p.y;
        // Computing confidence term in point p
        float sum = 0;
        for (int k = i-(patch_size/2);k <= i + patch_size/2;++k){
            for (int l = j-(patch_size/2) ;l <= j +(patch_size/2);++l){
                // we take the pixels that are in the source region
                if (msk.at<uchar>(l, k) == 255){
                    sum +=  C_p.at<float>(l,k);
                }
            }
        }
        C_p.at<float>(j,i) = (float)sum / pow(patch_size,2);
        // max gradient of the patch
        Point2f max_grad = compute_max_grad(M,patch_size,i,j);
        float grad_x = max_grad.x;
        float grad_y = max_grad.y;
        // Normal to the boundary on the point p
        Point next_p = contours[index][(n+1+size)%size]; // we add size to avoid negative values<<<<<<
        Point prev_p = contours[index][(n-1 +size)%size ];
        if (next_p.y != prev_p.y){
            slope = (float)(next_p.x - prev_p.x)/(next_p.y - prev_p.y);
            normal = Point2f((float)1/pow(1 + slope*slope,0.5), (float)slope/pow(1 + slope*slope,0.5) );
        }
        else{
            if (next_p.x < prev_p.x){
                normal = Point2f(0, 1);
            }
            else{
                normal = Point2f(0,-1);
            }
        }
        float D_p = (float)abs(grad_x*normal.x + grad_y*normal.y)/255;
        priority =  C_p.at<float>(j,i) * D_p;
        if (priority > max_priority){
            max_priority = priority;
            high_priority = p;
        }
    }
    return high_priority;
}


void img::complete_1(img source,int patch_size,int patch_number,Mat &msk){

    vector<Mat> patches = source.collect(patch_size, patch_number,false,"");
    vector<Point> vect;
    Mat patch;
    for (int i = 0;i < width;++i){
        for (int j = 0; j < height;++j){
            if (msk.at<uchar>(j,i) == 0){
                vect.push_back(Point(i,j));
            }
        }
    }
    int to_process_pixel = count(255 - msk) / 255;
    for (int k = 0;k < to_process_pixel;++k){
        Point p = this->priority_pixel_1(vect,patch_size,msk);
        int i = p.x;
        int j = p.y;
        //Patch around the pixel
        patch = M(Rect(i-patch_size/2,j-patch_size/2,patch_size,patch_size));
        //we will replace the pixels in the patch and update confidence values
        Mat replacement_patch = compute_min_patch(patch,patches,patch_size,msk,i,j);
        M.at<uchar>(j,i) = replacement_patch.at<uchar>(patch_size/2,patch_size/2);
        msk.at<uchar>(j,i) = 255;

        vect.erase(remove(vect.begin(),vect.end(),Point(i,j)),vect.end());
    }
}

void img::complete_2(img source,int patch_size,int patch_number,Mat &msk){

    vector<Mat> patches = source.collect(patch_size, patch_number,false,"");
    vector <vector<Point>> contours;
    vector <Point>priority;
    // C_p initialization;
    Mat C_p;
    msk.convertTo(C_p, CV_32FC1, 1./255.);
   int to_process_pixel = count(255 - msk) / 255;
    for (int k = 0; k < to_process_pixel;++k){
        msk = 255 - msk;
	    findContours(msk, contours, CV_RETR_LIST , CV_CHAIN_APPROX_NONE);
	    msk = 255 - msk;
        Point p = this->priority_pixel_2(contours,patch_size,C_p,msk);
        int i = p.x;
        int j = p.y;
        //Patch around the pixel
        Mat patch = M(Rect(i-patch_size/2,j-patch_size/2,patch_size,patch_size));
        //we will replace the pixels in the patch and update confidence values
        Mat replacement_patch = compute_min_patch(patch,patches,patch_size,msk,i,j);
        M.at<uchar>(j,i) = replacement_patch.at<uchar>(patch_size/2,patch_size/2);
        msk.at<uchar>(j,i) = 255;
        // Updating confidence values
        for (int m = i-(patch_size/2);m <= i + patch_size/2;++m){
            for (int n = j-(patch_size/2) ;n <= j +(patch_size/2);++n){
                if (msk.at<uchar>(n,m) == 0){
                    C_p.at<float>(n,m) = C_p.at<float>(j,i);
                }
            }
        }
    }
}

void show_patches(vector<Mat> patches){
    Mat res;
    int patch_number = patches.size();
    cout << "the patch_size is : " << patch_number << endl;
    int lenght = patches[0].cols;
    cout << "the lenght is : " << lenght << endl;
    int width = sqrt(patch_number)*lenght + sqrt(patch_number) + 4;
    res.create(width,width,CV_8UC1);
    res.setTo(0);
    Mat patch;
    int counter = 0;
    int x = 0;
    int y = 0;
    int i = 0;
    for (vector<Mat>::iterator it = patches.begin();it<patches.end();++it){
        x = counter % width; 
        if (x == 0){
            y = i + (counter / width) * lenght;
            ++i;
        }
        for (int i = x;i<x+lenght;++i){
            for (int j = y;j<y+lenght;++j){
                res.at<uchar>(j,i) = (*it).at<uchar>(j-y,i-x);
            }
        }

        counter += lenght + 1;
    }
    img(res).display("patches");
    string path5 = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/patches.png";
    img(res).save(path5);
}

Point2f compute_max_grad(Mat &M,int patch_size,int x,int y){
    Mat x_kernel;
    Mat y_kernel;
    x_kernel.create(3,3,CV_8SC1);
    y_kernel.create(3,3,CV_8SC1);
    // Kernels initialization
    x_kernel.data[0] = -1;
    x_kernel.data[1] = 0;
    x_kernel.data[2] = 1;
    x_kernel.data[3] = -2;
    x_kernel.data[4] = 0;
    x_kernel.data[5] = 2;
    x_kernel.data[6] = -1;
    x_kernel.data[7] = 0;
    x_kernel.data[8] = 1;
    // y kernel initialization
    for (int i = 0;i<3;++i){
        for (int j = 0;j<3;++j){
            y_kernel.data[i + 3*j] = x_kernel.data[j + 3*i];
        }
    }
    float grad_x;
    float grad_y;
    float magnitude;
    float max_magnitude = 0;
    Point2f max_gradient;
    for (int i = x - patch_size/2; i <= x + patch_size/2; ++i){
        for (int j = y - patch_size/2; j <= y + patch_size/2; ++j){
            Mat pixel_neighbour = M(Rect(i-1,j-1,3,3));
            grad_x = 0;
            grad_y = 0;
            for (int m = 0;m<3;++m){
                for (int n = 0;n<3;++n){
                    grad_x += pixel_neighbour.data[m + 3*n] * x_kernel.at<signed char>(m,n);
                    grad_y += pixel_neighbour.data[m + 3*n] * y_kernel.at<signed char>(m,n);
                } 
            }
            magnitude = pow(grad_x*grad_x + grad_y*grad_y,0.5);
            if (magnitude > max_magnitude){
                max_magnitude = magnitude;
                max_gradient = Point2f(grad_x,grad_y);
            }
        }
    }
    return max_gradient;
}

Mat compute_min_patch(Mat patch,vector<Mat> v,int patch_size,Mat &mask,int m,int n){
    int sum;
    Mat min_patch;
    int min = pow(255*patch_size,2);
    
    for (vector<Mat>::iterator it = v.begin();it<v.end();++it){
        sum = 0;
        for (int i = 0;i < patch_size;++i){
            for (int j = 0;j < patch_size;++j){
                // We only take into consideration the source region pixels
                if (mask.at<uchar>(n-patch_size/2 + j,m-patch_size/2 + i) == 255){
                    sum += pow(patch.at<uchar>(j,i)-(*it).at<uchar>(j,i),2);
                }
            }
        }
        if (sum < min){
            min_patch = *it;
            min = sum;
        }
        
    }
    return min_patch;
}

int count(Mat patch){
    int sum = 0;
    int length = patch.cols;
    for (int i = 0;i<length;++i){
        for (int j = 0;j<length;++j){
            sum += patch.at<uchar>(j,i);
        }
    }
    return sum;
}

void clean(Mat res,int patch_size){
    // Remove some of the details in the corners of the image to avoid having patches outside the borders
    int height = res.rows;
    int width = res.cols;
    int radius = patch_size;
    for (int j = height - radius;j<height;++j){
		for (int i= 0;i<width;++i){
			res.at<uchar>(j,i) = 255;
		}
    }
    for (int j = 0;j<radius;++j){
		for (int i= 0;i<width;++i){
			res.at<uchar>(j,i) = 255;
		}
    }
    for (int i = 0;i<radius;++i){
		for (int j= 0;j<height;++j){
				res.at<uchar>(j,i) = 255;
        }
    }
    for (int i = width-radius;i<width ;++i){
		for (int j= 0;j<height;++j){
			res.at<uchar>(j,i) = 255;
		}
    }
}