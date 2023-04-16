#pragma once

#include"syntaxHTML.h"

// 将 Token 转换为 HTML 字符串
std::string markdownParser::tokenToString(const Token& token) {
	std::string reString;							//	用于返回的字符串

	switch (token.type)
	{
	case TokenType::TITLE:
		reString = htmlTitle(token);
		break;
	case TokenType::QUOTE:
		reString = htmlQuote(token);
		break;
	case TokenType::TEXT:
		reString = token.content;
		break;
	case TokenType::CODE:
		reString = "<code>\n"+token.content+"</code>\n";
		break;
	case TokenType::MATH:
		reString = "<div class=\"math\">\n" + token.content + "</div>\n";
		break;
	case TokenType::PARAGRAPH:
		reString = htmlPara(token);
		break;
	case TokenType::LIST:
		reString = htmlList(token);
		break;
	case TokenType::LISTCELL:
		reString = htmlListCell(token);
		break;
	case TokenType::WRAP:
		reString = "<br>";
		break;
	case TokenType::TABLE:
		reString = htmlTable(token);
		break;
	case TokenType::TH:
		reString = htmlTh(token);
		break;
	case TokenType::TR:
		reString = htmlTr(token);
		break;
	case TokenType::TD:
		reString = htmlTd(token);
		break;
	case TokenType::BOLD:
		reString = htmlBold(token);
		break;
	case TokenType::ITALIC:
		reString = htmlItalic(token);
		break;
	case TokenType::DELET:
		reString = htmlDelete(token);
		break;
	case TokenType::IMAGE:
		reString = "<img src=\"" + token.content + "\">";
		break;
	case TokenType::LINK:
		reString = htmlLink(token);
		break;
	case TokenType::FOOTNOTE:
		reString = htmlFootnote(token);
		break;
	default:
		break;
	}

	return reString;
}

//  将一系列 Tokens 转换为 HTML 代码
void markdownParser::toHTML(const std::vector<Token>& tokens, const std::string& htmlName) {
	std::string htmlString;
	std::ofstream htmlFile(htmlName);                       //	打开文件
	
	htmlString += head;										//	添加 HTML 头部

	for (int i=0; i < tokens.size(); i++) {
		htmlString += tokenToString(tokens[i]);
	}

	htmlString += tail;										//	添加 HTML 尾部

	htmlFile << htmlString;									//	写入 .html 文件

	htmlFile.close();
}