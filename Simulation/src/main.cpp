#include "img.h"

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

	
	// Simulation

	img modif = clean.apply_coeff(100,60,INVERSE,88,30,0.1,false);
	modif.display("funct");
	modif.save("C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/iso_best.png");
	
	modif = clean.apply_coeff(100,60,BEST_FUNCTION,89,30,100,true);
	modif.display("funct");
	modif.save("C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/inoso_best.png");

	modif = clean.apply_coeff(120,60,GAUSSIAN,88,0.05,100,true);
	modif.display("gauss");
	modif.save("C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Output/noisy.png");
	
	end = clock();
	cout << "time is : " << (float) (end - start)/CLOCKS_PER_SEC;
	return 0;
}