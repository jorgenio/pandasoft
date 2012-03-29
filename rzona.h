#ifndef RZONA_H
#define RZONA_H

#include "qdialog.h"
#include "QModelIndex"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class rzona;
}

class rzona : public QDialog
{
    Q_OBJECT

public:
    explicit rzona(QWidget *parent = 0);
    ~rzona();

protected:
    void changeEvent(QEvent *e);

private slots:
    void Imprimir();

private:
    Ui::rzona *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;
};

#endif // RZONA_H
