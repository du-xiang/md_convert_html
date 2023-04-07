#include<fstream>

#include"markdownParser.h"
#include"markBlock.cpp"


//  将 markdown 文本分解为Token
std::vector<Token> getTokens(const std::string &mdName){
    std::vector<Token> tokens;                          //  存放解析出的 Token
    std::string lineText;                               //  按行读取文件文本

	std::ifstream mdFile(mdName);                       // 打开文件

	while (getline(mdFile, lineText))                   // 按行读取文件
	{

	}

	mdFile.close();                                     // 关闭打开的文件

    return tokens;
}