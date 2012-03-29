#include "rempleado.h"
#include "ui_rempleado.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


rempleado::rempleado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rempleado)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("empleado");
    model->setRelation(7, QSqlRelation("sucursal", "Id_suc", "Nombre"));
    model->select();
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sucursal"));

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

rempleado::~rempleado()
{
    delete ui;
}

void rempleado::changeEvent(QEvent *e)
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
void rempleado::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Empleado", this);
    dialog->exec();
}
