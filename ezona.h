#ifndef EZONA_H
#define EZONA_H

#include "qdialog.h"
#include "QtSql"
#include "qdatawidgetmapper.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

namespace Ui {
    class ezona;
}

class ezona : public QDialog
{
    Q_OBJECT

public:
    explicit ezona(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent = 0);
    ~ezona();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ezona *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *sucursalmodel;
    QDataWidgetMapper *mapper;

private slots:
    void Aceptar();
    void Editar();
};

#endif // EZONA_H
