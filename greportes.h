#ifndef GREPORTES_H
#define GREPORTES_H

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
    class Greportes;
}

class Greportes : public QDialog
{
    Q_OBJECT

public:
    explicit Greportes(const QString &usurol,QWidget *parent = 0);
    ~Greportes();

private:
    Ui::Greportes *ui;
    QSqlRelationalTableModel *model;
private slots:
    //reportes
      void Ralmacen();
      void Rempleado();
      void Rproducto();

      void Rusuario();
      void Rventas();
      void Rzona();
      void Rconsignatario();
      void Rconsignaciones();
};

#endif // GREPORTES_H
