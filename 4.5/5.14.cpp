//
// Created by ste7an on 2021/12/7.
//
#include<string>
#include<iostream>
using namespace std;
int main() {
    int curCnt = 1, maxCnt = 0;
    string currString, preString = "", maxString;
    while (cin >> currString && currString != "n") {
        if (currString == preString) {
            ++curCnt;
            if (curCnt > maxCnt) {
                maxCnt = curCnt;
                maxString = currString;
            }
        } else curCnt = 1;
        preString = currString;
    }


    if(maxCnt >1) {
        cout << "max = " << maxCnt << endl;
        cout << "word is " << maxString << endl;
    }else cout <<"每个字符串都只出现了一次" << endl;
    return 0;

}