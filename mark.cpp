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