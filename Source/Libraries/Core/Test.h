#pragma once

#include <Core/Move.h>
#include <Core/Stdio.h>
#include <Core/Vector.h>

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
        cout().println("Running ", m_tests.size(), " test(s).");

        for (const Test& test : m_tests) {
            cout().println("Running test '", test.name(), '\'');
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

#define EXPECT_EQ(x, y) static_cast<bool>((x) == (y)) ? void(0) : cerr().println("FAIL: ", __FILE__, ':', __LINE__, ": Expect EQ failed: ", #x, " != ", #y)
#define EXPECT_NEQ(x, y) static_cast<bool>((x) != (y)) ? void(0) : cerr().println("FAIL: ", __FILE__, ':', __LINE__, ": Expect NEQ failed: ", #x, " == ", #y)
#define EXPECT(x) static_cast<bool>(x) ? void(0) : cerr().println("FAIL: ", __FILE__, ':', __LINE__, ": Expect '", #x, "' failed")

int main()
{
    TestSuite::the().run();
    return 0;
}
