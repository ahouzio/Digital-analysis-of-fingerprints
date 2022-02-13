#include "img.h"
#include "utils.h"



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

img img::rectangle(Point p,int w,int h,int colour){

    Mat res;
    M.copyTo(res);
    for (int i = p.x; i < p.x + w; ++i) {
		for (int j = p.y; j < p.y + h; ++j) {
            res.at<uchar>(j,i) = colour;
        }
    }
    return img(res);
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

img img::sym_x(){
    Mat padded;
    padded.create(height, width, M.type());
    padded.setTo(cv::Scalar::all(255));

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			padded.data[(height - j -1)*width + i] = M.data[j*width+i];
		}
	}
    return img(padded);
}

img img::sym_y(){
    Mat padded;
    padded.create(height, width, M.type());
    padded.setTo(cv::Scalar::all(255));
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			padded.data[(j*width + width - i - 1)] = M.data[j*width+i];
		}
	}
    return img(padded);
}

img img::sym_diag() {
    
    Mat padded;
    int m = max(width,height);
    padded.create(m, m, M.type());
    padded.setTo(cv::Scalar::all(255));
    M.copyTo(padded(Rect(0, 0, M.cols, M.rows)));

	for (int i = 0; i < m; ++i) {
		for (int j = i; j < m; ++j) {
			swap(padded.data[i*m + j], padded.data[j*m + i]);
		}
	}
    return img(padded(Rect(0,0,width,height)));
}

Point img::spot(){
    int sum = 0;
    Point center;
    vector <Point> candidate_spots;
    int patch_size = 9;
    int min_sum = 255*pow(patch_size,2);
    for (int i = patch_size; i < width - patch_size; ++i) {
		for (int j = patch_size; j < height- patch_size; ++j) {
            sum = 0;
            for (int m = i-(patch_size/2);m <= i + patch_size/2;++m){
                for (int n = j-(patch_size/2) ;n <= j +(patch_size/2);++n){
                    sum += M.data[m + n*width];  
                }
            }
            if (sum < min_sum ){
                center = Point(i,j);
                min_sum = sum;
            }
        }
    }
    Mat res;
    M.copyTo(res);
    int i = center.x;
    int j = center.y;
    for (int m = i-(patch_size/2);m <= i + patch_size/2;++m){
        for (int n = j-(patch_size/2) ;n <= j +(patch_size/2);++n){
			res.at<uchar>(n,m) = 255;
		}
	}

    return center;
}

img img::apply_coeff(int x_max, int y_max, FUNCTION_TYPE coeff, double angle, float a,double n,bool rand){
    angle = angle * PI / 180.0;
    double d;
    Point center = this->spot();
    int center_x = center.x;
    int center_y = center.y;
    x_max /= 2;
    y_max /= 2;
    float xradius = (float)max(width-center_x,center_x)/x_max;
    float yradius = (float)max(height-center_y,center_y)/y_max;
    Mat res;
    Mat res2;
    M.copyTo(res2);
    M.copyTo(res);
    for(int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            // Isotropic   
            // d = sqrt(pow((i-center_x),2) + pow((j - center_y),2));
            // Inosotropic
            d = sqrt( pow((float)(j - center_y)* cos(angle) + (float)(i - center_x)*sin(angle),2)/(xradius * xradius) 
                + pow((float)(j - center_y)* sin(angle) - (float)(i - center_x)*cos(angle),2)/(yradius * yradius) );
            res.at<uchar>(j,i) = 255 - coefficients(coeff,a,d , n)*(255 - res.at<uchar>(j,i));
        }
    }  
    return img(res);
}
double img::coefficients(FUNCTION_TYPE fct,double epsilon,double d,double n){
    if (fct == GAUSSIAN){
        return exp(-pow(epsilon*d,2));
    }
    else if (fct == INVERSE){
        return (1/(pow(2*d,2*n) + 1));
    }
    // n controls how flat the curve is and a controls where it reaches 0
    else if (fct == BEST_FUNCTION){
        if (d <= epsilon){
            return 1-pow(d/epsilon,n);
        }
        else{
            return 0;
        }
    }
}

