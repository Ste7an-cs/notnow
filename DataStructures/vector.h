//
// Created by ste7an on 2022/3/6.
//
#include <iostream>
#ifndef DATASTRUCTURES_VECTOR_H
#define DATASTRUCTURES_VECTOR_H


template<typename T>
class vector
{
public:
    vector(){
        Realloc(2);
    }

    ~vector()
    {



    }

    void pushBack(const T& value)
    {
        if(m_Size >= m_Capacity)
            Realloc(m_Capacity + m_Capacity / 2);
        m_Data[m_Size] = value;
        m_Size ++;
    }

    size_t Size() {return m_Size; }

    T operator[](size_t index){return m_Data[index] ;}

    private:
    void Realloc(size_t newCapacity)
    {
        //1. allocate a new block of memory
        //2. copy/move old elements into new block
        //3. delete
        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

        if (newCapacity < m_Size) m_Size = newCapacity;
        for(size_t i = 0; i < m_Size; i++)
            newBlock[i] = std::move(m_Data[i]);
        for(size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

private:
    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0 ;
};



#endif //DATASTRUCTURES_VECTOR_H
