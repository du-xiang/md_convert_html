#include<iostream>

#include"stack.h"

std::string mark_inline(std::string s)
{
    int i = 0;
    Stack st;
    std::string s_re, temp;
    while (i < s.length())
    {
        if (s[i] == '*' || s[i] == '_')
        { // '*'和'_'在行内都是代表着相同的字体格式
            temp += s[i];
            i += 1;
            if (i < s.length() && (s[i] == '*' || s[i] == '_'))
            {
                temp += s[i];
                i += 1;
                if (i < s.length() && (s[i] == '*' || s[i] == '_'))
                {
                    temp += s[i];
                    if (st.top->s != "***" && st.top->s != "___")
                    {
                        s_re = s_re + "<strong><i>";
                        st.pushStack(temp);
                        temp = "";
                    }
                    else
                    {
                        s_re = s_re + "</i></strong>";
                        st.popStack();
                        temp = "";
                    }
                    i += 1;
                }
                else
                {
                    if (st.top->s != "**" && st.top->s != "__")
                    {
                        s_re = s_re + "<strong>" + s[i];
                        st.pushStack(temp);
                        temp = "";
                    }
                    else
                    {
                        s_re = s_re + "</strong>" + s[i];
                        st.popStack();
                        temp = "";
                    }
                    i += 1;
                }
            }
            else
            {
                if (st.top->s != "*" && st.top->s != "_")
                {
                    s_re = s_re + "<i>" + s[i];
                    st.pushStack(temp);
                    temp = "";
                }
                else
                {
                    s_re = s_re + "</i>" + s[i];
                    st.popStack();
                    temp = "";
                }
                i += 1;
            }
        }
        else if (s[i] == '~')
        { // 匹配删除标记
            temp += s[i];
            i += 1;
            if (i < s.length() && s[i] == '~')
            {
                temp += s[i];
                i += 1;
                if (st.top->s != "~~")
                {
                    st.pushStack(temp);
                    s_re += "<del>";
                    temp = "";
                }
                else
                {
                    s_re += "</del>";
                    st.popStack();
                    temp = "";
                }
            }
            else
            {
                s_re = s_re + temp + s[i];
                i += 1;
            }
        }
        else if(s[i]=='['){
            // 匹配脚注和地址
            temp+=s[i];
            i+=1;
            if(i<s.length() && s[i]=='^'){
                
            }
        }else
        {
            s_re += s[i];
            i += 1;
        }
    }

    return s_re;
}

std::string mark_block(std::string block){
    int i = 0;          // 表示当前字符位置
    int s = 0, c = 0;   // 分别表示上一个非空格字符位置/目前统计的符号数
                        // s, c变量主要用在换行符标记检测
    std::string s_re="", temp="";

    std::cout<<block<<std::endl;

    while (i < block.length())
    {
        while (block[i] == '*' || block[i] == '-' || block[i] == ' ')
        {   //  检测换行符标记
            if (block[i] == ' ')
            { // 忽略空格
                i += 1;
                continue;
            }

            c += 1; // 当前字符非空格

            if (i != 0 && s != 0)
            { //换行符应为同一的'*'或'-'
                if (block[i] != block[s])
                {
                    temp += block[i];
                    break;
                }
            }
            else
            {
                i+=1;
            }
            if(s==0)
                s = i;    // 把s置为当前位置
            else
                s = i-1;
        }
        std::cout<<i<<","<<s<<","<<c<<std::endl;
        if(i==block.length())
            return "<br>";
        else return temp;

    }

    return temp;
}