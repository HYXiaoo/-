#ifndef TEXTPROCESS_H
#define TEXTPROCESS_H
#pragma once
#include <string.h>
#include <ctype.h>
//#include <iostream>
//using namespace std;

//求取KMP算法所使用的next数组
void GetNextval(char* p, int next[]) {
    int pLen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1)
    {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            if (p[j] != p[k])
                next[j] = k;
            else
                next[j] = next[k];
        }
        else
        {
            k = next[k];
        }
    }
}

//////////////////////
//KMP字符串查找算法
//s为母串 p为模式串
//beg为开始位置
//第一次匹配到即结束
/////////////////////
int KmpSearch(char* s, char* p, int beg) {

    int i = beg;
    int j = 0;
    int sLen = strlen(s);
    int pLen = strlen(p);
    int *next = new int[pLen];
    GetNextval(p, next);

    while (i < sLen && j < pLen)
    {
        //如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]
            //next[j]即为j所对应的next值
            j = next[j];
        }
    }

    delete next;

    if (j == pLen)
        return i - j;
    else
        return -1;
}

//////////////////////
//字符串统计
//charC 字母个数
//numC 数字个数
//spaceC 空白字符个数
//返回非法字符个数
/////////////////////
int Statistic(char *s, int &charC, int &numC, int &spaceC) {
    charC = 0;
    numC = 0;
    spaceC = 0;
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) charC++;
        else if (isdigit(s[i])) numC++;
        else if (isspace(s[i])) spaceC++;
    }
    return i - charC - numC - spaceC;
}
//删除串索引范围内的内容
//beg开始位置 l删除长度
//返回-1：索引超界
int DeleteRange(char *s, int beg, int l) {
    int len = strlen(s);
    if (beg+l > len||beg<0||l<1) return -1;
    int d = l;
    for (int i = beg; i <= len-d; i++) {
        s[i] = s[i + d];
        //cout << s[i];
    }
    //cout << endl;
    return 1;
}
#endif // TEXTPROCESS_H
