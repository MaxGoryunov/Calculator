#pragma once

#include <string>

class StringUtils {
public:
	static bool isDigit(std::string const& token) {
		return token >= "0" && token <= "9";
	}

	static bool isLetter(std::string const& token) {
		return (token >= "A" && token <= "Z") || (token >= "a" && token <= "z");
	}

	static bool isNumber(std::string const& token);

	static bool isWord(std::string const& word);
};