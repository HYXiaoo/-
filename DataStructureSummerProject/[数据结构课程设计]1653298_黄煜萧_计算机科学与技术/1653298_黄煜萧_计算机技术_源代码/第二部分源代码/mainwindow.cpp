#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textprocess.h"
#include "global.h"
#include <QMessageBox>
//#include <iostream>
#include <fstream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statLable->setText("alphabets:0 digits:0 spaces:0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    char *content;
    QByteArray ba=ui->textEdit->toPlainText().toLatin1();
    content=ba.data();
    if(strlen(content)>2000) {
        ui->textEdit->undo();
        QMessageBox::information(this,"dialog","Content Exceeds 2000!\nThe program only supports 2000 characters.");
        return;
    }

    int cnum,nnum,snum;
    Statistic(content,cnum,nnum,snum);
    ui->statLable->setText("alphabets:"
                           +QString::number(cnum)
                           +" digits:"
                           +QString::number(nnum)
                           +" spaces:"
                           +QString::number(snum));
    Bstack.push(content);
}

void MainWindow::on_revokeButton_clicked()
{
    char content[2048];
    if(Bstack.pop(content)>0){
        Fstack.push(content);
        Bstack.pop(content);
        //QMessageBox::information(this,"dialog",content);
        QString s=QString(QLatin1String(content));
        ui->textEdit->setText(s);
    }
}

void MainWindow::on_resButton_clicked()
{
    char content[2048];
    if(Fstack.pop(content)>0){
        //Fstack.pop(content);
        //QMessageBox::information(this,"dialog",content);
        QString s=QString(QLatin1String(content));
        ui->textEdit->setText(s);
    }
}

void MainWindow::on_countButton_clicked()
{
    if(ui->lineEdit->text().size()<=0) return;

    char *content,*p;
    QByteArray ba=ui->textEdit->toPlainText().toLatin1();
    content=ba.data();
    QByteArray bap=ui->lineEdit->text().toLatin1();
    p=bap.data();

    int i=-1,cnt=0;
    while(1){
        i=KmpSearch(content,p,i+1);
        if(i<0) break;
        else cnt++;
    }
    QMessageBox::information(this,"dialog","The substring appears "
                             +QString::number(cnt)
                             +" times\nin the content");
}

void MainWindow::on_deleteButton_clicked()
{
    if(ui->lineEdit->text().size()<=0) return;

    char *content,*p;
    QByteArray ba=ui->textEdit->toPlainText().toLatin1();
    content=ba.data();
    QByteArray bap=ui->lineEdit->text().toLatin1();
    p=bap.data();

     std::cout<<content;

    int i,len=strlen(p);

    i=KmpSearch(content,p,0);
    if(i<0) QMessageBox::information(this,"dialog","Substring not found!");
    else{
        DeleteRange(content,i,len);
        while((i=KmpSearch(content,p,0))>=0){
            //QMessageBox::information(this,"dialog",QString::number(i));
            DeleteRange(content,i,len);
        }
    }

    QString s=QString(QLatin1String(content));
    ui->textEdit->setText(s);
}

void MainWindow::on_svaeButton_clicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Select path ...", "./");
    if(file_path.isEmpty()){
        return;
    }
    std::ofstream fout(file_path.toStdString());

    char *content;
    QByteArray ba=ui->textEdit->toPlainText().toLatin1();
    content=ba.data();

    fout<<content;
    QMessageBox::information(this,"dialog","Save success!");
}

void MainWindow::on_loadButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Select path ...", "./");
    if(file_path.isEmpty()){
        return;
    }
    //QMessageBox::information(this,"dialog",file_path);

    std::ifstream fin(file_path.toStdString());
    char content[2048];
    for(int i=0;i<=2000;i++){
        if(fin.eof()||i>=2000){
            content[i]=0;
            break;
        }
        else content[i]=fin.get();
    }

    QString s=QString(QLatin1String(content));
    ui->textEdit->setText(s);
}
