#pragma once

#include"markTitleQuote.h"


//  将 markdown 文本分解为Token
std::vector<Token> markdownParser::getTokens(const std::string& mdName) {
	std::vector<Token> tokens{};                          //  存放解析出的 Token
	std::string lineText;                               //  按行读取文件文本
	bool isList = false;								//	是否处于列表解析状态
	bool isOrder = false;								//	列表是否为有序列表
	int pos = 0;										//	字符定位,用于列表判定
	int countSpace = 0;									//	列表前的空格字符数
	Token markWrap(TokenType::WRAP);					//	换行符Token
	Token markMath(TokenType::MATH);					//	存放数学公式内容Token
	Token markCode(TokenType::CODE);					//	存放代码内容Token
	Token markTable(TokenType::TABLE);					//	存放表格Token

	std::ifstream mdFile(mdName);                       //	打开文件

	while (getline(mdFile, lineText))                   //	按行读取文件
	{
		pos = 0;
		countSpace = 0;


		//	跳过空格字符并统计空格数量
		while (lineText[pos] == ' ') {
			pos += 1;
			countSpace += 1;
		}

		//	判定是否为列表解析器状态
		isList = false;
		//	有序列表
		if (lineText[pos] >= '1' && lineText[pos] <= '9' && lineText.substr(pos + 1, 2) == ". ") {
			isList = true;
			isOrder = true;
		}
		//	无序列表
		if (lineText.substr(pos, 2) == "* " || lineText.substr(pos, 2) == "- " || lineText.substr(pos, 2) == "+ ") {
			isList = true;
			isOrder = false;
		}
		
		if (isList)
			parserState = parserStates::parserStateList;

		//	判断是否为换行符
		//	需要注意的是换行符状态的检测需要在列表状态检测后
		//	因为有些换行符的前面部分字符与列表标记一样
		char ch		  = lineText[pos];					//	此行出现的除空格外第一个字符
		int countChar = 0;								//	统计出现的非空格字符数
		int posWrap	  = pos;							//	字符定位
		if (ch == '*' || ch == '-' || ch == ' ') {
			for (posWrap; posWrap < lineText.length(); posWrap++) {
				if (lineText[posWrap] == ch)
					countChar += 1;
				else if (lineText[posWrap] != ch && lineText[posWrap] != ' ')
					break;
			}
		}

		if (posWrap == lineText.length() && countChar >= 3 && lineText.length() != 0)
			parserState = parserStates::parserStateWrap;



		//	判定是否为多行数学公式或代码块
		if (lineText == "$$") {
			//	数学公式
			if (parserState == parserStates::parserStateMath) {
				tokens.push_back(markMath);
				markMath.content = "";					//	清空 Math Token 内容
				parserState = parserStates::parserStateOthers;
				continue;
			}
			else {
				parserState = parserStates::parserStateMath;
				continue;
			}

		}
		else if (lineText.substr(0, 3) == "```") {
			//	代码块
			if (parserState == parserStates::parserStateCode) {
				tokens.push_back(markCode);
				markCode.content = "";					//	清空 Code Token 内容
				parserState = parserStates::parserStateOthers;
				continue;
			}
			else {
				parserState = parserStates::parserStateCode;
				continue;
			}
		}

		switch(parserState){
		case parserStates::parserStateOthers:
			if(lineText[0] == '#'){
				tokens.push_back(markTitle(lineText));
			}else if(lineText[0] == '>'){
				tokens.push_back(markQuote(lineText));
			}else {
				if (lineText.length() != 0) {
					Token tokenPara(TokenType::PARAGRAPH);
					tokenPara.children = markInline(lineText);
					tokens.push_back(tokenPara);
				}
			}
			break;
		case parserStates::parserStateCode:
			markCode.content += (lineText+"\n");
			break;
		case parserStates::parserStateMath:
			markMath.content += (lineText+"\n");
			break;
		case parserStates::parserStateList:
			markList(tokens, lineText, pos, countSpace, isOrder);
			parserState = parserStates::parserStateOthers;
			break;
		case parserStates::parserStateTable:
			
			break;
		case parserStates::parserStateWrap:
			tokens.push_back(markWrap);
			parserState = parserStates::parserStateOthers;
			break;
		default:
			std::cout<<"解析器状态错误！"<<std::endl;
		}
	}

	mdFile.close();                                     // 关闭打开的文件
	return tokens;
}