#ifndef GSUCURSAL_H
#define GSUCURSAL_H

#include "QModelIndex"
#include "qdialog.h"
#include <QMainWindow>
#include "qstringlistmodel.h"
#include "qstandarditemmodel.h"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE
namespace Ui {
    class Gsucursal;
}

class Gsucursal : public QDialog
{
    Q_OBJECT

public:
    explicit Gsucursal(QWidget *parent = 0);
    ~Gsucursal();

private:
    Ui::Gsucursal *ui;
    QSqlRelationalTableModel *model;
private slots:
    void AddItem7();
    void EditItem7();
    void DelItem7();
};

#endif // GSUCURSAL_H
