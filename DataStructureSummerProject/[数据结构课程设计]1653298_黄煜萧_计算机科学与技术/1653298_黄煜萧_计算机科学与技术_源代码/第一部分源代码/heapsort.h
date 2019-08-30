#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "global.h"

void HeapAdjust(int *a, int i, int size) {//堆调整算法
    int lchild = 2 * i + 1;       //左孩子节点
    int rchild = 2 * i + 2;     //右孩子节点
    int max = i;
    if (i <= size / 2 + 1) {
        if (lchild < size && a[lchild] > a[max])
            max = lchild;
        if (rchild < size && a[rchild] > a[max])
            max = rchild;
        if (max != i) {
            if (a[i] != a[max]) {
                a[i] = a[i] ^ a[max];
                a[max] = a[i] ^ a[max];
                a[i] = a[i] ^ a[max];
            }
            HeapAdjust(a, max, size);    //递归调整
        }
    }
}

void Swap(int &a,int &b){
    if(a!=b){
        a=a^b;
        b=a^b;
        a=a^b;
    }
}

void BuildHeap(int *a, int size) {//注：在进行堆整理,必须先建立堆
    int i;
    for (i = size / 2 + 1; i >=0 ; i--)
        HeapAdjust(a, i, size);
}

int ExecuteStep(){//注：进行堆整理,为堆排序主循环所调用
    ///////////////////////////////////
    //返回值：
    //0=未开始排序
    //1=执行成功
    //2=排序已结束
    //3=程序状态非法
    ///////////////////////////////////
    if(GV.runStatus==0) return 0;
    else if(GV.runStatus==1){
        if(GV.heapSize>1){
            HeapAdjust(GV.array,0,GV.heapSize);
            return 1;
        }
        if(GV.heapSize==1){
            HeapAdjust(GV.array,0,GV.heapSize);
            return 2;
        }
        else return 2;
    }
    else return 3;
}
#endif // HEAPSORT_H
