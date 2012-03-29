#ifndef RCONSIGNACIONES_H
#define RCONSIGNACIONES_H

#include "qdialog.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class rconsignaciones;
}

class rconsignaciones : public QDialog
{
    Q_OBJECT

public:
    explicit rconsignaciones(QWidget *parent = 0);
    ~rconsignaciones();

private slots:
    void Imprimir();
    void Verdetalle();

private:
    Ui::rconsignaciones *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};







#endif // RCONSIGNACIONES_H
