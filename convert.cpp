#include"syntaxTree.h"

std::string getMdFilename()
{
	// 输入需要处理的文件
	std::string mdFilename;

	std::cout << "# 输入.md文件名\n# 非当前目录下则需要带路径\n文件名：";
	while (std::cin >> mdFilename)
	{
		// 取输入的文件名后缀进行比较
		std::string temp = mdFilename.substr(mdFilename.length() - 3, mdFilename.length());
		if (temp != ".md")
		{
			system("clear");
			std::cout << "文件类型错误(应以.md结尾)" << std::endl;
			std::cout << "# 输入.md文件名\n# 非当前目录下则需要带路径\n文件名：";
		}
		else
			break;
	}
	system("clear");

	return mdFilename;
}

std::string getHtmlFilename()
{
	// 输入需要处理的文件
	std::string htmlFilename;

	std::cout << "# 输入.html文件名\n文件名：";
	while (std::cin >> htmlFilename)
	{
		// 取输入的文件名后缀进行比较
		std::string temp = htmlFilename.substr(htmlFilename.length() - 5, htmlFilename.length());
		if (temp != ".html")
		{
			system("clear");
			std::cout << "文件类型错误(应以.html结尾)" << std::endl;
			std::cout << "# 输入.html文件名\n文件名：";
		}
		else
			break;
	}
	system("clear");

	return htmlFilename;
}



int main(){
    Node           parserTree(NodeType::ROOT);  				//  markdown 语法树
    markdownParser mdParser;                    				//  获取解析器类
    std::string    mdFilename,htmlFilename;     				//  输入与输出文件名

    mdFilename   = getMdFilename();             				//  获取 markdown 文件名
    htmlFilename = getHtmlFilename();           				//  获取 html 文件名

    parserTree   = mdParser.parser(mdFilename); 				//  获取语法树

    return 0;
}