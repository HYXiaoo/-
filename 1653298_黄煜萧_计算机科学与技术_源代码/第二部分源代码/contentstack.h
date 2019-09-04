#ifndef CONTENTSTACK_H
#define CONTENTSTACK_H
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<string.h>

//用于保存文本内容的栈
//可一个栈用于撤销修改
//一个栈用于恢复修改
class ContentStack {
private:
    struct node {
        char text[2048];
        node *next;
    } *head,*top;
    int maxSize;
public:
    //初始化栈的大小
    //超过大小的旧内容会被丢弃
    ContentStack(int size) {
        maxSize = size;
        head = new node;
        head->next = NULL;
        top = head;
    }
    ~ContentStack() {
        node *p = head,*q;
        while (p != NULL) {
            q = p;
            p = p->next;
            delete q;
        }
    }
    int size() {
        node *p = head;
        int cnt = 0;
        while (p->next != NULL) {
            cnt++;
            p = p->next;
        }
        return cnt;
    }
    //入栈
    //返回：1正常，0溢出
    //溢出为删去栈底再入栈
    int push(char *text) {
        node *p = new node;
        strcpy(p->text, text);
        p->next = NULL;
        top->next = p;
        top = p;
        if (size() <= maxSize) return 1;
        else {
            p = head;
            head = head->next;
            delete p;
            return 0;
        }
    }
    //出栈
    //返回：1正常，-1栈空
    int pop(char *text) {
        if (top == head) return -1;
        node *nearTop = head;
        while (nearTop->next != top) {
            nearTop = nearTop->next;
        }
        strcpy(text, top->text);
        nearTop->next = NULL;
        delete top;
        top = nearTop;
        return 1;
    }

};
#endif // CONTENTSTACK_H
