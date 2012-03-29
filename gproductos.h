#ifndef GPRODUCTOS_H
#define GPRODUCTOS_H

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
    class Gproductos;
}

class Gproductos : public QDialog
{
    Q_OBJECT

public:
    explicit Gproductos(QWidget *parent = 0);
    ~Gproductos();

private:
    Ui::Gproductos *ui;
    QSqlRelationalTableModel *model;

private slots:
    //productos
      void AddItem5();
      void EditItem5();
      void DelItem5();
};

#endif // GPRODUCTOS_H
