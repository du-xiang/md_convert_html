#pragma once

#include "judgeMark.h"


// 行内标记
std::vector<Token> markdownParser::markInline(const std::string& line) {
	std::vector<Token> tokens;
	Token tokenText(TokenType::TEXT);
	tokenText.content = line;

	tokens.push_back(tokenText);

	return tokens;
}