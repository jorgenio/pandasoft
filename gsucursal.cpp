#include "gsucursal.h"
#include "ui_gsucursal.h"
#include "esucursal.h"
#include "ui_esucursal.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "qlistwidget.h"

Gsucursal::Gsucursal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gsucursal)
{
    ui->setupUi(this);
    ui->informacion7->hide();

    model = new QSqlRelationalTableModel(this);
    model->setTable("sucursal");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));

    ui->lista7->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista7->setSortingEnabled(true);
    ui->lista7->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista7->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista7->setShowGrid(false);
    ui->lista7->verticalHeader()->hide();
    ui->lista7->setAlternatingRowColors(true);
    ui->lista7->setModel(model);

    connect( ui->modbutton7, SIGNAL(clicked()), this, SLOT(EditItem7()) );

}

Gsucursal::~Gsucursal()
{
    delete ui;
}
void Gsucursal::AddItem7()
{

    esucursal *add = new esucursal(-1, model, "Adicionar Sucursal", this);
    int accepted = add->exec();
    ui->informacion7->hide();

    if (accepted == 1) {
        ui->informacionlabel7->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion7->show();
    }

}
void Gsucursal::EditItem7()
{
    ui->informacion7->hide();
    QModelIndexList selection = ui->lista7->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        esucursal *edit = new esucursal(idIndex.row(), model, "Modificar Sucursal", this);
        int accepted = edit->exec();
        ui->informacion7->hide();

        if (accepted == 1) {
            ui->informacionlabel7->setText(" Los datos se \n guardaron \n correctamente ");
            ui->informacion7->show();
        }

    } else {
        ui->informacionlabel7->setText(" Seleccione la\n sucursal que\n desee modificar");
        ui->informacion7->show();
    }
}

void Gsucursal::DelItem7()
{

        ui->informacion7->hide();
        QModelIndexList selection = ui->lista7->selectionModel()->selectedRows(0);
        if (!selection.empty()) {
            QModelIndex idIndex = selection.at(0);
            mensajebox *add = new mensajebox("Borrar sucursal", "Esta seguro de Esta seguro de eliminar?", this);
            int accepted = add->exec();
            if (accepted == 1) {
                model->removeRow(idIndex.row());
                ui->informacionlabel7->setText("  La sucursal \n fue eliminada");
                ui->informacion7->show();
            }
        } else {
            ui->informacionlabel7->setText(" Seleccione la\n sucursal que\n desee eliminar");
            ui->informacion7->show();

        }
}
