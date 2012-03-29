#include "rconsignaciones.h"
#include "ui_rconsignaciones.h"
#include "rdconsignaciones.h"
#include "ui_rdconsignaciones.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"

rconsignaciones::rconsignaciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rconsignaciones)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("Asignar");
    model->select();


    ui->lista->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista->setSortingEnabled(true);
    ui->lista->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista->setShowGrid(false);
    ui->lista->verticalHeader()->hide();
    ui->lista->setAlternatingRowColors(true);
    ui->lista->setModel(model);

    connect( ui->print, SIGNAL(clicked()), this, SLOT(Imprimir()));

}

rconsignaciones::~rconsignaciones()
{
    delete ui;
}
void rconsignaciones::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Consignaciones", this);
    dialog->exec();
}
void rconsignaciones::Verdetalle()
{

    QModelIndexList selection = ui->lista->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex index = selection.at(0);
        QSqlRecord record = model->record(index.row());
        QString Id_asig = record.value("Id_asig").toString();

    rdconsignaciones *dialog = new rdconsignaciones(Id_asig, this);
    dialog->exec();
}

}
