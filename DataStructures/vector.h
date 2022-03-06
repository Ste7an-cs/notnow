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
        //allocate 2 elements
        //ReAlloc(2);
    }

    ~vector()
    {
        std::cout << " vector Destory" << std::endl;
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }

    void pushBack( T&& value)
    {
        if(m_Size >= m_Capacity)
            ReAlloc(m_Capacity + m_Capacity / 2);
        m_Data[m_Size] = std::move(value);
        m_Size ++;
    }

    void pushBack(const T& value)
    {
        if(m_Size >= m_Capacity)
            ReAlloc(m_Capacity + m_Capacity / 2);
        m_Data[m_Size] = value;
        m_Size ++;
    }

    template<typename... Args>
    T& EmplaceBack(Args&&... args)
    {
        if(m_Size >= m_Capacity)
            ReAlloc(m_Capacity + m_Capacity / 2);
        //placement new
        std::cout << " Placement new" << std::endl;
        new (&m_Data[m_Size]) T(std::forward<Args>(args)...);

        //m_Data[m_Size] = T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }
    constexpr size_t Size() const {return m_Size; }

    T& operator[](size_t index) {return m_Data[index] ;}
    const T& operator[](size_t index) const  {return m_Data[index] ;}

    void PopBack()
    {
        std::cout << "Pop Back" << std::endl;
        if (m_Size > 0)
        {
            m_Size--;
            m_Data[m_Size].~T();
        }

    }
    void Clear()
    {
        for(size_t i=0; i < m_Size; ++i){
            m_Data[i].~T();
        }
        m_Size = 0;
        std::cout << "delete everything" << std::endl;
    }
private:
    void ReAlloc(size_t newCapacity)
    {
        //1. allocate a new block of memory
        //2. copy/move old elements into new block
        //3. delete
        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
        if (newCapacity < m_Size) m_Size = newCapacity;

        //move
        for(size_t i = 0; i < m_Size; i++)
            newBlock[i] = std::move(m_Data[i]);
        //delete
        std::cout << " realloc" << std::endl;
        for(size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        //set
        ::operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

private:
    T* m_Data = (T*)::operator new(m_Capacity * sizeof(T));
    size_t m_Size = 0;
    size_t m_Capacity = 2;
};



#endif //DATASTRUCTURES_VECTOR_H
