#include <Core/Types.h>
#include <iostream>

static i64 NEXT_ID = 0;

class Test {
public:
    Test()
    {
        m_id = NEXT_ID++;
        std::cout << "Created #" << m_id << '\n';
    }

    Test(const Test& other)
    {
        m_id = NEXT_ID++;
        std::cout << "Copied #" << other.m_id << " into #" << m_id << '\n';
    }

    Test(Test&& other)
    {
        m_id = other.m_id;
        other.m_id = -1;
        std::cout << "Moved #" << m_id << '\n';
    }

    ~Test()
    {
        std::cout << "Destroyed #" << m_id << '\n';
    }

private:
    i64 m_id = 0;
};
