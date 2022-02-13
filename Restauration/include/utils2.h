#pragma once
#ifndef utils2_h
#define utils2_h

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
 * @param a lower bound of the interval
 * @param b upper bound of the interval
 * @return random nmuber between a and b 
 */
int randrange(int a ,int b);


#endif