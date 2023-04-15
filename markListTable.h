#pragma once

#include"markdownParser.h"

void markdownParser::markList(std::vector<Token>& tokens, const std::string& line, const int& pos, const int& countSpace, const bool& isOrder) {
	Token tokenListCell(TokenType::LISTCELL);			//	创建列表 cell token 存放列表信息
	tokenListCell.children = markInline(line.substr(pos + 2));

	//	tokens为空、tokens 最后一个 TokenType 不是 LIST、当前空格数小于 LIST 空格数
	//	以上三种情况需要新建一个 LIST 并将 tokenListCell 插入其中
	//	
	if (tokens.size() != 0) {
		Token* lastTokenPtr = &(tokens.back());			//	指向vector最后一个token
		std::vector<Token>* tokensPtr = &(tokens);
		//	token 类型不为列表，或LIST空格数大于等于当前列表空格数
		while (lastTokenPtr->level < countSpace && lastTokenPtr->type == TokenType::LIST) {
			tokensPtr = &(lastTokenPtr->children);
			lastTokenPtr = &(lastTokenPtr->children.back());
		}

		if (lastTokenPtr->type != TokenType::LIST) {
			Token tokenTemp(TokenType::LIST, isOrder ? "1" : "0", countSpace);

			tokenTemp.children.push_back(tokenListCell);
			tokensPtr->push_back(tokenTemp);
		}
		else {
			//	判断 LIST 和 LISTCELL 的有无序状态是否一致
			if ((lastTokenPtr->content == "1") == isOrder) {
				tokensPtr->back().children.push_back(tokenListCell);
			}
			else {
				Token tokenTemp(TokenType::LIST, isOrder ? "1" : "0", countSpace);

				tokenTemp.children.push_back(tokenListCell);
				tokensPtr->push_back(tokenTemp);
			}
		}
	}
	else {
		Token tokenTemp(TokenType::LIST, isOrder ? "1" : "0", countSpace);

		tokenTemp.children.push_back(tokenListCell);
		tokens.push_back(tokenTemp);
	}
}