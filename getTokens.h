#include<fstream>

#include"markTitleQuote.h"


//  将 markdown 文本分解为Token
std::vector<Token> markdownParser::getTokens(const std::string &mdName){
    std::vector<Token> tokens;                          //  存放解析出的 Token
    std::string lineText;                               //  按行读取文件文本
	Token markMath(TokenType::MATH);					//	存放数学公式内容Token
	Token markCode(TokenType::CODE);					//	存放代码内容Token

	std::ifstream mdFile(mdName);                       //	打开文件

	while (getline(mdFile, lineText))                   //	按行读取文件
	{
		if(lineText == "$$"){
			//	数学公式
			if(parserState == ParserStates::ParserStateMath){
				tokens.push_back(markMath);
				markMath.content = "";					//	清空 Math Token 内容
			}else parserState = ParserStates::ParserStateMath;

		}else if(lineText.substr(0,3) == "```"){
			//	代码块
			if(parserState == ParserStates::ParserStateCode){
				tokens.push_back(markCode);
				markCode.content = "";					//	清空 Code Token 内容
			}
			
		}

		switch(parserState){
		case ParserStates::ParserStateOthers:			//	判断是否处于多行解析状态
			if(lineText[0] == '#'){
				tokens.push_back(markTitle(lineText));
			}else if(lineText[0] == '>'){
				tokens.push_back(markTitle(lineText));
			}else if(lineText[0] >= '1' && lineText[0] <= '9'){

			}else if(lineText[0] == '+'){

			}else if(lineText[0] == '*' || lineText[0] == '-' || lineText[0] == ' '){

			}else ;
			break;
		case ParserStates::ParserStateCode:
			markCode.content += lineText;
			break;
		case ParserStates::ParserStateMath:
			markMath.content += lineText;
			break;
		default:
			std::cout<<"解析器状态错误！"<<std::endl;
		}
	}

	mdFile.close();                                     // 关闭打开的文件

    return tokens;
}