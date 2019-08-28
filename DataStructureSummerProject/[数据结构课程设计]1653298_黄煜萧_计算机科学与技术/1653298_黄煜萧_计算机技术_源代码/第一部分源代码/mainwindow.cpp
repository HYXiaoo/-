#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <sstream>
#include <QMessageBox>
#include "global.h"
#include "heapsort.h"
#include "treebuild.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GV.runStatus=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insertButton_clicked()
{
    QString s=ui->InputEdit->text();
    if(s!="0"&&s.toInt()==0){
        QMessageBox::information(this,"Dialog","Data Format is wrong!\nThe program only Supports integer.");
        ui->InputEdit->clear();
        return;
    }
    ui->listWidget->addItem(ui->InputEdit->text());
    ui->InputEdit->clear();
}

void MainWindow::on_deleteButton_clicked()
{
    int row = ui->listWidget->currentRow();
    ui->listWidget->takeItem(row);
}

void MainWindow::on_executeButton_clicked()
{
    //std::cout<<GV.runStatus;
    if(GV.runStatus==0){
        GV.size=ui->listWidget->count();
        for(int i=0;i<GV.size;i++){
            GV.array[i]=ui->listWidget->item(i)->text().toInt();
        }

        GV.heapSize=GV.size;
        GV.runStatus=1;//表示排序开始
        ui->treeWidget->clear();
        ui->statusLabel->setText("Sorting...");
        ui->InputEdit->setEnabled(false);
        ui->listWidget->setEnabled(false);
        ui->executeButton->setText("Execute a Step");

        BuildHeap(GV.array,GV.size);//建立初始的堆
    }
    if(GV.runStatus==1){
        int flag=ExecuteStep();
        if(flag==1){
            QList<QTreeWidgetItem *> rootList=treeBuild(GV.array,0,GV.heapSize);
            ui->treeWidget->insertTopLevelItems(0,rootList);
            Swap(GV.array[0],GV.array[--GV.heapSize]);
        }
        else if(flag==2){
            QList<QTreeWidgetItem *> rootList=treeBuild(GV.array,0,GV.heapSize);
            ui->treeWidget->insertTopLevelItems(0,rootList);
            Swap(GV.array[0],GV.array[--GV.heapSize]);

            QMessageBox::information(this,"Dialog","Sort Complete!");
            ui->statusLabel->setText("Waiting for next turn data...");
            GV.runStatus=0;

            ui->listWidget->setEnabled(true);
            ui->InputEdit->setEnabled(true);
            ui->executeButton->setText("Start");
            ui->listWidget->clear();
        }
    }
}

void MainWindow::on_finishButton_clicked()
{
    if(GV.runStatus==0){
        GV.size=ui->listWidget->count();
        for(int i=0;i<GV.size;i++){
            GV.array[i]=ui->listWidget->item(i)->text().toInt();
        }

        GV.heapSize=GV.size;
        GV.runStatus=1;//表示排序开始
        ui->treeWidget->clear();
        ui->statusLabel->setText("Sorting...");
        ui->InputEdit->setEnabled(false);
        ui->listWidget->setEnabled(false);

        BuildHeap(GV.array,GV.size);//建立初始的堆
    }
    if(GV.runStatus==1){
        while(GV.heapSize>=0){
            ExecuteStep();
            QList<QTreeWidgetItem *> rootList=treeBuild(GV.array,0,GV.heapSize);
            ui->treeWidget->insertTopLevelItems(0,rootList);
            Swap(GV.array[0],GV.array[--GV.heapSize]);
        }
        QMessageBox::information(this,"Dialog","Sort Complete!");
        ui->statusLabel->setText("Waiting for next turn data...");
        GV.runStatus=0;

        ui->listWidget->setEnabled(true);
        ui->InputEdit->setEnabled(true);
        ui->executeButton->setText("Start");
        ui->listWidget->clear();
    }
}
