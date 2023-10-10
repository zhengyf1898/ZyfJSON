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
	LEPT_PARSE_ROOT_NOT_SINGULAR,
	MISS_QUOTATION_MARK,
	INVALID_STRING_CHAR,
	INVALID_UNICODE_HEX,
	INVALID_UNICODE_SURROGATE,
	INVALID_STRING_ESCAPE
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

	string getParseStr() { return str; }

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
			case '\"':
				return parseRawString();
			case '\0':
				return LEPT_PARSE_EXPECT_VALUE;
			default:
				return parseNumber();
		}
	}
	int parseRawString() {
		while (1)
		{
			switch (*++curr_)
			{
			case '\"':
				start_ = ++curr_;
				return LEPT_PARSE_OK;
			case '\0':
				return MISS_QUOTATION_MARK;
			default:
				if (static_cast<unsigned char>(*curr_) < 0x20)
					return INVALID_STRING_CHAR;
				str.push_back(*curr_);
				break;
			case '\\':
				switch (*++curr_)
				{
				case '\"':
					str.push_back('\"');
					break;
				case '\\':
					str.push_back('\\');
					break;
				case '/':
					str.push_back('/');
					break;
				case 'b':
					str.push_back('\b');
					break;
				case 'f':
					str.push_back('\f');
					break;
				case 'n':
					str.push_back('\n');
					break;
				case 't':
					str.push_back('\t');
					break;
				case 'r':
					str.push_back('\r');
					break;
				case 'u':
				{
					unsigned u1 = parse4hex();
					if (u1 >= 0xd800 && u1 <= 0xdbff)
					{ // high surrogate
						if (*++curr_ != '\\')
							return INVALID_UNICODE_SURROGATE;
						if (*++curr_ != 'u')
							return INVALID_UNICODE_SURROGATE;
						unsigned u2 = parse4hex(); // low surrogate
						if (u2 < 0xdc00 || u2 > 0xdfff)
							return INVALID_UNICODE_SURROGATE;
						u1 = (((u1 - 0xd800) << 10) | (u2 - 0xdc00)) + 0x10000;
					}
					str += encodeUTF8(u1);
				}
				break;
				default:
					return INVALID_STRING_ESCAPE;
				}
				break;
			}
		}
	}

	string encodeUTF8(unsigned u) noexcept
	{
		string utf8;
		if (u <= 0x7F) // 0111,1111
			utf8.push_back(static_cast<char>(u & 0xff));
		else if (u <= 0x7FF)
		{
			utf8.push_back(static_cast<char>(0xc0 | ((u >> 6) & 0xff)));
			utf8.push_back(static_cast<char>(0x80 | (u & 0x3f)));
		}
		else if (u <= 0xFFFF)
		{
			utf8.push_back(static_cast<char>(0xe0 | ((u >> 12) & 0xff)));
			utf8.push_back(static_cast<char>(0x80 | ((u >> 6) & 0x3f)));
			utf8.push_back(static_cast<char>(0x80 | (u & 0x3f)));
		}
		else
		{
			utf8.push_back(static_cast<char>(0xf0 | ((u >> 18) & 0xff)));
			utf8.push_back(static_cast<char>(0x80 | ((u >> 12) & 0x3f)));
			utf8.push_back(static_cast<char>(0x80 | ((u >> 6) & 0x3f)));
			utf8.push_back(static_cast<char>(0x80 | (u & 0x3f)));
		}
		return utf8;
	}
	
	unsigned parse4hex()
	{
		unsigned u = 0;
		for (int i = 0; i != 4; ++i)
		{
			// now *curr_ = "uXXXX...."
			unsigned ch = static_cast<unsigned>(toupper(*++curr_));
			u <<= 4; // u *= 16
			if (ch >= '0' && ch <= '9')
				u |= (ch - '0');
			else if (ch >= 'A' && ch <= 'F')
				u |= ch - 'A' + 10;
			else
				return INVALID_UNICODE_HEX;
		}
		return u;
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
	string str;
	double val;
};

