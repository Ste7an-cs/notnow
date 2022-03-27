#include <iostream>
#include "iterator.h"
#include "allocator.h"
#include "vector.h"
#include <vector>
#include <string>
struct Person
{
public:

    Person(int age, std::string name)
            :m_age(age), m_name(std::move(name))
    {
        std::cout<< "i am constructed" << std::endl;
    }

    Person(const Person& other)
            :m_age(other.m_age), m_name(other.m_name)
    {
        std::cout<< "i am copyed" << std::endl;
    }

    Person(Person&& other) noexcept
    :m_age(other.m_age), m_name(other.m_name)

    {
        std::cout<< "i am moved" << std::endl;
    }
    ~ Person()
    {
        std::cout<< "destroy" << std::endl;
    }
private:
    int m_age;
    std::string m_name;
};


int main() {

    std::vector<Person> students;
    Person kate(18, "kate");
//    std::cout<< "emplace back: lvalue" << std::endl;
//    students.emplace_back(kate);


    std::cout<< "push back: rvalue" << std::endl;
//    students.push_back(Person(18, "kate"));
    students.push_back(kate);



    return 0;
}
