#ifndef RCONSIGNATARIO_H
#define RCONSIGNATARIO_H

#include "qdialog.h"
#include "QModelIndex"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class rconsignatario;
}

class rconsignatario : public QDialog
{
    Q_OBJECT

public:
    explicit rconsignatario(QWidget *parent = 0);
    ~rconsignatario();

protected:
    void changeEvent(QEvent *e);

private slots:
    void Imprimir();

private:
    Ui::rconsignatario *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // RCONSIGNATARIO_H
