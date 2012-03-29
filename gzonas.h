#ifndef GZONAS_H
#define GZONAS_H
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
    class Gzonas;
}

class Gzonas : public QDialog
{
    Q_OBJECT

public:
    explicit Gzonas(QWidget *parent = 0);
    ~Gzonas();

private:
    Ui::Gzonas *ui;
    QSqlRelationalTableModel *model;
private slots:
    void AddItem10();
    void EditItem10();
    void DelItem10();

};

#endif // GZONAS_H
