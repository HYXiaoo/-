#ifndef GLOBAL_H
#define GLOBAL_H

class {
public:
    int array[1024]; //数组缓存
    int size;        //排序所使用数组的大小
    int runStatus;   //程序状态变量
    ///////////////////////////////////
    //runStatus解释:
    //0=未开始排序
    //1=排序中
    ///////////////////////////////////
    int heapSize;    //堆的大小
} GV;

#endif // GLOBAL_H
