#ifndef ESUCURSAL_H
#define ESUCURSAL_H

#include "qdialog.h"
#include "QtSql"
#include "qdatawidgetmapper.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

namespace Ui {
    class esucursal;
}

class esucursal : public QDialog
{
    Q_OBJECT

public:
    explicit esucursal(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent = 0);
    ~esucursal();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::esucursal *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *sucursalmodel;
    QDataWidgetMapper *mapper;

private slots:
    void Aceptar();
    void Editar();
};

#endif // ESUCURSAL_H
