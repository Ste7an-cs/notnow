#include <iostream>
#include <vector>
#include "vector.h"

struct Vector3
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    int* m_MemoryBlock = nullptr;
    Vector3(){
        m_MemoryBlock = new int[5];
    }
    Vector3(float scalar)
    : x(scalar), y(scalar), z(scalar){
        m_MemoryBlock = new int[5];
    }
    Vector3(float x, float y, float z)
    : x(x), y(y), z(z) { m_MemoryBlock = new int[5];}

    Vector3(const Vector3& other)
        : x(other.x), y(other.y), z(other.z)
    {
        std::cout << "Copy\n";
    }
    Vector3( Vector3&& other) noexcept
        : x(other.x), y(other.y), z(other.z)
    {
        m_MemoryBlock = other.m_MemoryBlock;
        other.m_MemoryBlock = nullptr;
        std::cout << "Move\n";
    }


    ~Vector3()
    {
        delete[] m_MemoryBlock;
        std::cout << "Vector3 Destory\n";
    }
    Vector3& operator=(const Vector3& other)
    {
        std::cout << "Copy assignment\n";
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vector3& operator=( Vector3&& other)
 noexcept     {
        m_MemoryBlock = other.m_MemoryBlock;
        other.m_MemoryBlock = nullptr;
        std::cout << "Move assignment\n";
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;

    }
};

template<typename T>
void PrintVector(const vector<T>& v)
{
    for(size_t i=0; i<v.Size(); i++)
    {
        std::cout << v[i] << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

template<>
void PrintVector(const vector<Vector3>& v)
{
    for(size_t i=0; i<v.Size(); i++)
    {
        std::cout << v[i].x << "," << v[i].y << "," << v[i].z << std::endl;
    }
    std::cout << "-------------" << std::endl;
}
int main()
{
    vector<Vector3> data;
    data.pushBack(Vector3(1.0f));
    data.pushBack(Vector3(2, 3, 4));
    data.pushBack(Vector3());
    PrintVector(data);
    data.PopBack();
    data.PopBack();
    data.EmplaceBack();
    data.EmplaceBack(1,2,3);
    data.EmplaceBack(12,21,31);
    PrintVector(data);
    data.Clear();
    PrintVector(data);
    data.EmplaceBack(1,2,3);
    data.EmplaceBack(12,21,31);
    PrintVector(data);
}
