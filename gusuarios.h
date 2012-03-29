#ifndef GUSUARIOS_H
#define GUSUARIOS_H

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
    class Gusuarios;
}

class Gusuarios : public QDialog
{
    Q_OBJECT

public:
    explicit Gusuarios(QWidget *parent = 0);
    ~Gusuarios();

private:
    Ui::Gusuarios *ui;
    QSqlRelationalTableModel *model;

private slots:
    void AddItem8();
    void EditItem8();
    void DelItem8();
};

#endif // GUSUARIOS_H
