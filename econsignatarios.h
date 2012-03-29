#ifndef ECONSIGNATARIOS_H
#define ECONSIGNATARIOS_H

#include "qdialog.h"
#include "QtSql"
#include "qdatawidgetmapper.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

namespace Ui {
    class econsignatarios;
}

class econsignatarios : public QDialog
{
    Q_OBJECT

public:
    explicit econsignatarios(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent = 0);
    ~econsignatarios();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::econsignatarios *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *sucursalmodel;
    QDataWidgetMapper *mapper;

private slots:
    void Aceptar();
    void Editar();
};

#endif // ECONSIGNATARIOS_H
