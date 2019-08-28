#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_insertButton_clicked();

    void on_deleteButton_clicked();

    void on_executeButton_clicked();

    void on_finishButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
