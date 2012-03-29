#ifndef RPRODUCTO_H
#define RPRODUCTO_H

#include "qdialog.h"
#include "QModelIndex"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class rproducto;
}

class rproducto : public QDialog
{
    Q_OBJECT

public:
    explicit rproducto(QWidget *parent = 0);
    ~rproducto();

protected:
    void changeEvent(QEvent *e);
private slots:
    void Imprimir();
private:
    Ui::rproducto *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // RPRODUCTO_H
