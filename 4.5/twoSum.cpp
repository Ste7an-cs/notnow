//
// Created by ste7an on 2021/12/10.
//
#include"include/twoSum.h"


std::vector<int> Solution::twoSum(Solution n) {
     int target = Solution::get_target();
     std::vector<int> num = get_num();
     map<int,int> hashMap;
     for(int i = 0; i < num.size(); ++i){
        auto it = hashMap.find(target - num[i]);
        if (it != hashMap.end()) return {it->second , i};
        hashMap[num[i]] = i;
    }
     return {};
}
