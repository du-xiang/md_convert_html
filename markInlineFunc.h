#pragma once

#include "judgeMark.h"


std::string markdownParser::inlineMarkText(const std::string& line, int& pos) {
	std::string strText;
	
	while (inlineMarkSwitch(line, pos) == TokenType::TEXT && line.length() > pos) {
		strText += line[pos];
		pos += 1;
	}

	return strText;
}


TokenType markdownParser::inlineMarkSwitch(const std::string& line, const int& pos) {
	std::string strTemp;
	
	//	防止溢出
	if (line.length() > pos+1)
		strTemp = line.substr(pos, 2);
	else
		strTemp = line.substr(pos, 1);
	
	if (line[pos] == '*' || line[pos] == '_')
		if (strTemp == "**" || strTemp == "__")
			return TokenType::BOLD;
		else
			return TokenType::ITALIC;
	else if (line[pos] == '[')
		if (strTemp == "[^")
			return TokenType::FOOTNOTE;
		else
			return TokenType::LINK;
	else if (strTemp == "~~")
		return TokenType::DELET;
	else if (strTemp == "![")
		return TokenType::IMAGE;
	else
		return TokenType::TEXT;
}

// 行内标记
std::vector<Token> markdownParser::markInline(const std::string& line) {
	std::vector<Token> tokens;
	//std::string buffer;									//	作为一个缓冲器存放非标记字符
	//std::vector<std::string> markStack;					//  使用一个 vector 作为一个栈使用(.push_back() or .pop_back())
	int pos = 0;

	while (pos < line.length()) {
		switch (inlineMarkSwitch(line, pos)) {
		case TokenType::TEXT: {
			Token tokenText(TokenType::TEXT);
			tokenText.content = inlineMarkText(line, pos);
			tokens.push_back(tokenText);
			break; }
		case TokenType::BOLD:
			if (line.find(line.substr(pos, 2), pos + 2) != std::string::npos) {
				Token tokenBold(TokenType::BOLD);
				int posTemp = line.find(line.substr(pos, 2), pos + 2);
				tokenBold.children = markInline(line.substr(pos + 2, posTemp - pos - 2));
				pos = posTemp + 2;
				tokens.push_back(tokenBold);
			}
			else {
				Token tokenText(TokenType::TEXT);
				pos += 2;
				tokenText.content = line.substr(pos, 2) + inlineMarkText(line, pos);
				tokens.push_back(tokenText);
			}
			break;
		case TokenType::ITALIC:
			if (line.find(line.substr(pos, 1), pos + 1) != std::string::npos) {
				Token tokenBold(TokenType::ITALIC);
				int posTemp = line.find(line.substr(pos, 1), pos + 1);
				tokenBold.children = markInline(line.substr(pos + 1, posTemp - pos - 1));
				pos = posTemp + 1;
				tokens.push_back(tokenBold);
			}
			else {
				Token tokenText(TokenType::TEXT);
				pos += 1;
				tokenText.content = line.substr(pos, 1) + inlineMarkText(line, pos);
				tokens.push_back(tokenText);
			}
			break;
		case TokenType::DELET:
			if (line.find(line.substr(pos, 2), pos + 2) != std::string::npos) {
				Token tokenDelete(TokenType::DELET);
				int posTemp = line.find(line.substr(pos, 2), pos + 2);
				tokenDelete.children = markInline(line.substr(pos + 2, posTemp - pos - 2));
				pos = posTemp + 2;
				tokens.push_back(tokenDelete);
			}
			else {
				Token tokenText(TokenType::TEXT);
				pos += 2;
				tokenText.content = line.substr(pos, 2) + inlineMarkText(line, pos);
				tokens.push_back(tokenText);
			}
			break;
		case TokenType::IMAGE:
			if (line.find("](", pos + 1) != std::string::npos || line.find(")", pos + 1) != std::string::npos) {
				Token tokenImage(TokenType::IMAGE);
				int posTemp = line.find("](", pos + 1);
				int posEnd = line.find(")", pos + 1);
				tokenImage.content = line.substr(posTemp + 2, posEnd - posTemp -2);
				pos = posEnd + 1;
				tokens.push_back(tokenImage);
			}
			else {
				Token tokenText(TokenType::TEXT);
				pos += 2;
				tokenText.content = line.substr(pos, 2) + inlineMarkText(line, pos);
				tokens.push_back(tokenText);
			}
			break;
		case TokenType::FOOTNOTE:
			if (line.find("]", pos + 1) != std::string::npos) {
				Token tokenFootnote(TokenType::FOOTNOTE);
				int posTemp = line.find("]", pos + 1);
				tokenFootnote.children = markInline(line.substr(pos + 2, posTemp - pos - 2));
				pos = posTemp + 1;
				tokens.push_back(tokenFootnote);
			}
			break;
		case TokenType::LINK:
			if (line.find("](", pos + 1) != std::string::npos || line.find(")", pos + 1) != std::string::npos) {
				Token tokenLink(TokenType::LINK);
				Token tokenText(TokenType::TEXT);
				int posTemp = line.find("](", pos + 1);
				int posEnd = line.find(")", pos + 1);
				tokenText.content = line.substr(pos + 1, posTemp - pos - 1);
				tokenLink.content = line.substr(posTemp + 2, posEnd - posTemp - 2);
				tokenLink.children.push_back(tokenText);
				pos = posEnd + 1;
				tokens.push_back(tokenLink);
			}
			else {
				Token tokenText(TokenType::TEXT);
				pos += 2;
				tokenText.content = line.substr(pos, 2) + inlineMarkText(line, pos);
				tokens.push_back(tokenText);
			}
			break;
		default:
			std::cout << "错误：行内解析类型错误！" << std::endl;
		}
	}

	return tokens;
}