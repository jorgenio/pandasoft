#include "gconsignatarios.h"
#include "ui_gconsignatarios.h"

#include "econsignatarios.h"
#include "ui_econsignatarios.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qlistwidget.h"

Gconsignatarios::Gconsignatarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gconsignatarios)
{
    ui->setupUi(this);

    ui->informacion3->hide();

    model = new QSqlRelationalTableModel(this);
    model->setTable("consignatario");
    model->setRelation(5, QSqlRelation("zona", "Id_zon", "nombre"));
    model->select();
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Zona"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));

    ui->lista3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista3->setSortingEnabled(true);
    ui->lista3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista3->setShowGrid(false);
    ui->lista3->verticalHeader()->hide();
    ui->lista3->setAlternatingRowColors(true);
    ui->lista3->setModel(model);

    connect( ui->addbutton3, SIGNAL(clicked()), this, SLOT(AddItem3()) );
    connect( ui->modbutton3, SIGNAL(clicked()), this, SLOT(EditItem3()) );
    connect( ui->delbutton3, SIGNAL(clicked()), this, SLOT(DelItem3()) );

}


Gconsignatarios::~Gconsignatarios()
{
    delete ui;
}
//gconsignatario
void Gconsignatarios::AddItem3()
{
    econsignatarios *add = new econsignatarios(-1, model, "Adicionar Consignatario", this);
    int accepted = add->exec();
    ui->informacion3->hide();

    if (accepted == 1) {
        ui->informacionlabel3->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion3->show();
    }

}
void Gconsignatarios::EditItem3()
{
    ui->informacion3->hide();
    QModelIndexList selection = ui->lista3->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        econsignatarios *edit = new econsignatarios(idIndex.row(), model, "Modificar Consignatario", this);
        int accepted = edit->exec();
        ui->informacion3->hide();

        if (accepted == 1) {
        ui->informacionlabel3->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion3->show();
        }

    } else {
        ui->informacionlabel3->setText(" Seleccione el\n consignatario que\n desee modificar");
        ui->informacion3->show();
    }
}
void Gconsignatarios::DelItem3()
{

    ui->informacion3->hide();
    QModelIndexList selection = ui->lista3->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        mensajebox *add = new mensajebox("Borrar consignatario ", "Esta seguro de eliminar?", this);
        int accepted = add->exec();
        if (accepted == 1) {
            model->removeRow(idIndex.row());
            ui->informacionlabel3->setText("El consignatario \nfue eliminado");
            ui->informacion3->show();
        }
    } else {
        ui->informacionlabel3->setText("Seleccione el\nconsignatario que\n desee eliminar");
        ui->informacion3->show();

    }
}


