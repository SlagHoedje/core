#include <Core/Test.h>

#include <Core/String.h>
#include <Core/StringView.h>

TEST(null_string)
{
    String string;

    EXPECT(string.is_null());
    EXPECT_EQ(string.length(), 0);
    EXPECT_EQ(string.data(), nullptr);
}

TEST(string_with_contents)
{
    String string("Hello!");

    EXPECT(!string.is_null());
    EXPECT_EQ(string.length(), 6);
    EXPECT_NEQ(string.data(), nullptr);

    EXPECT_EQ(string, "Hello!");
}

TEST(string_comparison)
{
    String string1("Hello, World!");
    String string2("Hello, World!");

    EXPECT_EQ(string1, string2);
    EXPECT_EQ(string1, "Hello, World!");
    EXPECT_EQ(string1, StringView(string2));
    EXPECT_EQ(string1, StringView("Hello, World!"));
}

TEST(substring)
{
    String string("Banana");

    EXPECT_EQ(string.substring(2, 3), "nan");
    EXPECT_EQ(string.substring(2, 3), string.substring_view(2, 3));
}
