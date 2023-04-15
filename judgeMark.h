#pragma once
#include "markdownParser.h"


bool markdownParser::isWrap(const std::string& line, const int& pos) {
	char ch = line[pos];					//	此行出现的除空格外第一个字符
	int countChar = 0;								//	统计出现的非空格字符数
	int posWrap = pos;							//	字符定位
	if (ch == '*' || ch == '-' || ch == ' ') {
		for (posWrap; posWrap < line.length(); posWrap++) {
			if (line[posWrap] == ch)
				countChar += 1;
			else if (line[posWrap] != ch && line[posWrap] != ' ')
				break;
		}
	}

	if (posWrap == line.length() && countChar >= 3 && line.length() != 0)
		return true;
	else
		return false;
}


bool markdownParser::isList(const std::string& line, const int& pos, bool& isOrder) {
	bool isList = false;

	//	有序列表
	if (line[pos] >= '1' && line[pos] <= '9' && line.substr(pos + 1, 2) == ". ") {
		isList = true;
		isOrder = true;
	}
	//	无序列表
	if (line.substr(pos, 2) == "* " || line.substr(pos, 2) == "- " || line.substr(pos, 2) == "+ ") {
		isList = true;
		isOrder = false;
	}

	if (isList)
		return true;
	else
		return false;
}


bool markdownParser::isTable(const std::string& line) {
	return false;
}