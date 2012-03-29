#ifndef EEMPLEADO_H
#define EEMPLEADO_H

#include "qdialog.h"
#include "QtSql"
#include "qdatawidgetmapper.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

namespace Ui {
    class eempleado;
}

class eempleado : public QDialog
{
    Q_OBJECT

public:
    explicit eempleado(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent = 0);
    ~eempleado();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::eempleado *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *sucursalmodel;
    QDataWidgetMapper *mapper;

private slots:
    void Aceptar();
    void Editar();
};

#endif // EEMPLEADO_H
