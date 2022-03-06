#include <iostream>
#include <vector>
#include "vector.h"
int main()
{
    vector<int> data;
    data.pushBack(2);

    data.pushBack(3);
    data.pushBack(4);
    data.pushBack(44);
    //range based loop
    for(size_t i = 0; i < data.Size(); i++){
        std::cout << data[i] << std::endl;
    }
    std::cout << "-------------" << std::endl;
}
