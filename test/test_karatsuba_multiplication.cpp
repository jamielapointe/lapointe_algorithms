#include <gtest/gtest.h>

#include <iostream>

#include "karatsuba_multiplication.hpp"

using LaPointe_Algorithms::Multiplication::Karatsuba::add;
using LaPointe_Algorithms::Multiplication::Karatsuba::multiply;
using LaPointe_Algorithms::Multiplication::Karatsuba::sub;

TEST(TestKaratsubaMultiplication, simpleAdd0) {
  std::string x   = "4";
  std::string y   = "2";

  std::string sum = add(x, y);
  ASSERT_EQ(sum, "6");
}

TEST(TestKaratsubaMultiplication, simpleAdd1) {
  std::string x   = "9";
  std::string y   = "9";

  std::string sum = add(x, y);
  ASSERT_EQ(sum, "18");
}

TEST(TestKaratsubaMultiplication, simpleAdd2) {
  std::string x   = "25";
  std::string y   = "36";

  std::string sum = add(x, y);
  ASSERT_EQ(sum, "61");
}

TEST(TestKaratsubaMultiplication, simpleAdd3) {
  std::string x   = "873";
  std::string y   = "541";

  std::string sum = add(x, y);
  ASSERT_EQ(sum, "1414");
}

TEST(TestKaratsubaMultiplication, simpleAdd4) {
  std::string x   = "873";
  std::string y   = "9";

  std::string sum = add(x, y);
  ASSERT_EQ(sum, "882");
}

TEST(TestKaratsubaMultiplication, largeAdd0) {
  std::string x   = "3141592653589793238462643383279502884197169399375105820974944592";
  std::string y   = "2718281828459045235360287471352662497757247093699959574966967627";

  std::string sum = add(x, y);
  ASSERT_EQ(sum, "5859874482048838473822930854632165381954416493075065395941912219");
}

TEST(TestKaratsubaMultiplication, simpleSub0) {
  std::string x   = "4";
  std::string y   = "2";

  std::string sum = sub(x, y);
  ASSERT_EQ(sum, "2");
}

TEST(TestKaratsubaMultiplication, simpleSub1) {
  std::string x   = "9";
  std::string y   = "9";

  std::string sum = sub(x, y);
  ASSERT_EQ(sum, "0");
}

TEST(TestKaratsubaMultiplication, simpleSub2) {
  std::string x   = "25";
  std::string y   = "36";

  std::string sum = sub(x, y);
  ASSERT_EQ(sum, "-11");
}

TEST(TestKaratsubaMultiplication, simpleSub3) {
  std::string x   = "873";
  std::string y   = "541";

  std::string sum = sub(x, y);
  ASSERT_EQ(sum, "332");
}

TEST(TestKaratsubaMultiplication, simpleSub4) {
  std::string x   = "873";
  std::string y   = "9";

  std::string sum = sub(x, y);
  ASSERT_EQ(sum, "864");
}

TEST(TestKaratsubaMultiplication, largeSub0) {
  std::string x   = "3141592653589793238462643383279502884197169399375105820974944592";
  std::string y   = "2718281828459045235360287471352662497757247093699959574966967627";

  std::string sum = sub(x, y);
  ASSERT_EQ(sum, "423310825130748003102355911926840386439922305675146246007976965");
}

TEST(TestKaratsubaMultiplication, simpleMultiplication0) {
  std::string x = "9";
  std::string y = "4";
  std::string expcted{"36"};
  auto        product = multiply(x, y);
  ASSERT_EQ(product, expcted);
}

TEST(TestKaratsubaMultiplication, simpleMultiplication1) {
  std::string x = "26";
  std::string y = "5";
  std::string expected{"130"};
  auto        product = multiply(x, y);
  ASSERT_EQ(product, expected);
}

TEST(TestKaratsubaMultiplication, simpleMultiplication2) {
  std::string x = "75";
  std::string y = "32";
  std::string expected{"2400"};
  auto        product = multiply(x, y);
  ASSERT_EQ(product, expected);
}

TEST(TestKaratsubaMultiplication, simpleMultiplication3) {
  std::string x = "3747";
  std::string y = "7988";
  std::string expected{"29931036"};
  auto        product = multiply(x, y);
  ASSERT_EQ(product, expected);
}

TEST(TestKaratsubaMultiplication, simpleMultiplication4) {
  std::string x = "9378";
  std::string y = "3";
  std::string expected{"28134"};
  auto        product = multiply(x, y);
  ASSERT_EQ(product, expected);
}

TEST(TestKaratsubaMultiplication, largeMultiplication0) {
  std::string x = "3141592653589793238462643383279502884197169399375105820974944592";
  std::string y = "2718281828459045235360287471352662497757247093699959574966967627";
  std::string expected(
      "8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871"
      "952806582723184");
  auto product = multiply(x, y);
  ASSERT_EQ(product, expected);
  std::cout << product << std::endl;
}
