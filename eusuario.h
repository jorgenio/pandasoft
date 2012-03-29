#ifndef EUSUARIO_H
#define EUSUARIO_H

#include "qdialog.h"
#include "QtSql"
#include "qdatawidgetmapper.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

namespace Ui {
    class eusuario;
}

class eusuario : public QDialog
{
    Q_OBJECT

public:
    explicit eusuario(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent = 0);
    ~eusuario();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::eusuario *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *sucursalmodel;
    QDataWidgetMapper *mapper;

private slots:
    void Aceptar();
    void Editar();

};

#endif // EUSUARIO_H
