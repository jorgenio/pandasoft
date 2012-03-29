#ifndef GEMPLEADOS_H
#define GEMPLEADOS_H

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
    class Gempleados;
}

class Gempleados : public QDialog
{
    Q_OBJECT

public:
    explicit Gempleados(QWidget *parent = 0);
    ~Gempleados();

private:
    Ui::Gempleados *ui;
    QSqlRelationalTableModel *model;

private slots:
    void AddItem4();
    void EditItem4();
    void DelItem4();
};

#endif // GEMPLEADOS_H
