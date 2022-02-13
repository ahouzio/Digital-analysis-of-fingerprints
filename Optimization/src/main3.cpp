
#include "loss3.h"

int main() {

    clock_t start, end;
	start = clock();
	// Loading the image
    string path1 = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Input/weak_finger.png";
	string path2 = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Input/clean_finger.png";
	string path3 = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Input/tx_finger.png";
	string path4 = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Input/txy_finger.png";
	string path5 = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Input/rtxy_finger.png";
    img weak = img(path1);
	img clean = img(path2);
	img translated_x = img(path3);
	img translated_xy = img(path4);
	img rotated_xy = img(path5);

	// Image optimization starter

	// Squared mean error loss function 
	float optimal_tx_1 = loss_translation_x(translated_x,clean,"C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Optimization/Output/loss_x.txt",&loss_fct_1);
	cout << "optimal tx is : " << optimal_tx_1 << endl;

	// Second error loss function 
	tuple<float,float> optimal = loss_translation_xy(translated_xy,clean,"C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Optimization/Output/loss_xy.txt",&loss_fct_2);
	cout << "optimal tx and ty is : " << get<0>(optimal) << " "<< get<1>(optimal) << endl;

	// Error 
	img error = pixel_diff(translated_xy,clean,get<0>(optimal),get<1>(optimal),0);
	error.display("error image");

	Mat g = translate_xy(get<0>(optimal),get<1>(optimal),clean);
    img(g).display("translated");
	float optimal_angle = loss_rot(rotated_xy,img(g),"C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Optimization/Output/loss_rotation.txt",&loss_fct_2);
    g = rotation(optimal_angle,img(g));
    img(g).display("rotated and translated");

	// Error 
	error = pixel_diff(rotated_xy,img(g),get<0>(optimal),get<1>(optimal),optimal_angle);
	error.display("error image");

	// Display the optimal parameters
	cout << "optimal angle : " << optimal_angle << endl;
	cout << "optimal tx is : " << optimal_tx_1 << endl;
	

	// Gradient Descent
	gradient_descent(translated_x,clean,-25,"C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Optimization/Output/gradient_descent.txt",&loss_fct_2);
	end = clock();
	cout << "time is : " << (float) (end - start)/CLOCKS_PER_SEC;
	return 0;
}