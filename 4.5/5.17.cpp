//
// Created by ste7an on 2021/12/7.
//
#include <iostream>
#include <vector>
using namespace std;

int main(){
   vector<int> num1, num2;
   num1 = {0,1,1,2};
   num2 = {0,1,1,2,3,5,8};
   auto it1 = num1.cbegin();
   auto it2 = num2.cbegin();
   while(it1 != num1.cend() && it2 != num2.cend()){
       if (*it1 != *it2){
           cout << "不存在前缀关系" << endl;
           break;
       }
       ++it1;
       ++it2;
   }
   if(it1 == num1.cend()) cout << "num1 是 num2 的前缀" << endl;
   if(it2 == num2.cend()) cout << "num2 是 num1 的前缀" << endl;
    return 0;
}
