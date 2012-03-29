#ifndef RGVENTA_H
#define RGVENTA_H

#include "qdialog.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE
namespace Ui {
    class rgventa;
}

class rgventa : public QDialog
{
    Q_OBJECT

public:
    explicit rgventa(const QString &codven, QWidget *parent = 0);
    ~rgventa();

private slots:
    void Imprimir();

private:
    Ui::rgventa *ui;
    QSqlRelationalTableModel *model;
    QPrinter *printer;
    QListWidget *List;

};

#endif // RGVENTA_H
