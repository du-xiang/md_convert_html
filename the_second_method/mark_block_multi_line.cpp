#include<iostream>


std::string mark_block_order_list(std::string str_ol){
    if(str_ol.substr(1, 2) == ". ")
        return "<li>"+str_ol.substr(3, str_ol.length()-3)+"</li>";
    else return str_ol;
}


std::string mark_block_unordered_list(std::string str_uol){
    if(str_uol[1] == ' ')
        return "<li>"+str_uol.substr(2, str_uol.length()-2)+"</li>";
    else return str_uol;
}