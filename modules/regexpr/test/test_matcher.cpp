// Copyright 2019 Zhivaev Artem

#include <gtest/gtest.h>

#define protected public
#define private   public

#include "include/matcher.h"

#undef private
#undef protected

using namespace std;

TEST(MCharSetTest, Constructor_Moves_Iterator) {
    // Arrange
    const std::string seq("abc");
    auto it = seq.begin();

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 1), it);
}

TEST(MCharSetTest, Constructor_Moves_Iterator_Char_Class) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}


TEST(MCharSetTest, Constructor_Moves_Iterator_Char_Class_Range) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}

TEST(MCharSetTest, Char_Set_Init_Single_Char) {
    // Arrange
    const std::string seq("abc");
    auto it = seq.begin();
    std::set<char> s = { 'a' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Char_Class) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Range_Char_Class) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass) {
    // Arrange
    const std::string seq("[a-def]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass_2) {
    // Arrange
    const std::string seq("[abc-f]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass_3) {
    // Arrange
    const std::string seq("[abc-fgh]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass_4) {
    // Arrange
    const std::string seq("[ab-de-gh]ghij");
    auto it = seq.begin();
    std::set<char> s = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Match_Moves_Iterator) {
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

TEST(MCharSetTest, Match_Returns_True) {
    // Arrange
    const string seq("[a-f]sssss");
    const string str("dccccc");
    auto sit(seq.begin());
    auto it(str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest, Match_Returns_False) {
    // Arrange
    const string seq("[a-f]sssss");
    const string str("gccccc");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_FALSE(m.match(&it));
}

TEST(MCharSetTest, Match_Count_Braces_Moves_Iterator) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    auto sit(seq.begin());

    // Act
    MCharSet m(&sit);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), sit);
}

TEST(MCharSetTest, Match_Count_Astersisk_Moves_Iterator) {
    // Arrange
    const string seq("[abc-fgh]*qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), it);
}

TEST(MCharSetTest, Match_Count_Plus_Moves_Iterator) {
    // Arrange
    const string seq("[abc-fgh]+qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), it);
}

TEST(MCharSetTest, Match_Count_Question_Mark_Moves_Iterator) {
    // Arrange
    const string seq("[abc-fgh]?qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), it);
}

TEST(MCharSetTest, Match_Count_Braces_Init_Range) {
    // Arrange
    const string seq("[abc-fgh]{11,72}qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(11, m.min_);
    EXPECT_EQ(72, m.max_);
}

TEST(MCharSetTest, Match_Count_Asterisk_Init_Range) {
    // Arrange
    const string seq("[abc-fgh]*qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(0, m.min_);
    EXPECT_EQ(-1, m.max_);
}

TEST(MCharSetTest, Match_Count_Plus_Init_Range) {
    // Arrange
    const string seq("[abc-fgh]+qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(1, m.min_);
    EXPECT_EQ(-1, m.max_);
}

TEST(MCharSetTest, Match_Count_Question_Mark_Init_Range) {
    // Arrange
    const string seq("[abc-fgh]?qwerty");
    auto it(seq.begin());

    // Act
    MCharSet m(&it);

    // Assert
    EXPECT_EQ(0, m.min_);
    EXPECT_EQ(1, m.max_);
}

TEST(MCharSetTest, Match_Count_Init_Braces) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    auto sit(seq.begin());

    // Act
    MCharSet m(&sit);

    // Assert
    EXPECT_EQ(m.min_, 1);
    EXPECT_EQ(m.max_, 7);
}

TEST(MCharSetTest, Braces_Match_Moves_Iterator) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    const string str("abduuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 3), it);
}

TEST(MCharSetTest, Braces_Match_Moves_Iterator_2) {
    // Arrange
    const string seq("[a-f]{1,7}asdasd");
    const string str("abcdefabcduuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 7), it);
}

TEST(MCharSetTest, QMark_Match_Moves_Iterator) {
    // Arrange
    const string seq("[a-f]?asdasd");
    const string str("cuuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 1), it);
}

TEST(MCharSetTest, QMark_Match_Moves_Iterator_2) {
    // Arrange
    const string seq("[a-f]?asdasd");
    const string str("uuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(str.begin(), it);
}

TEST(MCharSetTest, Plus_Match_Moves_Iterator) {
    // Arrange
    const string seq("[a-f]+asdasd");
    const string str("duuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 1), it);
}

TEST(MCharSetTest, Plus_Match_Moves_Iterator_2) {
    // Arrange
    const string seq("[a-f]+asdasd");
    const string str("dafbuuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 4), it);
}

TEST(MCharSetTest, Asterisk_Match_Moves_Iterator) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("facduuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(next(str.begin(), 4), it);
}

TEST(MCharSetTest, Asterisk_Match_Moves_Iterator_2) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("uuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act
    m.match(&it);

    // Assert
    EXPECT_EQ(str.begin(), it);
}


TEST(MCharSetTest, Braces_Match_Returns_True) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("abcuuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest, Braces_Match_Returns_True_2) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("abcfedcuuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest, Braces_Match_Returns_True_3) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("acfdcuuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest, Braces_Match_Returns_False) {
    // Arrange
    const string seq("[a-f]{3,7}asdasd");
    const string str("acuuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_FALSE(m.match(&it));
}

TEST(MCharSetTest, Asterisk_Match_Returns_True) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("uuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}

TEST(MCharSetTest, Asterisk_Match_Returns_True_2) {
    // Arrange
    const string seq("[a-f]*asdasd");
    const string str("acbfduuuuuu");
    auto sit (seq.begin());
    auto it (str.begin());
    MCharSet m(&sit);

    // Act & Assert
    EXPECT_TRUE(m.match(&it));
}



















