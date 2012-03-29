#ifndef RVENTAS_H
#define RVENTAS_H

#include "qdialog.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE
namespace Ui {
    class rventas;
}

class rventas : public QDialog
{
    Q_OBJECT

public:
    explicit rventas(QWidget *parent = 0);
    ~rventas();

protected:
    void changeEvent(QEvent *e);

private slots:
    void Imprimir();
    void Verdetalle();

private:
    Ui::rventas *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // RVENTAS_H
