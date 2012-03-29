#include "gproductos.h"
#include "ui_gproductos.h"

#include "eproducto.h"
#include "ui_eproducto.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qlistwidget.h"

Gproductos::Gproductos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gproductos)
{
    ui->setupUi(this);

    ui->informacion5->hide();

    model = new QSqlRelationalTableModel(this);
    model->setTable("producto");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));

    ui->lista5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista5->setSortingEnabled(true);
    ui->lista5->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista5->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista5->setShowGrid(false);
    ui->lista5->verticalHeader()->hide();
    ui->lista5->setAlternatingRowColors(true);
    ui->lista5->setModel(model);


    connect( ui->addbutton5, SIGNAL(clicked()), this, SLOT(AddItem5()) );
    connect( ui->modbutton5, SIGNAL(clicked()), this, SLOT(EditItem5()) );
    connect( ui->delbutton5, SIGNAL(clicked()), this, SLOT(DelItem5()) );

}

Gproductos::~Gproductos()
{
    delete ui;
}
void Gproductos::AddItem5()
{

    eproducto *add = new eproducto(-1, model, "Adicionar Producto", this);
    int accepted = add->exec();
    ui->informacion5->hide();

    if (accepted == 1) {
        ui->informacionlabel5->setText(" Los datos se \n guardaron \n correctamente ");
        ui->informacion5->show();
    }

}
void Gproductos::EditItem5()
{
    ui->informacion5->hide();
    QModelIndexList selection = ui->lista5->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        eproducto *edit = new eproducto(idIndex.row(), model, "Modificar Producto", this);
        int accepted = edit->exec();
        ui->informacion5->hide();

        if (accepted == 1) {
             ui->informacionlabel5->setText(" Los datos se \n guardaron \n correctamente ");
             ui->informacion5->show();
        }

    } else {
        ui->informacionlabel5->setText(" Seleccione el\n producto que\n desee modificar");
        ui->informacion5->show();
    }

}
void Gproductos::DelItem5()
{

        ui->informacion5->hide();
        QModelIndexList selection = ui->lista5->selectionModel()->selectedRows(0);
        if (!selection.empty()) {
            QModelIndex idIndex = selection.at(0);
            mensajebox *add = new mensajebox("Borrar producto", "Esta seguro de eliminar?", this);
            int accepted = add->exec();
            if (accepted == 1) {
                model->removeRow(idIndex.row());
                ui->informacionlabel5->setText("  El producto \n fue eliminado");
                ui->informacion5->show();
            }
        } else {
            ui->informacionlabel5->setText(" Seleccione el\n producto que\n desee eliminar");
            ui->informacion5->show();

        }
}
