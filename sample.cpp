#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <array>

int main (){
    int array[5] = {1,2,3,4,5};
    int* ap = array; 

    int i = 4.3;
    i = (i-1 )/2;

    std::cout << i << std::endl;
}