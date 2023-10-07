#pragma once
#include <iostream>
#include <string>

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
		res = parseValue();
		//parseWhitespace();
		return res;
	}

private:

	void parseWhitespace() {
		while (*curr_ == ' ' || *curr_ == '\t' || *curr_ == '\n' || *curr_ == '\r') {
			curr_++;
		}
		start_ = curr_;
	}
	int parseValue() {
		switch (*curr_) {
			case 'n':
				return parseLiteral("null");
			case 't':
				return parseLiteral("true");
			case 'f':
				return parseLiteral("false");
		}
	}

	int parseLiteral(const std::string &literal) {
		for (int i = 0; literal[i ]; i++, curr_++) {
			if (*curr_ != literal[i])
				return LEPT_PARSE_INVALID_VALUE;
		}
		start_ = curr_;
		return LEPT_PARSE_OK;
	}
	string::iterator start_;
	string::iterator curr_;
	string content_;
};

