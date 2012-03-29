#ifndef RSUCURSAL_H
#define RSUCURSAL_H

#include "qdialog.h"
#include "QModelIndex"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class rsucursal;
}

class rsucursal : public QDialog
{
    Q_OBJECT

public:
    explicit rsucursal(QWidget *parent = 0);
    ~rsucursal();

protected:
    void changeEvent(QEvent *e);
private slots:
    void Imprimir();
private:
    Ui::rsucursal *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // RSUCURSAL_H
