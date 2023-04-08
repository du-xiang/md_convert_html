#include<iostream>
#include<string>
#include<vector>

//  Token 类型定义
enum class TokenType{
    TEXT,   //  文本Token
    TITLE,  //  标题Token
    WRAP,   //  换行符Token
    QUOTE   //  引用Token
};

//  Toke 属性定义
typedef struct Token{
    TokenType type;              // Token 类型
    std::string content;         // Token 内容
    int level;                   // 标题级别
    std::vector<Token> children; // 子 Token(仅用于列表和表格)

    Token(TokenType t) : type(t), level(0) {}
};

// 语法树结点类型定义
enum class NodeType{
    ROOT, // 根节点
    TEXT, // 文本节点
    HEAD, // 标题节点
    PARA, // 段落节点
    LIST, // 列表节点
    TABLE // 表格节点
};

// 语法树属性定义
typedef struct Node{
    NodeType type;              // 节点类型
    std::string content;        // 节点内容（仅用于文本节点）
    int level;                  // 标题级别（仅用于标题节点）
    std::vector<Node> children; // 子节点

    Node(NodeType t) : type(t), level(0) {}
};



// markdown 解析器类
class markdownParser{
public:
    // 将 markdown 文本解析为语法树
    Node parser(const std::string &mdName, const std::string &htmlName);


private:
    bool isMultiLine = false;   // 是否处于多行标记检测

    // ************************************************
    //  getTokens()、syntaxTree() 用于实现 parser()
    // ************************************************

    //  将 markdown 文本分解为Token
    std::vector<Token> getTokens(const std::string &mdName);

    //  将一系列 Token 转换为语法树
    void syntaxTree(const std::vector<Token> &tokens, Node &parent);


    // ********************
    // 用于实现 getTokens() 
    // ********************

    // 检测标题标记
    Token markTitle(const std::string &line);

    // 检测引用标记
    Token markQuote(const std::string &line);

    // 检测行内标记
    Token markInline(const std::string &line);


    // ********************
    // 用于实现 syntaxTree()
    // ********************
    
};


// 将 markdown 文本解析为语法树
Node markdownParser::parser(const std::string &mdName, const std::string &htmlName){
    std::vector<Token> tokens = getTokens(mdName);       // 将文本解析为 Token
    Node root(NodeType::ROOT);                           // 创建语法树根节点
    syntaxTree(tokens, root);                            // 将 Token 转换为语法树
    return root;
}