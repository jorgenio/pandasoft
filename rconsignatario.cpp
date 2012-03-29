#include "rconsignatario.h"
#include "ui_rconsignatario.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


rconsignatario::rconsignatario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rconsignatario)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("consignatario");
    model->setRelation(5, QSqlRelation("zona", "Id_zon", "nombre"));
    model->select();
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Zona"));
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

rconsignatario::~rconsignatario()
{
    delete ui;
}

void rconsignatario::changeEvent(QEvent *e)
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
void rconsignatario::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Consignatarios", this);
    dialog->exec();
}
