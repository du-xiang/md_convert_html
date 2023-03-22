#include <iostream>
#include <fstream>
#include <string>

#include "stack.h"

std::string get_filename_md()
{
	// ������Ҫ������ļ�
	std::string s_file_md;

	std::cout << "# ����.md�ļ���\n# �ǵ�ǰĿ¼������Ҫ��·��\n�ļ�����";
	while (std::cin >> s_file_md)
	{
		// ȡ������ļ�����׺���бȽ�
		std::string temp = s_file_md.substr(s_file_md.length() - 3, s_file_md.length());
		if (temp != ".md")
		{
			system("clear");
			std::cout << "�ļ����ʹ���(Ӧ��.md��β)" << std::endl;
			std::cout << "# ����.md�ļ���\n# �ǵ�ǰĿ¼������Ҫ��·��\n�ļ�����";
		}
		else
			break;
	}
	system("clear");

	return s_file_md;
}

std::string get_filename_html()
{
	// ������Ҫ������ļ�
	std::string s_file_html;

	std::cout << "# ����.html�ļ���\n�ļ�����";
	while (std::cin >> s_file_html)
	{
		// ȡ������ļ�����׺���бȽ�
		std::string temp = s_file_html.substr(s_file_html.length() - 5, s_file_html.length());
		if (temp != ".html")
		{
			system("clear");
			std::cout << "�ļ����ʹ���(Ӧ��.html��β)" << std::endl;
			std::cout << "# ����.html�ļ���\n�ļ�����";
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

	// ��ȡ�ļ���
	s_file_md = get_filename_md();
	s_file_html = get_filename_html();

	// ���ļ�
	std::ifstream file_md(s_file_md);
	std::ofstream file_html(s_file_html);

	while (getline(file_md, s_line))
	{

		// �޸ĺ�����ı����뵽html�ļ���
		file_html << s_line + '\n';
	}

	// �رմ򿪵��ļ�
	file_md.close();
	file_html.close();

	return 0;
}