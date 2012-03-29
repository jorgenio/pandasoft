#include "ralmacen.h"
#include "ui_ralmacen.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


ralmacen::ralmacen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ralmacen)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("producto");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Producto"));

    ui->lista->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista->setSortingEnabled(true);
    ui->lista->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista->setShowGrid(false);
    ui->lista->verticalHeader()->hide();
    ui->lista->setAlternatingRowColors(true);
    ui->lista->setModel(model);
    ui->lista->hideColumn(2);
    ui->lista->hideColumn(3);
    ui->lista->hideColumn(5);
    ui->lista->hideColumn(6);
    ui->lista->hideColumn(7);


    connect( ui->print, SIGNAL(clicked()), this, SLOT(Imprimir()));
}

ralmacen::~ralmacen()
{
    delete ui;
}

void ralmacen::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void ralmacen::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Almacen", this);
    dialog->exec();
}
