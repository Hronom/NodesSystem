#ifndef INSTALLEDPROGRAMSFORM_H
#define INSTALLEDPROGRAMSFORM_H

#include <QWidget>
#include "INode.h"
#include "NodeInfo.h"

namespace Ui
{
    class InstalledProgramsForm;
}

class InstalledProgramsForm : public QWidget
{
    Q_OBJECT

private:
    Ui::InstalledProgramsForm *mUI;

public:
    InstalledProgramsForm(NodeInfo xNodeInfo, QWidget *xParent = 0);
    ~InstalledProgramsForm();

    void setProgramList(QString xFilePath);

protected:
    void changeEvent(QEvent *xEvent);

private slots:
    void on_pushButton_clicked();
};

#endif // INSTALLEDPROGRAMSFORM_H
