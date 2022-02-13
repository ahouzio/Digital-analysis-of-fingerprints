#pragma once
#ifndef utils_h
#define utils_h

#include <iostream>
#include <random>

using namespace std;
enum FUNCTION_TYPE{
    GAUSSIAN = 0,
    INVERSE  = 1,
    BEST_FUNCTION = 2
};
/**
 * @brief returns a random number between a and b according to the uniform distribution
 * 
 * @param a 
 * @param b 
 * @return random nmuber between a and b 
 */
int randrange(int a ,int b);


#endif