#include "pch.h"
#include"E:\\ZyfJSON\\ZyfJSON\\JSON.h"
#include <gtest/gtest.h>
#include <string>

#define testLiteral(value, expect)     \
  do                                   \
  {                                    \
    Parser p(value);                   \
    EXPECT_EQ(p.parse(), expect);      \
  } while (0)


#define testNumber(expect, value)       \
  do                                    \
  {                                     \
    Parser p(value);                    \
	p.parse();                          \
    EXPECT_EQ(p.getParseNum(), expect); \
  } while (0)

TEST(RoundTrip, literal)
{
	testLiteral("true", 0);
	testLiteral("false", 0);
	testLiteral("null", 0);

};

TEST(RoundTrip, number)
{

	testNumber(0.0, "0");
	testNumber(0.0, "-0");
	testNumber(0.0, "-0.0");
	testNumber(1.0, "1");
	testNumber(-1.0, "-1");
	testNumber(1.5, "1.5");
	testNumber(-1.5, "-1.5");
	testNumber(3.1416, "3.1416");
	testNumber(1E10, "1E10");
	testNumber(1e10, "1e10");
	testNumber(1E+10, "1E+10");
	testNumber(1E-10, "1E-10");
	testNumber(-1E10, "-1E10");
	testNumber(-1e10, "-1e10");
	testNumber(-1E+10, "-1E+10");
	testNumber(-1E-10, "-1E-10");
	testNumber(1.234E+10, "1.234E+10");
	testNumber(1.234E-10, "1.234E-10");
	testNumber(5.0E-324, "5e-324");
	testNumber(0, "1e-10000");
	testNumber(1.0000000000000002, "1.0000000000000002");
	testNumber(4.9406564584124654e-324, "4.9406564584124654e-324");
	testNumber(-4.9406564584124654e-324, "-4.9406564584124654e-324");
	testNumber(2.2250738585072009e-308, "2.2250738585072009e-308");
	testNumber(-2.2250738585072009e-308, "-2.2250738585072009e-308");
	testNumber(2.2250738585072014e-308, "2.2250738585072014e-308");
	testNumber(-2.2250738585072014e-308, "-2.2250738585072014e-308");
	testNumber(1.7976931348623157e+308, "1.7976931348623157e+308");
	testNumber(-1.7976931348623157e+308, "-1.7976931348623157e+308");

};