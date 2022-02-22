#include <iostream>
#include <vector>
#include "include/twoSum.h"


void isex(std::vector<int> &num1, std::vector<int> &num2);

int main() {
    std::vector<int> num1, num2;
    num1 = {0,1,1,2};
    num2 = {0,1,1,2,3,5,8};
    isex(num1, num2);


    std::cout << "#########" << std::endl;


    std::vector<int> nums = {1, 2, 3, 6, 10};
    int m_target = 7;
    Solution twosum(nums, m_target);
    twosum.result = twosum.twoSum(twosum);
    std::cout <<twosum.result[0] << std::endl;
    std::cout <<twosum.result[1] ;

    return 0;
}