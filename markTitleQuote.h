#include "markdownParser.h"


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
    Token tokenQuote(TokenType::QUOTE);			//	引用 Token
	Token tokenText(TokenType::TEXT);			//	文本 Token
	int pos = 0;								//	当前字符位置
	int count =0;								//	统计 '>' 个数
	bool isQuote = true;						//	判断 Token 是否为 quote

    while(pos < line.length() && line[pos] == '>'){
		pos   += 1;
		count += 1;
	}

    if(line[pos] == ' '){
		switch(count){
			case 1:
				tokenQuote.level = 1;
				break;
			case 2:
				tokenQuote.level = 2;
				break;
			case 3:
				tokenQuote.level = 3;
				break;
			default:
				isQuote = false;
		}
	}

    if(isQuote && pos+1 < line.length()){
		markInline(line.substr(pos+1));
	}else if(isQuote && pos+1 >= line.length()){
		return tokenQuote;
	}else{
		return tokenText;
	}
}