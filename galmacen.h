#ifndef GALMACEN_H
#define GALMACEN_H

#include "QModelIndex"
#include "qdialog.h"
#include <QMainWindow>
#include "qstringlistmodel.h"
#include "qstandarditemmodel.h"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE
namespace Ui {
    class Galmacen;
}

class Galmacen : public QDialog
{
    Q_OBJECT

public:
    explicit Galmacen(QWidget *parent = 0);
    ~Galmacen();

private slots:
    void SProductos();
    void REproductos();

private:
    Ui::Galmacen *ui;
    QSqlRelationalTableModel *model;
};

#endif // GALMACEN_H
