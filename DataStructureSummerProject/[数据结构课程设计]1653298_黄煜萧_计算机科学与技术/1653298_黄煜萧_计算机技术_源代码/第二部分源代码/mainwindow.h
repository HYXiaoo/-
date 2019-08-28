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
    void on_textEdit_textChanged();

    void on_revokeButton_clicked();

    void on_resButton_clicked();

    void on_countButton_clicked();

    void on_deleteButton_clicked();

    void on_svaeButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
