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
    MCharSet m(it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 1), it);
}

TEST(MCharSetTest, Constructor_Moves_Iterator_Char_Class) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}


TEST(MCharSetTest, Constructor_Moves_Iterator_Char_Class_Range) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(std::next(seq.begin(), 5), it);
}

TEST(MCharSetTest, Char_Set_Init_Single_Char) {
    // Arrange
    const std::string seq("abc");
    auto it = seq.begin();
    std::set<char> s{'a'};

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Char_Class) {
    // Arrange
    const std::string seq("[abc]defg");
    auto it = seq.begin();
    std::set<char> s{'a', 'b', 'c'};

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Range_Char_Class) {
    // Arrange
    const std::string seq("[a-f]ghij");
    auto it = seq.begin();
    std::set<char> s{'a', 'b', 'c', 'd', 'e', 'f'};

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass) {
    // Arrange
    const std::string seq("[a-def]ghij");
    auto it = seq.begin();
    std::set<char> s {'a', 'b', 'c', 'd', 'e', 'f'};

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass_2) {
    // Arrange
    const std::string seq("[abc-f]ghij");
    auto it = seq.begin();
    std::set<char> s {'a', 'b', 'c', 'd', 'e', 'f'};

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass_3) {
    // Arrange
    const std::string seq("[abc-fgh]ghij");
    auto it = seq.begin();
    std::set<char> s {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Char_Set_Init_Mixed_CharClass_4) {
    // Arrange
    const std::string seq("[ab-de-gh]ghij");
    auto it = seq.begin();
    std::set<char> s {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    // Act
    MCharSet m(it);

    // Assert
    EXPECT_EQ(s, m.chSet_);
}

TEST(MCharSetTest, Match_Moves_Iterator) {
    // Arrange
    const std::string seq{"[a-f]sssss"};
    const string str{"bcccc"};
    auto sit = seq.begin();
    auto it = str.begin();
    MCharSet m(sit);

    // Act
    m.match(it);

    // Assert
    EXPECT_EQ(next(str.begin(), 1), it);
}

TEST(MCharSetTest, Match_Returns_True) {
    // Arrange
    const string seq{"[a-f]sssss"};
    const string str{"dccccc"};
    auto sit {seq.begin()};
    auto it {str.begin()};
    MCharSet m{sit};

    // Act & Assert
    EXPECT_TRUE(m.match(it));
}

TEST(MCharSetTest, Match_Returns_False) {
    // Arrange
    const string seq{"[a-f]sssss"};
    const string str{"gccccc"};
    auto sit {seq.begin()};
    auto it {str.begin()};
    MCharSet m{sit};

    // Act & Assert
    EXPECT_FALSE(m.match(it));
}

TEST(MCharSetTest, Match_Count_Braces_Moves_Iterator) {
    // Arrange
    const string seq{"[a-f]{1,7}asdasd"};
    auto sit{seq.begin()};

    // Act
    MCharSet m{sit};

    // Assert
    EXPECT_EQ(next(seq.begin(), 10), sit);
}

TEST(MCharSetTest, Match_Count_Init_Braces) {
    // Arrange
    const string seq{"[a-f]{1,7}asdasd"};
    auto sit{seq.begin()};

    // Act
    MCharSet m{sit};

    // Assert
    EXPECT_EQ(m.min_, 1);
    EXPECT_EQ(m.max_, 7);
}

/* TEST(MCharSetTest, Match_Moves_Iterator) { */
/*     // Arrange */

/*     // Act */

/*     // Assert */

/* } */

/* TEST(MCharSetTest, Match_Moves_Iterator) { */
/*     // Arrange */

/*     // Act */

/*     // Assert */

/* } */

/* TEST(MCharSetTest, Match_Moves_Iterator) { */
/*     // Arrange */

/*     // Act */

/*     // Assert */

/* } */

/* TEST(MCharSetTest, Match_Moves_Iterator) { */
/*     // Arrange */

/*     // Act */

/*     // Assert */

/* } */

