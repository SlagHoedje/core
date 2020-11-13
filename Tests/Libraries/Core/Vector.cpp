#include <Core/Test.h>

#include <Core/Vector.h>

TEST(basic)
{
    Vector<int> vector;

    EXPECT_EQ(vector.size(), 0);

    vector.append(1);
    vector.append(2);
    vector.append(3);

    EXPECT_EQ(vector.size(), 3);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 3);

    vector.clear();

    EXPECT_EQ(vector.size(), 0);
}

TEST(insert_remove)
{
    Vector<int> vector;

    vector.append(1);
    vector.append(2);

    EXPECT_EQ(vector.size(), 2);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);

    vector.prepend(0);

    EXPECT_EQ(vector.size(), 3);
    EXPECT_EQ(vector[0], 0);
    EXPECT_EQ(vector[1], 1);
    EXPECT_EQ(vector[2], 2);

    vector.insert(1, 5);
    vector.insert(1, 6);

    EXPECT_EQ(vector.size(), 5);
    EXPECT_EQ(vector[0], 0);
    EXPECT_EQ(vector[1], 6);
    EXPECT_EQ(vector[2], 5);
    EXPECT_EQ(vector[3], 1);
    EXPECT_EQ(vector[4], 2);

    vector.remove(0);
    vector.remove(3);

    EXPECT_EQ(vector.size(), 3);
    EXPECT_EQ(vector[0], 6);
    EXPECT_EQ(vector[1], 5);
    EXPECT_EQ(vector[2], 1);

    vector.clear();

    EXPECT_EQ(vector.size(), 0);
}
