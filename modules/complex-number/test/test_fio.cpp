#include <gtest/gtest.h>

#include "include/complex_number.h"

TEST(FIO_ComplexNumberTest, Success_Test) {
    // Arrange
    double re = 0.0;
    double im = 0.0;

    // Act
    ComplexNumber z(re, im);

    // Assert
    EXPECT_EQ(re, z.getRe());
    EXPECT_EQ(im, z.getIm());
}

TEST(FIO_ComplexNumberTest, Success_Test_1) {
    // Arrange
    double re = 0.0;
    double im = 0.0;
    bool res = false;

    // Act
    ComplexNumber z(re, im);

    // Assert
    EXPECT_EQ(false, res);
}
