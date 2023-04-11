#include<fstream>

#include"markTitleQuote.h"


//  将 markdown 文本分解为Token
std::vector<Token> markdownParser::getTokens(const std::string &mdName){
    std::vector<Token> tokens;                          //  存放解析出的 Token
    std::string lineText;                               //  按行读取文件文本
	int countSpace = 0;									//	空格计数,用于列表层级
	int pos = 0;										//	字符定位,用于列表判定
	bool isOut = false;									//	用于列表检测退出标记
	bool isOrder = false;								//	用于判定是否为有序列表
	Token markMath(TokenType::MATH);					//	存放数学公式内容Token
	Token markCode(TokenType::CODE);					//	存放代码内容Token
	Token markTable(TokenType::TABLE);					//	存放表格Token
	Token markListOrder(TokenType::ListOrder);			//	存放有序列表Token
	Token markListUnorder(TokenType::ListUnordered);	//	存放无序列表Token

	std::ifstream mdFile(mdName);                       //	打开文件

	while (getline(mdFile, lineText))                   //	按行读取文件
	{
		pos 		= 0;
		countSpace 	= 0;
		isOut		= true;


		while(lineText[pos] == ' '){
			//	统计空格字符个数
			countSpace  += 1;
			pos 		+= 1;
		}

		if(lineText[pos] > '1' && lineText[pos] < '9'){
			if(lineText.substr(pos+1, 2) == ". "){
				parserState = parserStates::parserStateList;
				isOut = false;
				isOrder = true;
			}
		}else if(lineText.substr(pos, 2) == "* " || lineText.substr(pos, 2) == "- " || lineText.substr(pos, 2) == "+ "){
			parserState = parserStates::parserStateList;
			isOut = false;
			isOrder = false;
		}

		//	列表结束后一行
		//	解析器状态依旧为 parserStateList, 且 isOut = true
		//	此时需要将解析器状态调整为 parserStateOthers
		//	且需要将列表 Token 压入 vector，并清空列表 Token 内容
		if(isOut == true && parserState == parserStates::parserStateList){
			parserState = parserStates::parserStateOthers;
			tokens.push_back(markListOrder);
			if(isOrder){
				tokens.push_back(markListOrder);
			}
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
			}
			break;
		case parserStates::parserStateCode:
			markCode.content += lineText;
			break;
		case parserStates::parserStateMath:
			markMath.content += lineText;
			break;
		case parserStates::parserStateList:
			if(isOrder){
				markListOrder.content = lineText.substr(pos);
				markListOrder.level = (countSpace+1)/2;	//	空格数除以2 (向上取整)
				tokens.push_back(markListOrder);
				markListOrder.content = "";
				markListOrder.level = 0;
				parserState = parserStates::parserStateOthers;
			}else{
				markListUnorder.content = lineText.substr(pos);
				markListUnorder.level = (countSpace+1)/2;	//	空格数除以2 (向上取整)
				tokens.push_back(markListUnorder);
				markListUnorder.content = "";
				markListUnorder.level = 0;
				parserState = parserStates::parserStateOthers;
			}
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