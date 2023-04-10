#include<fstream>

#include"markTitleQuote.h"


//  将 markdown 文本分解为Token
std::vector<Token> markdownParser::getTokens(const std::string &mdName){
    std::vector<Token> tokens;                          //  存放解析出的 Token
    std::string lineText;                               //  按行读取文件文本
	int countSpace = 0;									//	空格计数,用于列表层级
	int pos = 0;										//	字符定位,用于列表判定
	Token markMath(TokenType::MATH);					//	存放数学公式内容Token
	Token markCode(TokenType::CODE);					//	存放代码内容Token
	Token markList(TokenType::LIST);					//	存放列表Token
	Token markTable(TokenType::TABLE);					//	存放表格Token

	std::ifstream mdFile(mdName);                       //	打开文件

	while (getline(mdFile, lineText))                   //	按行读取文件
	{
		pos 		= 0;
		countSpace 	= 0;

		while(lineText[pos] == ' '){
			//	统计空格字符个数
			countSpace  += 1;
			pos 		+= 1;
		}

		if(lineText[pos] > '1' && lineText[pos] < '9'){
			if(lineText.substr(pos+1, 2) == ". "){

			}
		}else if(lineText.substr(pos, 2) == "* "){
			
		}

		if(lineText == "$$"){
			//	数学公式
			if(parserState == parserStates::parserStateMath){
				tokens.push_back(markMath);
				markMath.content = "";					//	清空 Math Token 内容
				parserState = parserStates::parserStateOthers;	
			}else 
				parserState = parserStates::parserStateMath;

		}else if(lineText.substr(0,3) == "```"){
			//	代码块
			if(parserState == parserStates::parserStateCode){
				tokens.push_back(markCode);
				markCode.content = "";					//	清空 Code Token 内容
				parserState = parserStates::parserStateOthers;
			}else
				parserState = parserStates::parserStateCode;
		}

		switch(parserState){
		case parserStates::parserStateOthers:
			if(lineText[0] == '#'){
				tokens.push_back(markTitle(lineText));
			}else if(lineText[0] == '>'){
				tokens.push_back(markTitle(lineText));
			}else if(lineText[0] >= '1' && lineText[0] <= '9'){

			}else if(lineText[0] == '+'){

			}else if(lineText[0] == '*' || lineText[0] == '-' || lineText[0] == ' '){

			}else ;
			break;
		case parserStates::parserStateCode:
			markCode.content += lineText;
			break;
		case parserStates::parserStateMath:
			markMath.content += lineText;
			break;
		case parserStates::parserStateList:

			break;
		case parserStates::parserStateTable:

			break;
		default:
			std::cout<<"解析器状态错误！"<<std::endl;
		}
	}

	mdFile.close();                                     // 关闭打开的文件

    return tokens;
}