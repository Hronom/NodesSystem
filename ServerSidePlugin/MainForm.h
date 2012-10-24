#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QFile>
#include "INode.h"
#include "NodeInfo.h"
#include "IPlugin.h"
#include "InstalledProgramsForm.h"

namespace Ui
{
    class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT
private:
    Ui::MainForm *mUI;
    INode *mINode;

public:
    MainForm(INode *xINode, QWidget *xParent = 0);
    ~MainForm();

private:
    void refillNodesTable();

protected:
    void changeEvent(QEvent *xEvent);

private slots:
    void itemClicked_SLOT(QTableWidgetItem* xTableWidgetItem);
    void newNodesFound();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // MAINFORM_H
