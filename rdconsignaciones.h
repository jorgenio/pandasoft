#ifndef RDCONSIGNACIONES_H
#define RDCONSIGNACIONES_H

#include "qdialog.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE
namespace Ui {
    class rdconsignaciones;
}

class rdconsignaciones : public QDialog
{
    Q_OBJECT

public:
    explicit rdconsignaciones(const QString &codven, QWidget *parent = 0);
    ~rdconsignaciones();
private slots:
    void Imprimir();


private:
    Ui::rdconsignaciones *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;

};

#endif // RDCONSIGNACIONES_H
