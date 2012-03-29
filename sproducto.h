#ifndef SPRODUCTO_H
#define SPRODUCTO_H

#include "qdialog.h"
#include "QModelIndex"
#include "qdatawidgetmapper.h"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE
namespace Ui {
    class sproducto;
}

class sproducto : public QDialog
{
    Q_OBJECT

public:
    explicit sproducto(QWidget *parent = 0);
    ~sproducto();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::sproducto *ui;
    QSqlRelationalTableModel *productomodel;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
private slots:
  void guardar();
  void cargar();

};

#endif // SPRODUCTO_H
