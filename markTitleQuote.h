#pragma once

#include "markListTable.h"


// 行内标记
std::vector<Token> markdownParser::markInline(const std::string& line) {
	std::vector<Token> tokens;
	Token tokenText(TokenType::TEXT);
	tokenText.content = line;

	tokens.push_back(tokenText);

	return tokens;
}

//	标题标记
Token markdownParser::markTitle(const std::string& line) {
	Token tokenTitle(TokenType::TITLE);			//	标题 Token
	Token tokenPara(TokenType::PARAGRAPH);		//	段落 Token
	int pos = 0;								//	当前字符位置
	int count = 0;								//	统计 '#' 个数
	bool isTitle = true;						//	判断 Token 是否为 title

	while (pos < line.length() && line[pos] == '#') {
		pos += 1;
		count += 1;
	}

	if (line[pos] == ' ') {
		switch (count) {
		case 1:
			tokenTitle.level = 1;
			break;
		case 2:
			tokenTitle.level = 2;
			break;
		case 3:
			tokenTitle.level = 3;
			break;
		case 4:
			tokenTitle.level = 4;
			break;
		case 5:
			tokenTitle.level = 5;
			break;
		case 6:
			tokenTitle.level = 6;
			break;
		default:
			isTitle = false;
		}
	}
	else
		isTitle = false;

	if (isTitle) {
		if(pos + 1 < line.length())				//	防止.substr() 函数溢出
			tokenTitle.children = markInline(line.substr(pos + 1));
		return tokenTitle;
	}
	else {
		if (pos + 1 < line.length())
			tokenPara.children = markInline(line.substr(pos + 1));
		return tokenPara;
	}
}

// 引用标记
Token markdownParser::markQuote(const std::string& line) {
	Token tokenQuote(TokenType::QUOTE);			//	引用 Token
	Token tokenPara(TokenType::PARAGRAPH);		//	段落 Token
	int pos = 0;								//	当前字符位置
	int count = 0;								//	统计 '>' 个数
	bool isQuote = true;						//	判断 Token 是否为 quote


	while (pos < line.length() && line[pos] == '>') {
		pos += 1;
		count += 1;
	}

	switch (count) {
	case 1:
		tokenQuote.level = 1;
		break;
	case 2:
		tokenQuote.level = 2;
		break;
	case 3:
		tokenQuote.level = 3;
		break;
	default:
		isQuote = false;
	}

	if (isQuote) {
		if (pos < line.length())				//	防止.substr() 函数溢出
			tokenQuote.children = markInline(line.substr(pos));
		return tokenQuote;
	}
	else {
		if (pos < line.length())				//	防止.substr() 函数溢出
			tokenPara.children = markInline(line.substr(pos));
		return tokenPara;
	}
}