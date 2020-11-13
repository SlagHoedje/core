#pragma once

#include <Core/Move.h>
#include <Core/Vector.h>
#include <stdio.h>

class Test {
public:
    Test(const char* name, void (*function)())
        : m_name(name)
        , m_function(function)
    {
    }

    const char* name() const
    {
        return m_name;
    }

    void exec() const
    {
        m_function();
    }

private:
    const char* m_name;
    void (*m_function)();
};

class TestSuite {
public:
    static TestSuite& the()
    {
        return global;
    }

    void add_test(Test&& test)
    {
        m_tests.append(move(test));
    }

    void run()
    {
        printf("Running %zu test(s).\n", m_tests.size());

        for (const Test& test : m_tests) {
            printf("Running test '%s'\n", test.name());
            test.exec();
        }
    }

private:
    static TestSuite global;

    Vector<Test> m_tests;
};

TestSuite TestSuite::global = TestSuite();

#define TEST(name)                                             \
    void __test_##name();                                      \
    static int __test_init_##name = ([] {                      \
        TestSuite::the().add_test(Test(#name, __test_##name)); \
    }(),                                                       \
        0);                                                    \
    void __test_##name()

#define EXPECT_EQ(x, y) static_cast<bool>((x) == (y)) ? void(0) : (void)printf("FAIL: %s:%d: Expect EQ failed: %s != %s\n", __FILE__, __LINE__, #x, #y)
#define EXPECT_NEQ(x, y) static_cast<bool>((x) != (y)) ? void(0) : (void)printf("FAIL: %s:%d: Expect NEQ failed: %s == %s\n", __FILE__, __LINE__, #x, #y)
#define EXPECT(x) static_cast<bool>(x) ? void(0) : (void)printf("FAIL: %s:%d: Expect %s failed\n", __FILE__, __LINE__, #x)

int main()
{
    TestSuite::the().run();
    return 0;
}
