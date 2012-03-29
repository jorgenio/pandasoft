#include "gzonas.h"
#include "ui_gzonas.h"
#include "ezona.h"
#include "ui_ezona.h"
#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "qlistwidget.h"

Gzonas::Gzonas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gzonas)
{
    ui->setupUi(this);
    ui->informacion10->hide();


    model = new QSqlRelationalTableModel(this);
    model->setTable("zona");
    model->setRelation(3, QSqlRelation("sucursal", "Id_suc", "Nombre"));
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sucursal"));
    model->removeColumn(3);

    ui->lista10->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista10->setSortingEnabled(true);
    ui->lista10->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista10->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista10->setShowGrid(false);
    ui->lista10->verticalHeader()->hide();
    ui->lista10->setAlternatingRowColors(true);
    ui->lista10->setModel(model);
   // ui->lista->hideColumn(7);

    connect( ui->addbutton10, SIGNAL(clicked()), this, SLOT(AddItem10()) );
    connect( ui->modbutton10, SIGNAL(clicked()), this, SLOT(EditItem10()) );
    connect( ui->delbutton10, SIGNAL(clicked()), this, SLOT(DelItem10()) );

}

Gzonas::~Gzonas()
{
    delete ui;
}
void Gzonas::AddItem10()
{
    ezona *add = new ezona(-1, model, "Adicionar Zona", this);
    int accepted = add->exec();
    ui->informacion10->hide();

    if (accepted == 1) {
        ui->informacionlabel10->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion10->show();
    }

}
void Gzonas::EditItem10()
{
    ui->informacion10->hide();
    QModelIndexList selection = ui->lista10->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        ezona *edit = new ezona(idIndex.row(), model, "Modificar Zona", this);
        int accepted = edit->exec();
        ui->informacion10->hide();

        if (accepted == 1) {
            ui->informacionlabel10->setText(" Los datos se \n guardaron \n correctamente ");
            ui->informacion10->show();
        }

    } else {
        ui->informacionlabel10->setText(" Seleccione la\n zona que\n desee modificar");
        ui->informacion10->show();
    }

}
void Gzonas::DelItem10()
{
        ui->informacion10->hide();
        QModelIndexList selection = ui->lista10->selectionModel()->selectedRows(0);
        if (!selection.empty()) {
            QModelIndex idIndex = selection.at(0);

            mensajebox *add = new mensajebox("Borrar zona", "Esta seguro de eliminar?", this);
            int accepted = add->exec();
            if (accepted == 1) {
                model->removeRow(idIndex.row());
                ui->informacionlabel10->setText("  La zona \n fue eliminada");
                ui->informacion10->show();
            }
        } else {
            ui->informacionlabel10->setText(" Seleccione la\n zona que\n desee eliminar");
            ui->informacion10->show();

        }
}
