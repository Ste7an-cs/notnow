//
// Created by Ste7an on 2022/2/22.
//

#ifndef INC_4_5_TWOSUM_H
#define INC_4_5_TWOSUM_H
#include <iostream>
#include <map>
#include<vector>
using namespace std;

class Solution{
public:
    vector<int> twoSum(Solution n);
    Solution(vector<int>& a, int b)
            :   nums(a) , m_target(b)
    {};

    vector<int> get_num() const{
        return nums ;
    };
    int get_target() const{
        return m_target ;
    };
    vector<int>  result;
private:
    const int m_target;
    vector<int> &nums;
};
#endif //INC_4_5_TWOSUM_H
