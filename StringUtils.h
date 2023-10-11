#pragma once

#include <string>

using std::string;

class StringUtils {
public:
	static bool isIdent(string const& token) {
		return token >= "0" && token <= "9";
	}

	static bool isLetter(string const& token) {
		return token >= "A" && token <= "Z";
	}
};