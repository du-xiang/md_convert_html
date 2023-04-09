#include<fstream>

#include"markdownParser.h"

// 行内标记
Token markdownParser::markInline(const std::string &line){
	Token tokenText(TokenType::TEXT);
	tokenText.content = line;

	return tokenText;
}

//	标题标记
Token markdownParser::markTitle(const std::string &line){
	Token tokenTitle(TokenType::TITLE);			//	标题 Token
	Token tokenText(TokenType::TEXT);			//	文本 Token
	int pos = 0;								//	当前字符位置
	int count =0;								//	统计 '#' 个数
	bool isTitle = true;						//	判断 Token 是否为 title

	while(pos < line.length() && line[pos] == '#'){
		pos   += 1;
		count += 1;
	}

	if(line[pos] == ' '){
		switch(count){
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

	if(isTitle && pos+1 < line.length()){
		markInline(line.substr(pos+1));
	}else if(isTitle && pos+1 >= line.length()){
		return tokenTitle;
	}else{
		return tokenText;
	}
}

// 引用标记
Token markdownParser::markQuote(const std::string &line){
	Token tokenQuote(TokenType::QUOTE);
}


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
			isMath = !isMath;
			if(markMath.content != ""){
				tokens.push_back(markMath);
				markMath.content = "";					//	清空 Math Token 内容
			}
		}else if(lineText.substr(0,3) == "```"){
			//	代码块
			isCode = !isCode;
			if(markCode.content != ""){
				tokens.push_back(markCode);
				markCode.content = "";					//	清空 Code Token 内容
			}
		}

		if(!isCode && !isMath){								//	判断是否处于多行解析状态
			if(lineText[0] == '#'){
				tokens.push_back(markTitle(lineText));
			}else if(lineText[0] == '>'){
				tokens.push_back(markTitle(lineText));
			}else if(lineText[0] >= '1' && lineText[0] <= '9'){

			}else if(lineText[0] == '+'){

			}else if(lineText[0] == '*' || lineText[0] == '-' || lineText[0] == ' '){

			}else ;
		}else if(isCode){
			markCode.content += lineText;
		}else if(isMath){
			markMath.content += lineText;
		}
	}

	mdFile.close();                                     // 关闭打开的文件

    return tokens;
}