#include "rusuario.h"
#include "ui_rusuario.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"


rusuario::rusuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rusuario)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("usuario");
    model->setRelation(8, QSqlRelation("sucursal", "Id_suc", "Nombre"));
    model->select();
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Sucursal"));



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

rusuario::~rusuario()
{
    delete ui;
}

void rusuario::changeEvent(QEvent *e)
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
void rusuario::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Usuario", this);
    dialog->exec();
}
