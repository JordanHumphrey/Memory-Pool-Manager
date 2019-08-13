#include "Allocator.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    std::vector<unsigned int,Allocator<unsigned int,256>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(2);
    
    for(auto i:vec)
    {
        std::cout << i << " ";
    }
    return 0;
}
