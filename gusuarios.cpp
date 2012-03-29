#include "gusuarios.h"
#include "ui_gusuarios.h"
#include "eusuario.h"
#include "ui_eusuario.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qlistwidget.h"

Gusuarios::Gusuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gusuarios)
{
    ui->setupUi(this);

    ui->informacion8->hide();

    model = new QSqlRelationalTableModel(this);
    model->setTable("usuario");
    model->setRelation(8, QSqlRelation("sucursal", "Id_suc", "Nombre"));
    model->select();
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Sucursal"));
    model->removeColumn(8);

    ui->lista8->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista8->setSortingEnabled(true);
    ui->lista8->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista8->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista8->setShowGrid(false);
    ui->lista8->verticalHeader()->hide();
    ui->lista8->setAlternatingRowColors(true);
    ui->lista8->setModel(model);
    ui->lista8->hideColumn(7);

    connect( ui->addbutton8, SIGNAL(clicked()), this, SLOT(AddItem8()) );
    connect( ui->modbutton8, SIGNAL(clicked()), this, SLOT(EditItem8()) );
    connect( ui->delbutton8, SIGNAL(clicked()), this, SLOT(DelItem8()) );

}

Gusuarios::~Gusuarios()
{
    delete ui;
}

void Gusuarios::AddItem8()
{
    eusuario *add = new eusuario(-1, model, "Adicionar Usuario", this);
    int accepted = add->exec();
    ui->informacion8->hide();

    if (accepted == 1) {
        ui->informacionlabel8->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion8->show();
    }


}
void Gusuarios::EditItem8()
{
    ui->informacion8->hide();
    QModelIndexList selection = ui->lista8->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        eusuario *edit = new eusuario(idIndex.row(), model, "Modificar Usuario", this);
        int accepted = edit->exec();
        ui->informacion8->hide();

        if (accepted == 1) {
        ui->informacionlabel8->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion8->show();
        }

    } else {
        ui->informacionlabel8->setText(" Seleccione el\n usuario que\n desee modificar");
        ui->informacion8->show();
    }


}
void Gusuarios::DelItem8()
{
    ui->informacion8->hide();
    QModelIndexList selection = ui->lista8->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);

        mensajebox *add = new mensajebox("Borrar usuario", "Esta seguro de eliminar?", this);
        int accepted = add->exec();
        if (accepted == 1) {
            model->removeRow(idIndex.row());
            ui->informacionlabel8->setText("  El usuario \n fue eliminado");
            ui->informacion8->show();
        }

    } else {
        ui->informacionlabel8->setText(" Seleccione el\n usuario que\n desee eliminar");
        ui->informacion8->show();

    }
}
