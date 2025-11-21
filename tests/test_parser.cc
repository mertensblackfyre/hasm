#include "../includes/parser.h"
#include <gtest/gtest.h>

TEST(Parser, ParserInstructions) {
  EXPECT_EQ(Parser::parse_instruction("M=D       // RAM[1] = the sum"), "M=D");
  EXPECT_EQ(Parser::parse_instruction("M=D+1       // Hello   "), "M=D+1");
  EXPECT_EQ(Parser::parse_instruction("@LOOP      // goto LOOP "), "@LOOP");
  EXPECT_EQ(Parser::parse_instruction("    0;JMP"), "0;JMP");
  EXPECT_EQ(Parser::parse_instruction("AM= A+1  // AA"), "AM=A+1");
  EXPECT_EQ(Parser::parse_instruction(" @R1"), "@R1");
}

TEST(Parser, Parser_A) {
  EXPECT_EQ(Parser::parse_A_instruction("@12"), "12");
  EXPECT_EQ(Parser::parse_A_instruction("@R2"), "R2");
  EXPECT_EQ(Parser::parse_A_instruction("@1"), "1");
  EXPECT_EQ(Parser::parse_A_instruction("@"), "");
}

TEST(Parser, Parser_C) {
  C_Instruction test_1 = Parser::parse_C_instruction("M=D+1");
  C_Instruction test_2 = Parser::parse_C_instruction("M=D");
  C_Instruction test_3 = Parser::parse_C_instruction("0;JMP");
  C_Instruction test_4 = Parser::parse_C_instruction("D=D-1;JMP");

  // Test 1
  EXPECT_EQ(test_1.dest,"M");
  EXPECT_EQ(test_1.comp,"D+1");
  EXPECT_EQ(test_1.jump,"");


  // Test 2
  EXPECT_EQ(test_2.dest,"M");
  EXPECT_EQ(test_2.comp,"D");
  EXPECT_EQ(test_2.jump,"");



  // Test 3
  EXPECT_EQ(test_3.dest,"");
  EXPECT_EQ(test_3.comp,"0");
  EXPECT_EQ(test_3.jump,"JMP");


  // Test 4
  EXPECT_EQ(test_4.dest,"D");
  EXPECT_EQ(test_4.comp,"D-1");
  EXPECT_EQ(test_4.jump,"JMP");

}
