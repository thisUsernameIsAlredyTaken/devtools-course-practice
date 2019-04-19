// Copyright 2019 Zhivaev Artem

#include <gtest/gtest.h>

#include "include/matcher.h"

TEST(MatcherTest, MCharSet_Moves_Iterator) {
    // Arrange
    std::string seq("abc");
    std::string::const_iterator it = seq.begin();

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

