#ifndef RUSUARIO_H
#define RUSUARIO_H

#include "qdialog.h"
#include "QModelIndex"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class rusuario;
}

class rusuario : public QDialog
{
    Q_OBJECT

public:
    explicit rusuario(QWidget *parent = 0);
    ~rusuario();

protected:
    void changeEvent(QEvent *e);
private slots:
    void Imprimir();
private:
    Ui::rusuario *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // RUSUARIO_H
