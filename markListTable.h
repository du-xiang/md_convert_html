#pragma once

#include "markInlineFunc.h"

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


//	解析表格对齐格式
//	返回字符串 reAlign
//	字符串字符全为 '0'、'1'、'2'
//	'0'：左对齐、'1'：居中对齐、'2'：右对齐
std::string markdownParser::tableAlign(const std::string& line) {
	std::string reAlign;
	std::string reTemp = line;
	int pos = 0;
	int posSpace = 0;

	//	清除全部空格
	if (!reTemp.empty()){
		while ((posSpace = reTemp.find(' ', posSpace)) != std::string::npos){
			reTemp.erase(posSpace, 1);
		}
	}

	while (reTemp.find("|", pos+1) != std::string::npos) {
		if (reTemp[pos + 1] == ':') {
			if (reTemp[reTemp.find("|", pos + 1) - 1] == ':')
				reAlign += '1';
			else
				reAlign += '0';
		}
		else {
			if (reTemp[reTemp.find("|", pos + 1) - 1] == ':')
				reAlign += '2';
			else
				reAlign += '0';
		}

		if (reTemp.find("|", pos+1) < reTemp.length() - 1) {		//	防止溢出
			pos = reTemp.find("|", pos+1);
		}
		else
			break;
	}
	
	return reAlign;
}


//	将表格表头元素解析为 vector
std::vector<Token> markdownParser::markTableTh(const std::string& line) {
	std::vector<Token> reTokens;
	std::string strTemp;
	int pos = 1;

	while (line.find("|", pos) != std::string::npos) {
		Token td(TokenType::TH);

		strTemp = line.substr(pos, line.find("|", pos) - pos);

		//	先去除两端空格字符
		if (!strTemp.empty()) {
			strTemp.erase(0, strTemp.find_first_not_of(" "));
			strTemp.erase(strTemp.find_last_not_of(" ") + 1);
		}

		td.children = markInline(strTemp);
		reTokens.push_back(td);

		if (line.find("|", pos) < line.length() - 2) {		//	防止溢出
			pos = line.find("|", pos) + 1;
		}
		else
			break;
	}

	return reTokens;
}


//	将表格行元素解析为 vector
std::vector<Token> markdownParser::markTableTd(const std::string& line, const std::string& tableAlign) {
	std::vector<Token> reTokens;
	std::string strTemp;
	int pos = 1;
	int posAlign = 0;


	while (line.find("|", pos) != std::string::npos) {
		Token td(TokenType::TD);

		// 判定列元素的对齐格式
		td.content = tableAlign[posAlign];
		posAlign += 1;

		strTemp = line.substr(pos, line.find("|", pos) - pos);

		//	先去除两端的空格字符
		if (!strTemp.empty()){
			strTemp.erase(0, strTemp.find_first_not_of(" "));
			strTemp.erase(strTemp.find_last_not_of(" ") + 1);
		}
		
		td.children = markInline(strTemp);
		reTokens.push_back(td);

		if (line.find("|", pos) < line.length() - 2) {		//	防止溢出
			pos = line.find("|", pos) + 1;
		}
		else
			break;
	}

	return reTokens;
}


//	表格不能只用表头一行就确定(需要至少两行才可以)
//	当检测到表头时不能直接解析为表格Token
//	第一行需要先将其解析为 Paragraph Token 
//	但是需要在 level 标记为 1，并将string存放在content中
//	等下一行解析情况符合表格情况时再将 Paragraph Token 替换为表格 token
//	第二列可能带有每一列元素的对齐格式，格式就保存在表头元素中
//	
void markdownParser::markTable(std::vector<Token>& tokens, const std::string& line, std::string& strAlign) {
	if (tokens.size() != 0) {
		if (tokens.back().type == TokenType::TABLE) {
			Token tr(TokenType::TR);
			tr.children = markTableTd(line, strAlign);
			tokens.back().children.push_back(tr);
		}
		else if (tokens.back().type == TokenType::PARAGRAPH && tokens.back().level == 1) {
			Token tokenTable(TokenType::TABLE);
			Token tokenTr(TokenType::TR);
			tokenTr.children = markTableTh(tokens.back().content);
			strAlign = tableAlign(line);

			tokenTable.children.push_back(tokenTr);
			tokens.back() = tokenTable;
		}
		else {
			Token tokenPara(TokenType::PARAGRAPH, line, 1);
			tokenPara.children = markInline(line);
			tokens.push_back(tokenPara);
		}
	}
	else {
		Token tokenPara(TokenType::PARAGRAPH, line, 1);
		tokenPara.children = markInline(line);
		tokens.push_back(tokenPara);
	}
}