//
// Created by ste7an on 2021/12/6.
//
#include <iostream>
using namespace std;



void binary_print(const unsigned int &v){
    int i;
    int bit;
    int size = sizeof(v)*8;
    //这里的size是输入参数v的位数，直接用32代替也可以，但写成sizeof(v)*8这样更为通用。
    for(i = 0; i < size; i ++)
    {
        bit = v&(1<<(size-i-1));//提取出第i位的值
        if(bit == 0) cout << 0;
        else cout << 1;
        if(i % 4 == 3)cout << ' '; //为了方便阅读输出，在每输出四位后加一个空格
    }
    cout << '\n';
}

int main(){
    unsigned char str = 'q';
    unsigned int  num,num1;
    num = ~str ;
    num1 =~(str << 6);
    cout <<"binary str is:" <<endl;
    binary_print(str);
    cout <<"binary num is:" <<endl;
    binary_print(num);
    binary_print(num1);
    cout << num << endl;
    int a= 12, b = 4,mid,mid1;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << "b="<<b <<endl << "a=" <<a <<endl;
    mid = (a ^ b) >> 1;
    mid1= a & b ;
    cout << mid <<endl;
    cout<<mid1<<endl;
    cout << sizeof(unsigned int) << endl;
    cout << sizeof(unsigned long ) << endl;
    unsigned long u11 = -1, u12 = 255;
    cout << "u11 & u12=" << (u11 & u12) <<endl;
    cout << "u11 && u12=" << (u11 && u12) <<endl;
    cout << "u11 | u12=" << (u11 | u12) <<endl;
    cout << "u11 || u12=" << (u11 % u12) <<endl;
    char str1 ='a';
    cout << "u11 || u12=" << char(int(str1)-32)<<endl;
    cout << "u11 || u12=" << static_cast<char>(int(str1)-32)<<endl;

}