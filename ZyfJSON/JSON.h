#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include<ctype.h>

using namespace std;

enum {
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EXPECT_VALUE,
	LEPT_PARSE_INVALID_VALUE,
	LEPT_PARSE_ROOT_NOT_SINGULAR
};

class Parser {
public:
	Parser(std::string content) : content_(content) {
		start_ = content_.begin();
		curr_ = content_.begin();
	}

	int parse() {

		int res = 0;
		parseWhitespace();
		if ((res = parseValue()) == LEPT_PARSE_OK) {
			parseWhitespace();
			if (*curr_ != '\0')
				return LEPT_PARSE_ROOT_NOT_SINGULAR;
		}
		
		return res;
	}

	double getParseNum() { return val; }

private:

	void parseWhitespace() {
		try {
			while (*curr_ == ' ' || *curr_ == '\t' || *curr_ == '\n' || *curr_ == '\r')
				curr_++;
		}
		catch(...){
			start_ = curr_;
		}
	}

	int parseValue() {
		switch (*curr_) {
			case 'n':
				return parseLiteral("null");
			case 't':
				return parseLiteral("true");
			case 'f':
				return parseLiteral("false");
			case '\0':
				return LEPT_PARSE_EXPECT_VALUE;
			default:
				return parseNumber();
		}
	}
	int parseNumber() {
		if (*curr_ == '-')
			++curr_;
		if (*curr_ == '0')
			++curr_;
		else
		{
			if (!isdigit(*curr_))
				return LEPT_PARSE_INVALID_VALUE;
			while (isdigit(*++curr_))
				;
		}
		if (*curr_ == '.')
		{
			if (!isdigit(*++curr_))
				return LEPT_PARSE_INVALID_VALUE;
			while (isdigit(*++curr_))
				;
		}
		if (toupper(*curr_) == 'E')
		{
			++curr_;
			if (*curr_ == '-' || *curr_ == '+')
				++curr_;
			if (!isdigit(*curr_))
				return LEPT_PARSE_INVALID_VALUE;
			while (isdigit(*++curr_))
				;
		}
		val = strtod(&*start_, nullptr);
		start_ = curr_;
		return LEPT_PARSE_OK;
	}

	int parseLiteral(const std::string &literal) {
		for (int i = 0; literal[i]; i++, curr_++) {
			if (*curr_ != literal[i])
				return LEPT_PARSE_INVALID_VALUE;
		}
		start_ = curr_;
		return LEPT_PARSE_OK;
	}
	string::iterator start_;
	string::iterator curr_;
	string content_;
	double val;
};

