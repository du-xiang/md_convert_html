#include<iostream>

#include "mark_block_multi_line.cpp"


std::string mark_block_h(std::string str_h){
    int i = 0;        // 表示当前字符位置
    int c = 0;        // 分别表示上一个非空格字符位置/目前统计的符号数

    while (i < str_h.length() && str_h[i] == '#'){
        // 检测标题标记
        c += 1;
        i += 1;
    }

    // 标题标记最后字符应该为空格
    if(str_h[i] == ' '){
        i += 1;
        std::string str_text = str_h.substr(i, str_h.length()-i);

        // 判定标题格式
        if(c == 1){
            return "<h1>"+str_text+"</h1>";
        }else if(c == 2){
            return "<h2>"+str_text+"</h2>";
        }else if(c == 3){
            return "<h3>"+str_text+"</h3>";
        }else if(c == 4){
            return "<h4>"+str_text+"</h4>";
        }else if(c == 5){
            return "<h5>"+str_text+"</h5>";
        }else
            return str_h;
    }
    
}


std::string mark_block_quote(std::string str_q){
    int i = 0;        // 表示当前字符位置
    int c = 0;        // 分别表示上一个非空格字符位置/目前统计的符号数

    while (i < str_q.length() && str_q[i] == '>'){
        // 检测引用标记
        c += 1;
        i += 1;
    }

    // 去除字符串块标记
    std::string str_text = str_q.substr(i, str_q.length()-i);

    // 判定引用层级
    if(c == 1){
        return "<div class=\"quote_1\">"+str_text+"</div>";
    }else if(c == 2){
        return "<div class=\"quote_2\">"+str_text+"</div>";
    }else if(c == 3){
        return "<div class=\"quote_3\">"+str_text+"</div>";
    }else
        return str_q;
}


std::string mark_block_wrap(std::string str_w){
    int i = 0;        // 表示当前字符位置
    int s = 0, c = 0; // 分别表示上一个非空格字符位置/目前统计的符号数
                      // s变量主要用在换行符标记检测
    std::string re_str = "";

    while (i < str_w.length() && (str_w[i] == '*' || str_w[i] == '-' || str_w[i] == ' '))
    { //  检测换行符标记
        if (str_w[i] == ' ')
        { // 忽略空格
            re_str += ' ';
            i += 1;
            continue;
        }

        c += 1; // 当前字符非空格

        if (c > 1){
            // 换行符应为同一的'*'或'_'
            if (str_w[i] != str_w[s]){
                re_str += str_w[i];
                break;
            }else{
                re_str += str_w[i];
                s = i;  // s标记当前字符位置
                i += 1; // 进入下一字符
            }
        }else{
            re_str += str_w[i];
            s = i;  // s标记当前字符位置
            i += 1; // 进入下一字符
        }
    }


    // 换行标记判定
    if (i == str_w.length() && str_w.length() != 0)
        return "<br>";
    else return str_w;
}


std::string mark_block_wrap_or_unordered_list(std::string str_w){
    // 判断是换行标记还是无序列表标记
    int i = 0;  // 字符位置标志
    int s = 0;  // 统计前面连续的空格个数

    // 前面连续空格字符个数统计
    while(i < str_w.length() && str_w[i] == ' '){
        s += 1;
        i += 1;
    }

    // 去除标记
    // 为无序列表做准备
    std::string str_sub = str_w.substr(i, str_w.length()-i);
    std::string str_text = str_w.substr(i+2, str_w.length()-i);

    // 且第一个出现的非空格字符不为'*'或'-'，则判定为非块标记
    if(str_w[i] != '*' && str_w[i] != '-' && str_w[i] != '+'){
        return str_w;
    }else if(str_w[i+1] != ' ' || s%2 != 0){
        // 第一个'*'或'-'后无空格，或前面连续的空格非偶数
        // 则直接进行换行符标记判定
        return mark_block_wrap(str_sub);
    }else{
        // 前面标记符合无序列表的特征
        // 若此行不符合换行符标记
        // 则直接判定成无序列表
        if(mark_block_wrap(str_text) != "<br>"){
            // 非换行标记
            return "<li>"+str_text+"</li>";
        }else return "<br>";
    }
}


std::string mark_block(std::string block)
{
    // 对首字符进行判断
    // 是否符合块标记首字符
    if(block[0] == '#')
        return mark_block_h(block);
    else if(block[0] == '>')
        return mark_block_quote(block);
    else if(block[0] >= '1' && block[0] <= '9')
        return mark_block_order_list(block);
    else if(block[0] == '+')
        return mark_block_unordered_list(block);
    else if(block[0] == '*' || block[0] == '-' || block[0] == ' ')
        return mark_block_wrap_or_unordered_list(block);
    else return block;

}