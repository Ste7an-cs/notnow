//
// Created by ste7an on 2021/12/10.
//
#include <iostream>
#include <map>
#include<vector>
using namespace std;

class Solution{
public:
    vector<int> twoSum(Solution n);
    Solution(vector<int>& a, int b)
            :   nums(a) , target(b)
    {}

     vector<int> get_num() const{
        return nums ;
    };
     int get_target() const{
        return target ;
    };


    vector<int>  result;

private:
     const int target;
     vector<int> &nums;
};
 vector<int> Solution::twoSum(Solution n) {
     int target = Solution::get_target();
     vector<int> num = get_num();
     map<int,int> hashMap;
     for(int i = 0; i < num.size(); ++i){
        auto it = hashMap.find(target - num[i]);
        if (it != hashMap.end()) return {it->second , i};
        hashMap[num[i]] = i;
    }
     return {};
}

int main(){
    vector<int> nums = {1, 2, 3, 6, 10};
    int target = 7;
    Solution twosum(nums, target);
    twosum.result = twosum.twoSum(twosum);
    cout <<twosum.result[0] ;
    cout <<twosum.result[1] ;

}
