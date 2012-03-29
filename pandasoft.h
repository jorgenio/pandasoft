#ifndef PANDASOFT_H
#define PANDASOFT_H
#include "QModelIndex"
#include "qdialog.h"
#include <QMainWindow>
#include "qstringlistmodel.h"
#include "qstandarditemmodel.h"
#include "qsqlquerymodel.h"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE


namespace Ui {
    class pandasoft;
}

class pandasoft : public QMainWindow
{
    Q_OBJECT

public:
    explicit pandasoft(QWidget *parent = 0);
    ~pandasoft();

private slots:
  void Principal();
  void GAlmacen();
  void GEmpleado();
  void GProductos();
  void GReportes();
  void GSucursal();
  void GUsuarios();
  void GVentas();
  void GZona();
  void GConsignatario();
  void GConsignaciones();

  void aboutpandasoft();

private:
    Ui::pandasoft *ui;
    QSqlRelationalTableModel *sucursalmodel;
    QListWidget *errorList;
    QSqlRelationalTableModel *model;
    QSqlQueryModel *qmodel;

    QSqlRelationalTableModel *modelodasignar;
    QSqlRelationalTableModel *modelodventa;
    QListWidget *List;
    QSqlRelationalTableModel *productomodel;
    QSqlRelationalTableModel *consignatariomodel;
    QSqlRelationalTableModel *estadomodel;

};

#endif // PANDASOFT_H
