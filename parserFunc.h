#include"markdownParser.h"

// 将 markdown 文本解析为语法树
Node markdownParser::parser(const std::string &markdown){
    std::vector<Token> tokens = getTokens(markdown);     // 将文本解析为 Token
    Node root(NodeType::ROOT);                           // 创建语法树根节点
    syntaxTree(tokens, root);                            // 将 Token 转换为语法树
    return root;
}

//  将 markdown 文本分解为Token
std::vector<Token> getTokens(const std::string &markdown){
    std::vector<Token> tokens;      //  存放解析出的 Token


    return tokens;
}

//  将一系列 Token 转换为语法树
void syntaxTree(const std::vector<Token> &tokens, Node &parent){

}