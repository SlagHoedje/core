#include <Core/Assert.h>
#include <Core/ByteBuffer.h>
#include <Core/Move.h>
#include <Core/String.h>
#include <Core/StringBuilder.h>
#include <Core/Types.h>
#include <Core/Vector.h>
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

int main()
{
    /// String testing
    String se;
    String se2(move(se));
    String se3(se2);

    se = se3;
    se = move(se3);

    String s("hello, world!");
    String s2(move(s));
    String s3(s2);

    s = s3;
    s = move(s3);
    s = "goodbye, world!";

    s.substring(4, 3);
    s.substring_view(4, 3);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    s = s;
    se = se;
#pragma GCC diagnostic pop

    ASSERT(!s.is_null(), "string shouldn't be null before moving");
    String s4(move(s));
    ASSERT(s.is_null(), "string should be null after moving");

    ASSERT(se.is_null(), "string should be null by default");

    ASSERT(s4.length() == 15, "length() returns incorrect length");

    // Vector Tests
    std::cout << "- Vector Tests\n";
    Vector<String> v;
    v.append("test");
    v.append("123");
    v.append("456");

    // String Builder Tests
    std::cout << "- String Builder Tests\n";
    StringBuilder sb;
    sb.append(String("Array: "));
    sb.append('[');
    sb.join(", ", v);
    sb.append(']');

    std::cout << sb.to_string() << '\n';

    // Vector Tests
    Vector<i32> vv(1);
    Vector<i32> vv2(1);
    vv = Vector<i32>(1);
    vv = vv2;

    Vector<i32> vv3;
    vv2 = vv3;
    vv2 = move(vv3);

    Vector<i32> vv4(vv2);
    Vector<i32> vv5(move(vv4));

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    vv = vv;
    vv2 = vv2;
#pragma GCC diagnostic pop

    // ByteBuffer tests
    ByteBuffer bb;
    ByteBuffer bb2(bb);
    ByteBuffer bb3(move(bb2));

    bb2 = bb;
    bb2 = move(bb2);
    bb3 = move(bb);

    StringView banana("banana");
    StringBuilder builder;
    builder.append(banana);
    builder.append('\n');

    banana = banana.substring_view(2, 3);

    builder.append(banana);
    builder.append('\n');

    std::cout << builder.to_string();

    builder.clear();

    String string = String("  hello world  et al  ");
    builder.join(", ", string.split_view(' '));
    builder.append('\n');

    std::cout << builder.to_string();
}
