#include "rventas.h"
#include "ui_rventas.h"
#include "rgventa.h"
#include "ui_rgventa.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


rventas::rventas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rventas)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("Venta");
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
    connect( ui->pushButton, SIGNAL(clicked()), this, SLOT(Verdetalle()));
}

rventas::~rventas()
{
    delete ui;
}

void rventas::changeEvent(QEvent *e)
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
void rventas::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Ventas", this);
    dialog->exec();
}
void rventas::Verdetalle()
{

    QModelIndexList selection = ui->lista->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex index = selection.at(0);
        QSqlRecord record = model->record(index.row());
        QString Id_asig = record.value("Id_asig").toString();

    rgventa *dialog = new rgventa(Id_asig, this);
    dialog->exec();
}
}
