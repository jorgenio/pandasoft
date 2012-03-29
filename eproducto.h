#ifndef EPRODUCTO_H
#define EPRODUCTO_H

#include "qdialog.h"
#include "QtSql"
#include "qdatawidgetmapper.h"
#include <QFileDialog>

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

namespace Ui {
    class eproducto;
}

class eproducto : public QDialog
{
    Q_OBJECT

public:
    explicit eproducto(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent = 0);
    ~eproducto();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::eproducto *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *sucursalmodel;
    QDataWidgetMapper *mapper;

private slots:
    void Aceptar();
    void Editar();
    void openFile();
};

#endif // EPRODUCTO_H
