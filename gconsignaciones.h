#ifndef GCONSIGNACIONES_H
#define GCONSIGNACIONES_H

#include "QModelIndex"
#include "qdialog.h"
#include <QMainWindow>
#include "qstringlistmodel.h"
#include "qstandarditemmodel.h"
#include "qdatawidgetmapper.h"
QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QListWidget;
QT_END_NAMESPACE
namespace Ui {
    class Gconsignaciones;
}

class Gconsignaciones : public QDialog
{
    Q_OBJECT

public:
    explicit Gconsignaciones(QWidget *parent = 0);
    ~Gconsignaciones();

private:
    Ui::Gconsignaciones *ui;
    QSqlRelationalTableModel *model;

    QSqlRelationalTableModel *modelodasignar;
    QSqlRelationalTableModel *productomodel;
    QSqlRelationalTableModel *consignatariomodel;
    QDataWidgetMapper *mapper;

private slots:
    void Addasignar();
    void AddDasignar();
    void CargarDasignar();
    void nuevoasignar();
    void modificarasignar();
    void showasignarDetails(QModelIndex index);
    void CAncelar();
    void Vendido();
    void Pendiente();
    void Eliminar();

};

#endif // GCONSIGNACIONES_H
