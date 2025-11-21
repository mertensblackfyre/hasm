#include "../includes/translate.h"
#include <gtest/gtest.h>

TEST(Translate, A_Instructions) {
  EXPECT_EQ(Translate::translate_a_instruc("@15"), "0000000000001111");
  EXPECT_EQ(Translate::translate_a_instruc("@1"), "0000000000000001");
  EXPECT_EQ(Translate::translate_a_instruc("@32"), "0000000000100000");
  EXPECT_EQ(Translate::translate_a_instruc("@99"), "0000000001100011");

  // Rs
  EXPECT_EQ(Translate::translate_a_instruc("@R0"), "0000000000000000");
  EXPECT_EQ(Translate::translate_a_instruc("@R1"), "0000000000000001");
  EXPECT_EQ(Translate::translate_a_instruc("@R2"), "0000000000000010");
  EXPECT_EQ(Translate::translate_a_instruc("@R3"), "0000000000000011");
  EXPECT_EQ(Translate::translate_a_instruc("@R4"), "0000000000000100");
  EXPECT_EQ(Translate::translate_a_instruc("@R5"), "0000000000000101");
  EXPECT_EQ(Translate::translate_a_instruc("@R6"), "0000000000000110");
  EXPECT_EQ(Translate::translate_a_instruc("@R7"), "0000000000000111");
  EXPECT_EQ(Translate::translate_a_instruc("@R8"), "0000000000001000");
  EXPECT_EQ(Translate::translate_a_instruc("@R9"), "0000000000001001");
  EXPECT_EQ(Translate::translate_a_instruc("@R10"), "0000000000001010");
  EXPECT_EQ(Translate::translate_a_instruc("@R11"), "0000000000001011");
  EXPECT_EQ(Translate::translate_a_instruc("@R12"), "0000000000001100");
  EXPECT_EQ(Translate::translate_a_instruc("@R13"), "0000000000001101");
  EXPECT_EQ(Translate::translate_a_instruc("@R14"), "0000000000001110");
  EXPECT_EQ(Translate::translate_a_instruc("@R15"), "0000000000001111");

  // SYMBOLS
  EXPECT_EQ(Translate::translate_a_instruc("@SCREEN"), "0100000000000000");
  EXPECT_EQ(Translate::translate_a_instruc("@KBD"), "0110000000000000");
  EXPECT_EQ(Translate::translate_a_instruc("@SP"), "0000000000000000");
  EXPECT_EQ(Translate::translate_a_instruc("@LCL"), "0000000000000001");
  EXPECT_EQ(Translate::translate_a_instruc("@ARG"), "0000000000000010");
  EXPECT_EQ(Translate::translate_a_instruc("@THIS"), "0000000000000011");
  EXPECT_EQ(Translate::translate_a_instruc("@THAT"), "0000000000000100");
}
