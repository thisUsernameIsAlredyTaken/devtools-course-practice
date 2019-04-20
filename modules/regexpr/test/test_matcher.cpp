// Copyright 2019 Zhivaev Artem

#include <gtest/gtest.h>

#include <string>
#include <set>

#define protected public
#define private   public

#include "include/matcher.h"

#undef private
#undef protected


using std::string;
using std::set;


TEST(MCharSetTest_Constructor, Moves_Iter_Single_Char) {
    // Arrange
    const std::string seq("abc");
    auto it = seq.begin();

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 1), it);
}

TEST(MCharSetTest_Constructor, Moves_Iter_Char_Class) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}


TEST(MCharSetTest_Constructor, Moves_Iter_Char_Class_Range) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}

TEST(MCharSetTest_Constructor, Init_Char_Set_Single_Char) {
    // Arrange
    const std::string seq("abc");
    auto it = seq.begin();
    std::set<char> s = { 'a' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest_Constructor, Init_Char_Set_Char_Class) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest_Constructor, Init_Char_Set_Char_Class_Range) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest_Constructor, Init_Char_Set_Char_Class_Mixed_1) {
    // Arrange
    const std::string seq("[a-def]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest_Constructor, Init_Char_Set_Char_Class_Mixed_2) {
    // Arrange
    const std::string seq("[abc-f]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest_Constructor, Init_Char_Set_Char_Class_Mixed_3) {
    // Arrange
    const std::string seq("[abc-fgh]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest_Constructor, Init_Char_Set_Char_Class_Mixed_4) {
    // Arrange
    const std::string seq("[ab-de-gh]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest_Constructor, Moves_Iter_Braces) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    auto sit(seq.begin());

    // Act
    MCharSet m(&sit);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), sit);
}

TEST(MCharSetTest_Constructor, Moves_Iter_Asterisk) {
    // Arrange
    const string seq("[abc-fgh]*qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), it);
}

TEST(MCharSetTest_Constructor, Moves_Iter_Plus) {
    // Arrange
    const string seq("[abc-fgh]+qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), it);
}

TEST(MCharSetTest_Constructor, Moves_Iter_QMark) {
    // Arrange
    const string seq("[abc-fgh]?qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), it);
}

TEST(MCharSetTest_Constructor, Min_Max_Init_Braces_1) {
    // Arrange
    const string seq("[abc-fgh]{11,72}qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(11, m.min_);
    EXPECT_EQ(72, m.max_);
}

TEST(MCharSetTest_Constructor, Min_Max_Init_Asterisk) {
    // Arrange
    const string seq("[abc-fgh]*qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(0, m.min_);
    EXPECT_EQ(-1, m.max_);
}

TEST(MCharSetTest_Constructor, Min_Max_Init_Plus) {
    // Arrange
    const string seq("[abc-fgh]+qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(1, m.min_);
    EXPECT_EQ(-1, m.max_);
}

TEST(MCharSetTest_Constructor, Min_Max_Init_QMark) {
    // Arrange
    const string seq("[abc-fgh]?qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(0, m.min_);
    EXPECT_EQ(1, m.max_);
}

TEST(MCharSetTest_Constructor, Min_Max_Init_Braces_2) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    auto sit(seq.begin());

    // Act
    MCharSet m(&sit);

    // Assert
    EXPECT_EQ(1, m.min_);
    EXPECT_EQ(7, m.max_);
}

TEST(MCharSetTest_Constructor, DISABLED_Min_Max_Init_Number_Only) {
    // Arrange
    const string seq("a{4}asd");
    auto sit = seq.begin();

    // Act
    MCharSet m(&sit);

    // Assert
    EXPECT_EQ(4, m.min_);
    EXPECT_EQ(4, m.max_);
}





TEST(MCharSetTest_Match, Moves_Iter) {
    // Arrange
    const std::string seq("[a-f]sssss");
    const string str("bcccc");
    auto sit = seq.begin();
    auto it = str.begin();
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 1), it);
}

TEST(MCharSetTest_Match, Returns_True_Single_Char) {
    // Arrange
    const string seq("[a-f]sssss");
    const string str("dccccc");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest_Match, Returns_False) {
    // Arrange
    const string seq("[a-f]sssss");
    const string str("gccccc");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_FALSE(m.match(&it));
}

TEST(MCharSetTest_Match, Moves_Iter_In_Range) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    const string str("abduuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 3), it);
}

TEST(MCharSetTest_Match, Moves_Iter_Out_Of_Range) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    const string str("abcdefabcduuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 7), it);
}

TEST(MCharSetTest_Match, Moves_Iter_Single_Char) {
    // Arrange
    const string seq("[a-f]?asdasd");
    const string str("cuuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 1), it);
}

TEST(MCharSetTest_Match, Moves_Iter_No_Char) {
    // Arrange
    const string seq("[a-f]?asdasd");
    const string str("uuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(str.begin(), it);
}

TEST(MCharSetTest_Match, Moves_Iter_One_Char) {
    // Arrange
    const string seq("[a-f]+asdasd");
    const string str("duuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 1), it);
}

TEST(MCharSetTest_Match, Moves_Iter_Some_Chars_1) {
    // Arrange
    const string seq("[a-f]+asdasd");
    const string str("dafbuuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 4), it);
}

TEST(MCharSetTest_Match, Moves_Iter_Some_Chars_2) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("facduuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 4), it);
}

TEST(MCharSetTest_Match, Moves_Iter_No_Chars) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("uuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(str.begin(), it);
}

TEST(MCharSetTest_Match, Returns_True_Min_Chars) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("abcuuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest_Match, Returns_True_Max_Chars) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("abcfedcuuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest_Match, Returns_True_In_Range) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("acfdcuuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest_Match, Returns_False_Not_Enough_Mathces) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("acuuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_FALSE(m.match(&it));
}

TEST(MCharSetTest_Match, Returns_True_No_Matches) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("uuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest_Match, Returns_True_Some_Mathes) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("acbfduuuuuu");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest_Match, DISABLED_Stops_When_Next_Matched) {
    // Arrange
    const string seq("a*b");
    const string str("aaaaaaab");
    auto sit = seq.begin();
    auto it = str.begin();
    MCharSet m1(&sit);
    MCharSet m2(&sit);

    // Act
    m1.setNext(&m2);
    m1.match(&it);

    // Assert
    EXPECT_EQ(seq.end(), sit);
}

TEST(MCharSetTest_Match, DISABLED_Stops_When_Next_Matched_Same_Char) {
    // Arrange
    const string seq("a*aaa");
    const string str("aaaaaaab");
    auto sit = seq.begin();
    auto it = str.begin();
    MCharSet m1(&sit);
    MCharSet m2(&sit);

    // Act
    m1.setNext(&m2);
    m1.match(&it);

    // Assert
    EXPECT_EQ(next(seq.end(), 7), sit);
}






TEST(MStringTest_Constructor, Moves_Iter_Until_Left_Bracket) {
    // Arrange
    const string seq("abc[0-9]");
    auto it = seq.begin();

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 3), it);
}

TEST(MStringTest_Constructor, MStr_Init_Until_Left_Bracket) {
    // Arrange
    const string seq("abc[0-9]");
    auto it = seq.begin();
    const string mStr("abc");

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(mStr, m.mStr_);
}

TEST(MStringTest_Constructor, Moves_Iter_Until_Asterisk) {
    // Arrange
    const string seq("abcd*");
    auto it = seq.begin();

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 3), it);
}

TEST(MStringTest_Constructor, MStr_Init_Until_Asterisk) {
    // Arrange
    const string seq("abcd*");
    auto it = seq.begin();
    const string mStr("abc");

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(mStr, m.mStr_);
}

TEST(MStringTest_Constructor, Moves_Iter_Until_Plus) {
    // Arrange
    const string seq("abcd+");
    auto it = seq.begin();

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 3), it);
}

TEST(MStringTest_Constructor, MStr_Init_Until_Plus) {
    // Arrange
    const string seq("abcd+");
    auto it = seq.begin();
    const string mStr("abc");

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(mStr, m.mStr_);
}


TEST(MStringTest_Constructor, Moves_Iter_Until_QMark) {
    // Arrange
    const string seq("abcd?");
    auto it = seq.begin();

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 3), it);
}

TEST(MStringTest_Constructor, MStr_Init_Until_QMark) {
    // Arrange
    const string seq("abcd?");
    auto it = seq.begin();
    const string mStr("abc");

    // Act
    MString m(&it);

    // Assert
    EXPECT_EQ(mStr, m.mStr_);
}

