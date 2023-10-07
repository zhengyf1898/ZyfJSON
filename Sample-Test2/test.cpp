#include "pch.h"
#include"E:\\ZyfJSON\\ZyfJSON\\JSON.h"
#include <gtest/gtest.h>
#include <string>


TEST(RoundTrip, literal)
{
	std::string t = " true ";
	Parser p(t);
	EXPECT_EQ(p.parse(), 0);
}