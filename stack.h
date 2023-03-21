#include<iostream>

class Node{
public:
    std::string s;
    Node *ps_front;
    Node();
    Node(std::string);
    void showNode();
};

class Stack : public Node{
public:
    Node *top;
    Stack();
    void showStack();
    bool pushStack(std::string node_s);
    bool popStack();
    
};

// Node类功能函数

Node::Node(){
    s="";
    ps_front=NULL;
}

Node::Node(std::string in){
    s=in;
}

void Node::showNode(){
    std::cout<<s<<std::endl;
}

// Stack类功能函数

Stack::Stack(){
    Node *t = new Node;
    top = t;
}

void Stack::showStack(){
    std::cout<<top->s<<std::endl;
}

// 入栈操作
bool Stack::pushStack(std::string node_s){
    Node *temp = new Node;
    temp->s = node_s;
    temp->ps_front = top;
    top = temp;
    return true;
}

// 出栈操作
bool Stack::popStack(){
    if(top->ps_front != NULL){
        Node *temp = top;
        top->s=top->ps_front->s;
        top=top->ps_front;
        delete temp;
    }else{
        std::cout<<"错误：出栈失败(栈空)"<<std::endl;
        return false;
    }
    return true;
}