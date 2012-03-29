#ifndef REPRODUCTOS_H
#define REPRODUCTOS_H

#include "qdialog.h"
#include "QModelIndex"
#include "qdatawidgetmapper.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class reproductos;
}

class reproductos : public QDialog
{
    Q_OBJECT

public:
    explicit reproductos(QWidget *parent = 0);
    ~reproductos();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::reproductos *ui;
    QSqlRelationalTableModel *productomodel;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
private slots:
  void guardar();
  void cargar();
};

#endif // REPRODUCTOS_H
