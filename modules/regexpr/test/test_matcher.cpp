// Copyright 2019 Zhivaev Artem

#include <gtest/gtest.h>

#define protected public
#define private   public

#include "include/matcher.h"

#undef private
#undef protected


TEST(MatcherTest, MCharSet_Moves_Iterator) {
    // Arrange
    const std::string seq("abc");
    auto it = seq.begin();

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 1), it);
}

TEST(MatcherTest, MCharSet_Moves_Iterator_Char_Class) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}


TEST(MatcherTest, MCharSet_Moves_Iterator_Char_Class_Range) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}

TEST(MatcherTest, MCharSet_Single_Char) {
    // Arrange
    const std::string seq("abc");
    auto it = seq.begin();
    std::set<char> s;

    // Act
    MCharSet m(it);
    s.insert('a');

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MatcherTest, MCharSet_CharClass) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();
    std::set<char> s;

    // Act
    MCharSet m(it);
    s.insert('a');
    s.insert('b');
    s.insert('c');

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MatcherTest, MCharSet_Range_CharClass) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();
    std::set<char> s;

    // Act
    MCharSet m(it);
    s.insert('a');
    s.insert('b');
    s.insert('c');
    s.insert('d');
    s.insert('e');
    s.insert('f');

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MatcherTest, MCharSet_Mixed_CharClass) {
    // Arrange
    const std::string seq("[a-def]ghij");
    auto it = seq.begin();
    std::set<char> s;

    // Act
    MCharSet m(it);
    s.insert('a');
    s.insert('b');
    s.insert('c');
    s.insert('d');
    s.insert('e');
    s.insert('f');

    // Assert
    EXPECT_EQ(s, m.chSet_);
}




