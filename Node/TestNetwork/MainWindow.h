#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CommunicationSystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    CommunicationSystem *mCommunicationSystem;
    Ui::MainWindow *mUI;

public:
    explicit MainWindow(QWidget *xParent = 0);
    ~MainWindow();    

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
