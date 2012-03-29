#include "rgventa.h"
#include "ui_rgventa.h"

#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"

rgventa::rgventa(const QString &codven,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rgventa)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("dventas");
    model->select();
    model->setFilter(codven);

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

rgventa::~rgventa()
{
    delete ui;
}
void rgventa::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Ventas", this);
    dialog->exec();
}
