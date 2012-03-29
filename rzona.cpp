#include "rzona.h"
#include "ui_rzona.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


rzona::rzona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rzona)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("zona");
    model->setRelation(3, QSqlRelation("sucursal", "Id_suc", "Nombre"));
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sucursal"));

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

rzona::~rzona()
{
    delete ui;
}

void rzona::changeEvent(QEvent *e)
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
void rzona::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Zona", this);
    dialog->exec();
}
