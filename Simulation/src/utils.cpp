#include "utils.h"




int randrange(int a ,int b)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(a, b); // define the range
    return distr(gen);
    
}



