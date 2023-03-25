#include<iostream>

#include"stack.h"

std::string mark_block(std::string block)
{
    int i = 0;        // 表示当前字符位置
    int s = 0, c = 0; // 分别表示上一个非空格字符位置/目前统计的符号数
                      // s变量主要用在换行符标记检测
    std::string s_re = "", temp = "";

    std::cout << block << std::endl;

    while (i < block.length() && block[i] == '#'){
        // 检测标题标记
        c += 1;
        temp += block[i];
        i += 1;
    }

    // 只有i=0(即首字符非'#')时继续
    // 否则继续向后检测
    if(i != 0){
        if(c == 1){
            return "<h1>";
        }else if(c == 2){
            return "<h2>";
        }else if(c == 3){
            return "<h3>";
        }else if(c == 4){
            return "<h4>";
        }else if(c == 5){
            return "<h5>";
        }else
            return "无此标题格式";
    }

    while (i < block.length() && block[i] == '>'){
        // 检测引用标记
        c += 1;
        temp += block[i];
        i += 1;
    }

    // 只有i=0(即上面字符未检测出)时退出
    // 否则继续向下检测
    if(i != 0){
        if(c == 1){
            return "引用1";
        }else if(c == 2){
            return "引用2";
        }else if(c == 3){
            return "引用3";
        }else
            return "引用格式错误";
    }

    while (i < block.length() && (block[i] == '*' || block[i] == '-' || block[i] == ' '))
    { //  检测换行符标记
        if (block[i] == ' ')
        { // 忽略空格
            temp += ' ';
            i += 1;
            continue;
        }

        c += 1; // 当前字符非空格

        if (c > 1){
            // 换行符应为同一的'*'或'-'
            if (block[i] != block[s]){
                temp += block[i];
                break;
            }else{
                temp += block[i];
                s = i;  // s标记当前字符位置
                i += 1; // 进入下一字符
            }
        }else{
            temp += block[i];
            s = i;  // s标记当前字符位置
            i += 1; // 进入下一字符
        }
    }


    // 如果这一行全为 '*' 或 '-' ，则为换行标记
    // 否则需要将其判定为文本格式化标记
    // 除非i=0,否则块元素判定到此结束
    if (i == block.length())
        return "<br>";
    else if (c == 2){
        return "斜体";
    }
    else if (c == 3){
        return "加粗";
    }
    else if (c == 4){
        return "斜体并加粗";
    }
    else
        return "前方视为正常文本处理";
}