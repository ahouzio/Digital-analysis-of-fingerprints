#include "img2.h"

int main() {

	clock_t start, end;
	start = clock();
	// Loading the images
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

	// Restauration using rectangular mask
	
	// img modified = weak;
	// Mat mask = modified.rectangle_mask(50,100,30,30);
	// modified.complete_1(weak,9,2000,mask);	
	// modified.display("square mask");
	
	// Restauration using a ring mask with the first function

	int patch_size = 9;
	int patch_number = 2000;
	img weak_2 = weak;
	img msk = weak.ring_mask(patch_size,20); // 231s for this
	// weak.complete_1(weak,patch_size,patch_number,msk.get_matrix()); 
	// weak.display("result");
	
	// Restauration using a ring mask and the inpainting algorithm

	msk = weak_2.ring_mask(patch_size,35); // 440s for this
	weak_2.complete_2(weak,patch_size,patch_number,msk.get_matrix());
	weak_2.display("ring mask");
	weak_2.save("C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Restauration/Output/restaured_4_2.png");
	
	end = clock();
	cout << "time is : " << (float) (end - start)/CLOCKS_PER_SEC;
	return 0;
}