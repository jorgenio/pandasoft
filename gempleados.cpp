#include "gempleados.h"
#include "ui_gempleados.h"
#include "eempleado.h"
#include "ui_eempleado.h"


#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qlistwidget.h"

Gempleados::Gempleados(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gempleados)
{
    ui->setupUi(this);
    ui->informacion4->hide();
    model = new QSqlRelationalTableModel(this);
    model->setTable("Empleado");
    model->select();

    ui->lista4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista4->setSortingEnabled(true);
    ui->lista4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista4->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista4->setShowGrid(false);
    ui->lista4->verticalHeader()->hide();
    ui->lista4->setAlternatingRowColors(true);
    ui->lista4->setModel(model);


    connect( ui->addbutton4, SIGNAL(clicked()), this, SLOT(AddItem4()) );
    connect( ui->modbutton4, SIGNAL(clicked()), this, SLOT(EditItem4()) );
    connect( ui->delbutton4, SIGNAL(clicked()), this, SLOT(DelItem4()) );

}

Gempleados::~Gempleados()
{
    delete ui;
}
void Gempleados::AddItem4()
{

    eempleado *add = new eempleado(-1, model, "Adicionar Empleado", this);
    int accepted = add->exec();
    ui->informacion4->hide();

    if (accepted == 1) {
        ui->informacionlabel4->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion4->show();
    }

}
void Gempleados::EditItem4()
{
    ui->informacion4->hide();
    QModelIndexList selection = ui->lista4->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        eempleado *edit = new eempleado(idIndex.row(), model, "Modificar Empleado", this);
        int accepted = edit->exec();
        ui->informacion4->hide();

        if (accepted == 1) {
            ui->informacionlabel4->setText(" Los datos se \n guardaron \n correctamente ");
            ui->informacion4->show();
        }

    } else {
        ui->informacionlabel4->setText(" Seleccione el\n empleado que\n desee modificar");
        ui->informacion4->show();
    }

}
void Gempleados::DelItem4()
{
        ui->informacion4->hide();
        QModelIndexList selection = ui->lista4->selectionModel()->selectedRows(0);
        if (!selection.empty()) {
            QModelIndex idIndex = selection.at(0);
            mensajebox *add = new mensajebox("Borrar empleado", "Esta seguro de eliminar?", this);
            int accepted = add->exec();
            if (accepted == 1) {
                model->removeRow(idIndex.row());
                ui->informacionlabel4->setText("  El empleado \n fue eliminado");
                ui->informacion4->show();
            }
        } else {
            ui->informacionlabel4->setText(" Seleccione el\n empleado que\n desee eliminar");
            ui->informacion4->show();

        }
}

