#pragma once

#include"headTail.h"

std::string markdownParser::htmlTitle(const Token& token) {
	std::string reTitle;
	std::string parserContent;						//	存放子 Tokens 解析的内容

	for (int i = 0; i < token.children.size(); i++) {
		parserContent += tokenToString(token.children[i]);
	}

	switch (token.level)
	{
	case 1:
		reTitle = "<h1>" + parserContent + "</h1>";
		break;
	case 2:
		reTitle = "<h2>" + parserContent + "</h2>";
		break;
	case 3:
		reTitle = "<h3>" + parserContent + "</h3>";
		break;
	case 4:
		reTitle = "<h4>" + parserContent + "</h4>";
		break;
	case 5:
		reTitle = "<h5>" + parserContent + "</h5>";
		break;
	case 6:
		reTitle = "<h6>" + parserContent + "</h6>";
		break;
	default:
		break;
	}

	return reTitle+"\n";
}

std::string markdownParser::htmlQuote(const Token& token) {
	std::string reQuote;
	std::string parserContent;						//	存放子 Tokens 解析的内容

	for (int i = 0; i < token.children.size(); i++) {
		parserContent += tokenToString(token.children[i]);
	}

	switch (token.level)
	{
	case 1:
		reQuote = "<div class=\"quote_1\">" + parserContent + "</div>";
		break;
	case 2:
		reQuote = "<div class=\"quote_2\">" + parserContent + "</div>";
		break;
	case 3:
		reQuote = "<div class=\"quote_3\">" + parserContent + "</div>";
		break;
	default:
		break;
	}

	return reQuote+"\n";
}

std::string markdownParser::htmlPara(const Token& token) {
	std::string rePara;
	std::string parserContent;						//	存放子 Tokens 解析的内容

	for (int i = 0; i < token.children.size(); i++) {
		parserContent += tokenToString(token.children[i]);
	}

	rePara = "<p>" + parserContent + "</p>";

	return rePara + "\n";
}


std::string markdownParser::htmlList(const Token& token) {
	std::string reList;
	std::string parserContent;						//	存放子 Tokens 解析的内容


	for (int i = 0; i < token.children.size(); i++) {
		parserContent += tokenToString(token.children[i]);
	}

	if (token.content == "1") {
		reList = "<ol>\n<li>\n" + parserContent + "</li>\n</ol>";
	}else {
		reList = "<ul>\n<li>\n" + parserContent + "</li>\n</ul>";
	}

	return reList;
}