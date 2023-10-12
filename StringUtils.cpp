#include "StringUtils.h"

using std::string;

bool StringUtils::isNumber(string const& token) {
	for (auto const& digit : token) {
		if (!(isDigit(string{ digit }) || digit == '.')) {
			return false;
		}
	}
	return true;
}

bool StringUtils::isWord(string const& word) {
	for (auto const& letter : word) {
		if (!isLetter(string{ letter })) {
			return false;
		}
	}
	return true;
}