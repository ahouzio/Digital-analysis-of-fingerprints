#include "img.h"

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