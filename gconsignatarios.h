#ifndef GCONSIGNATARIOS_H
#define GCONSIGNATARIOS_H

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
    class Gconsignatarios;
}

class Gconsignatarios : public QDialog
{
    Q_OBJECT

public:
    explicit Gconsignatarios(QWidget *parent = 0);
    ~Gconsignatarios();

private:
    Ui::Gconsignatarios *ui;
    QSqlRelationalTableModel *model;
private slots:
    //consignatarios
      void AddItem3();
      void EditItem3();
      void DelItem3();
};

#endif // GCONSIGNATARIOS_H
