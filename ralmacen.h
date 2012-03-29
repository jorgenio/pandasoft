#ifndef RALMACEN_H
#define RALMACEN_H

#include "qdialog.h"
#include "QModelIndex"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class ralmacen;
}

class ralmacen : public QDialog
{
    Q_OBJECT

public:
    explicit ralmacen(QWidget *parent = 0);
    ~ralmacen();

protected:
    void changeEvent(QEvent *e);
private slots:
    void Imprimir();
private:
    Ui::ralmacen *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // RALMACEN_H
