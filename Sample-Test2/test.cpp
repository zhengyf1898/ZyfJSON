#include "pch.h"
#include"E:\\ZyfJSON\\ZyfJSON\\JSON.h"
#include <gtest/gtest.h>
#include <string>

#define testLiteral(value, expect)     \
  do                                   \
  {                                    \
    JsonStr literal;                   \
    Parser p(value, &literal);         \
    EXPECT_EQ(p.parse(), expect);      \
  } while (0)


#define testNumber(expect, value)       \
  do                                    \
  {                                     \
    JsonNum num;                        \
    Parser p(value, &num);              \
	p.parse();                          \
    double n;                           \
    num.getdata(n);                     \
    EXPECT_EQ(n, expect);               \
  } while (0)

#define testString(expect, value)       \
  do                                    \
  {                                     \
    JsonStr str;                        \
    Parser p(value, &str);              \
	p.parse();                          \
    string s;                           \
    str.getdata(s);                     \
    EXPECT_EQ(s, expect);               \
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

TEST(RoundTrip, string) {
	testString("", "\"\"");
	testString("Hello", "\"Hello\"");
	testString("Hello\nWorld", "\"Hello\\nWorld\"");
	testString("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
	testString("\x24", "\"\\u0024\"");
	testString("\xC2\xA2", "\"\\u00A2\"");
	testString("\xE2\x82\xAC", "\"\\u20AC\"");
	testString("\xF0\x9D\x84\x9E", "\"\\uD834\\uDD1E\"");
	testString("\xF0\x9D\x84\x9E", "\"\\ud834\\udd1e\"");
}

TEST(RoundTrip, array) {
	JsonArray arr;
	Parser p("[ null , false , true , \"abc\" , 456 ]", &arr);
	p.parse();

	string l;
	arr.data[0]->getdata(l);
	EXPECT_EQ(l, "null");
	arr.data[1]->getdata(l);
	EXPECT_EQ(l, "false");
	arr.data[2]->getdata(l);
	EXPECT_EQ(l, "true");

	string s;
	arr.data[3]->getdata(s);
	EXPECT_EQ(s, "abc");

	double n;
	arr.data[4]->getdata(n);
	EXPECT_EQ(n, 456);
}