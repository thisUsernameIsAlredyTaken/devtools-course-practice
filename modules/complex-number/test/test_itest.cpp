// Copyright 2019 Iamshchikov Ivan

#include <gtest/gtest.h>

#include "include/complex_number.h"

TEST(_ComplexNumberTest, Can_Create_Complex_Number) {
  // Arrange
  double re = 1.6;
  double im = -5.2;

  // Act
  ComplexNumber z(re, im);

  // Assert
  EXPECT_EQ(re, z.getRe());
  EXPECT_EQ(im, z.getIm());
}

TEST(_ComplexNumberTest, Addition_Of_Two_Complex_Number) {
  // Arrange
  double re1 = 1.5;
  double im1 = -5.2;
  double re2 = 5.2;
  double im2 = 1.3;
  ComplexNumber z1(re1, im1);
  ComplexNumber z2(re2, im2);
  ComplexNumber res;

  // Act
  res = z1 + z2;

  // Assert
  EXPECT_EQ(re1 + re2, res.getRe());
  EXPECT_EQ(im1 + im2, res.getIm());
}

TEST(_ComplexNumberTest, Division_Of_Two_Complex_Number) {
  // Arrange
  double re1 = 6.5;
  double im1 = 0;
  double re2 = 3.25;
  double im2 = 0;
  ComplexNumber z1(re1, im1);
  ComplexNumber z2(re2, im2);
  ComplexNumber res;

  // Act
  res = z1 / z2;

  // Assert
  EXPECT_EQ(re1 / re2, res.getRe());
}