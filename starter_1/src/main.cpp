#include "img.h"

int main() {

    clock_t start, end;
	start = clock();
	// Loading the image
	string path = "C:/Users/Ahouz/OneDrive/Bureau/Modeling_project/Input/clean_finger.png";
	img clean = img(path);
    clean.display("Clean fingerprint");
    // Rectangle
    img rect = clean.rectangle(Point(50,50),40,100,0);
    rect = rect.rectangle(Point(100,50),100,40,255);
    rect.display("rectangles inside");
    // Symmetries
    img sym_x = clean.sym_x();
    img sym_y = clean.sym_y();
    img sym_diag = clean.sym_diag();
    sym_x.display("x-symmetry");
    sym_y.display("y-symmetry");
    sym_diag.display("diagonal symmetry");
}

