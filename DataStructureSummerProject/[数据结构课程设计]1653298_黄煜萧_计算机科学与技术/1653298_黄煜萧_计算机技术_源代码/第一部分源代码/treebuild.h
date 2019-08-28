#ifndef TREEBUILD_H
#define TREEBUILD_H

#include<QQueue>
#include<QList>
#include<QTreeWidget>
QList<QTreeWidgetItem *> treeBuild(int *a,int beg,int end){
    QList<QTreeWidgetItem *> rootList;
    QQueue<QTreeWidgetItem *> queue;
    QTreeWidgetItem *tp;
    for(int i=beg;i<end;i++){
        if(i==0){
            tp=new QTreeWidgetItem();
            tp->setText(0,QString::number(a[i]));
            rootList.append(tp);
            queue.push_back(tp);
        }
        else{
            tp=new QTreeWidgetItem();
            tp->setText(0,QString::number(a[i]));
            queue.front()->addChild(tp);
            queue.push_back(tp);

            i++;

            if(i<end){
                tp=new QTreeWidgetItem();
                tp->setText(0,QString::number(a[i]));
                queue.front()->addChild(tp);
                queue.push_back(tp);
            }

            queue.pop_front();
        }
    }
    return rootList;
}

#endif // TREEBUILD_H
