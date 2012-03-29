#include "rsucursal.h"
#include "ui_rsucursal.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


rsucursal::rsucursal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rsucursal)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("sucursal");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));


    ui->lista->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista->setSortingEnabled(true);
    ui->lista->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista->setShowGrid(false);
    ui->lista->verticalHeader()->hide();
    ui->lista->setAlternatingRowColors(true);
    ui->lista->setModel(model);
    ui->lista->hideColumn(7);

    connect( ui->print, SIGNAL(clicked()), this, SLOT(Imprimir()));
}

rsucursal::~rsucursal()
{
    delete ui;
}

void rsucursal::changeEvent(QEvent *e)
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
void rsucursal::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Sucursales", this);
    dialog->exec();
}
