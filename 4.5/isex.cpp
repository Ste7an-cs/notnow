//
// Created by Ste7an on 2022/2/22.
//
#include<iostream>
#include<vector>
void isex(std::vector<int> &num1, std::vector<int> &num2){

        auto it1 = num1.cbegin();
        auto it2 = num2.cbegin();
        while (it1 != num1.cend() && it2 != num2.cend()){
            if (*it1 != *it2) {
                std::cout << "不存在前缀关系" << std::endl;
                break;
            }
            ++it1;
            ++it2;
        }
        if (it1 == num1.cend()) std::cout << "num1 是 num2 的前缀" << std::endl;
        if (it2 == num2.cend()) std::cout << "num2 是 num1 的前缀" << std::endl;

}