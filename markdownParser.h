#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

//  Token 类型定义
enum class TokenType {
    BOLD,           //  文本加粗Token
    ITALIC,         //  文本斜体Token
    DELET,          //  文本删除线Token
    FOOTNOTE,       //  脚注Token
    LINK,           //  超链接Token
    IMAGE,          //  图片Token
    TEXT,           //  文本Token
    TITLE,          //  标题Token
    TABLE,          //  表格Token
    TH,             //  表格表头Token
    TR,             //  表格行元素
    TD,             //  表格行元素中的列元素
    WRAP,           //  换行符Token
    QUOTE,          //  引用Token
    CODE,           //  代码Token
    MATH,           //  数学公式Token
    PARAGRAPH,      //  段落Token
    LIST,           //  列表Token
    LISTCELL        //  列表元素Token
};

//  Toke 属性定义
struct Token {
    TokenType type;              // Token 类型
    std::string content;         // Token 内容
    int level;                   // 级别(标题、列表)
    std::vector<Token> children; // 子 Token(仅用于列表和表格)

    Token(TokenType t) : type(t), level(0) {}
    Token(TokenType t, std::string s):type(t), content(s), level(0){}
    Token(TokenType t, int l) :type(t), level(l) {}
    Token(TokenType t, std::string s, int l) :type(t), content(s), level(l) {}
};


//  定义解析器状态
//  用于区分代码块、数学公式、列表
enum class parserStates {
    parserStateOthers,          //  解析器状态：除下面几种之外其他
    parserStateMath,            //  解析器状态：多行数学公式
    parserStateCode,            //  解析器状态：代码块
    parserStateList,            //  解析器状态：列表
    parserStateTable,           //  解析器状态：表格
    parserStateWrap             //  解析器状态：换行符
};


// markdown 解析器类
class markdownParser {
public:
    //  解析器状态初始化为 parserStateOthers
    markdownParser() :parserState(parserStates::parserStateOthers) {}

    // 将 markdown 文本解析为语法树
    void parser(const std::string& mdName, const std::string& htmlName);


private:
    parserStates parserState;                           //  解析器状态

    // ************************************************
    //  getTokens()、syntaxTree() 用于实现 parser()
    // ************************************************

    //  将 markdown 文本分解为Token
    std::vector<Token> getTokens(const std::string& mdName);

    //  将一系列 Token 转换为 HTML 代码
    void toHTML(const std::vector<Token>& tokens, const std::string &htmlFilename);


    // ********************
    // 用于实现 getTokens() 
    // ********************

    //  检测标题标记
    Token markTitle(const std::string& line);

    //  检测引用标记
    Token markQuote(const std::string& line);

    //  判断是否为列表标记
    bool isList(const std::string& line, const int& pos, bool& isOrder);

    //  检测列表标记
    void markList(std::vector<Token>& tokens, const std::string& line, const int& pos, const int& countSpace, const bool& isOrder);

    //  判断是否为换行符标记
    bool isWrap(const std::string& line, const int& pos);

    //  判断是否为表格标记
    bool isTable(const std::string& line);

    //  检测表格标记
    void markTable(std::vector<Token>& tokens, const std::string& line, std::string& tableAlign);

    //  表格对齐方式检测
    std::string tableAlign(const std::string& line);

    //  检测表格表头元素标记
    std::vector<Token> markTableTh(const std::string& line);

    //  检测表格行元素标记
    std::vector<Token> markTableTd(const std::string& line, const std::string& tableAlign);

    //  检测行内标记
    std::vector<Token> markInline(const std::string& line);


    // ********************
    // 用于实现 toHTML()
    // ********************

    //  将 Tokens 转换为 html 字符串
    std::string tokenToString(const Token& token);

    //  标题 Token
    std::string htmlTitle(const Token& token);

    //  引用 Token
    std::string htmlQuote(const Token& token);

    //  段落 Token
    std::string htmlPara(const Token& token);

    //  列表 Token
    std::string htmlList(const Token& token);

    //  列表元素 Token
    std::string htmlListCell(const Token& token);

    //  表格 Token
    std::string htmlTable(const Token& token);

    //  表格表头 Token
    std::string htmlTh(const Token& token);

    //  表格行元素 Token
    std::string htmlTr(const Token& token);

    // 表格行元素中的列元素 Token
    std::string htmlTd(const Token& token);

    //  文本加粗 Token
    std::string htmlBold(const Token& token);

    //  文本斜体 Token
    std::string htmlItalic(const Token& token);

    //  文本删除线 Token
    std::string htmlDelete(const Token& token);

    //  链接 Token
    std::string htmlLink(const Token& token);

    //  脚注 Token
    std::string htmlFootnote(const Token& token);


    //  ************************
    //  用于实现 markInline()  
    //  ************************

    //  实现行内标签选择
    TokenType inlineMarkSwitch(const std::string& line, const int& pos);

    //  行内标签：文本
    std::string inlineMarkText(const std::string& line, int& pos);

};


// 将 markdown 文本解析为语法树
void markdownParser::parser(const std::string& mdName, const std::string& htmlName) {
    std::vector<Token> tokens = getTokens(mdName);       // 将文本解析为 Token
    toHTML(tokens, htmlName);                            // 将 Token 转换为语法树
}