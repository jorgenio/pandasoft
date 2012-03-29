#include "rproducto.h"
#include "ui_rproducto.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


rproducto::rproducto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rproducto)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("producto");
    model->setRelation(8, QSqlRelation("sucursal", "Id_suc", "Nombre"));
    model->select();
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Almacen"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));

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

rproducto::~rproducto()
{
    delete ui;
}

void rproducto::changeEvent(QEvent *e)
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
void rproducto::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Productos", this);
    dialog->exec();
}
