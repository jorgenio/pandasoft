#ifndef GVENTAS_H
#define GVENTAS_H

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
    class Gventas;
}

class Gventas : public QDialog
{
    Q_OBJECT

public:
    explicit Gventas(QWidget *parent = 0);
    ~Gventas();

private:
    Ui::Gventas *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *modelodventa;
    QListWidget *List;
    QSqlRelationalTableModel *productomodel;

private slots:
    void Addventas();
    void AddDventas();
    void CargarDventas();
    void nuevoventas();
    void showventasDetails(QModelIndex index);
    void CAncelar();

};

#endif // GVENTAS_H
