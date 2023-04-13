#pragma once

#include"markdownParser.h"

Token markdownParser::markList(const std::string& line, const int& countSpace, const bool& isOrder) {
	Token tokenList(TokenType::LIST, "1");

	if (!isOrder)
		tokenList.content = "0";							//	token 类型更改为无序列表
	
	tokenList.level = countSpace;							//	level 参数用来记录空格数
	if (tokenList.content == "0") {
		if (line.length() > 2)
			tokenList.children = markInline(line.substr(1));
	}
	else {
		if (line.length() > 3)
			tokenList.children = markInline(line.substr(2));
	}


	return tokenList;
}