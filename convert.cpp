#include <iostream>
#include <fstream>
#include <string>

#include "stack.h"

std::string get_filename_md()
{
	// 输入需要处理的文件
	std::string s_file_md;

	std::cout << "# 输入.md文件名\n# 非当前目录下则需要带路径\n文件名：";
	while (std::cin >> s_file_md)
	{
		// 取输入的文件名后缀进行比较
		std::string temp = s_file_md.substr(s_file_md.length() - 3, s_file_md.length());
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

	return s_file_md;
}

std::string get_filename_html()
{
	// 输入需要处理的文件
	std::string s_file_html;

	std::cout << "# 输入.html文件名\n文件名：";
	while (std::cin >> s_file_html)
	{
		// 取输入的文件名后缀进行比较
		std::string temp = s_file_html.substr(s_file_html.length() - 5, s_file_html.length());
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

	return s_file_html;
}

int main(int argc, char *argv[])
{
	std::string s_file_md, s_file_html, s_line;

	// 获取文件名
	s_file_md = get_filename_md();
	s_file_html = get_filename_html();

	// 打开文件
	std::ifstream file_md(s_file_md);
	std::ofstream file_html(s_file_html);

	while (getline(file_md, s_line))
	{

		// 修改后的行文本输入到html文件中
		file_html << s_line + '\n';
	}

	// 关闭打开的文件
	file_md.close();
	file_html.close();

	return 0;
}