#include<iostream>
#include<fstream>
#include<string>

int main(int argc, char* argv[]) {
	std::string s_file_md, s_file_html, s_line;

	// ������Ҫ������ļ�
	std::cout<<"# ����.md�ļ���\n# �ǵ�ǰĿ¼������Ҫ��·��\n�ļ�����";
	while(std::cin>>s_file_md){
        // ȡ������ļ�����׺���бȽ�
        std::string temp = s_file_md.substr(s_file_md.length() - 3, s_file_md.length());
		if(temp != ".md"){
            std::cout<<"�ļ����ʹ���(Ӧ��.md��β)"<<std::endl;
            std::cout<<"# ����.md�ļ���\n# �ǵ�ǰĿ¼������Ҫ��·��\n�ļ�����";
        }else break;
	}
	std::cout<<"\n"<<std::endl;

	std::cout<<"# ����.html�ļ���\n�ļ�����";
	while(std::cin>>s_file_html){
		// ȡ������ļ�����׺���бȽ�
        std::string temp = s_file_md.substr(s_file_md.length() - 5, s_file_md.length());
		if(temp != ".html"){
            std::cout<<"�ļ����ʹ���(Ӧ��.html��β)"<<std::endl;
            std::cout<<"# ����.html�ļ���\n�ļ�����";
        }else break;
	}
	std::cout<<"\n"<<std::endl;
	

	// ���ļ�
   	std::ifstream file_md(s_file_md);
	std::ofstream file_html(s_file_html);
    
   	while(getline(file_md,s_line)){


		   // �޸ĺ�����ı����뵽html�ļ���
		   file_html << s_line+'\n';
	}
 
   	// �رմ򿪵��ļ�
   	file_md.close();
   	file_html.close();

	return 0;
}