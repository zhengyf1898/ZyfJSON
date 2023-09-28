#pragma once
#include <iostream>
#include <string>

using namespace std;

class Parser {
public:
	Parser(const std::string& content) : start_(content.begin()), curr_(content.begin()) {}
private:
	string::const_iterator start_;
	string::const_iterator curr_;
	void parseWhitespace() {
		while (*curr_ == ' ' || *curr_ == '\t' || *curr_ == '\n' || *curr_ == '\r') {
			curr_++;
		}
		start_ = curr_;
	}
	void parseValue() {
		switch (*curr_) {
			case 'n':
				return parseLiteral("null");
			case 't':
				return parseLiteral("true");
			case 'f':
				return parseLiteral("false");
		}

	}
};

