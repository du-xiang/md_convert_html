#include<fstream>

#include"markdownParser.h"
#include"markBlock.cpp"


// 将 markdown 文本解析为语法树
Node markdownParser::parser(const std::string &mdName){
    std::vector<Token> tokens = getTokens(mdName);       // 将文本解析为 Token
    Node root(NodeType::ROOT);                           // 创建语法树根节点
    syntaxTree(tokens, root);                            // 将 Token 转换为语法树
    return root;
}

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

//  将一系列 Token 转换为语法树
void syntaxTree(const std::vector<Token> &tokens, Node &parent){

}