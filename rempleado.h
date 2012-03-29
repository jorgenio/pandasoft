#ifndef REMPLEADO_H
#define REMPLEADO_H

#include "qdialog.h"
#include "QModelIndex"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class rempleado;
}

class rempleado : public QDialog
{
    Q_OBJECT

public:
    explicit rempleado(QWidget *parent = 0);
    ~rempleado();

protected:
    void changeEvent(QEvent *e);
private slots:
    void Imprimir();
private:
    Ui::rempleado *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // REMPLEADO_H
