#include "rdconsignaciones.h"
#include "ui_rdconsignaciones.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "QtSql"
#include "qlistwidget.h"
#include "qprinter.h"
#include "tdpreviewdialog.h"

rdconsignaciones::rdconsignaciones(const QString &codven, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rdconsignaciones)
{
    ui->setupUi(this);
}

rdconsignaciones::~rdconsignaciones()
{
    delete ui;
}
void rdconsignaciones::Imprimir()
{
    printer= new QPrinter(QPrinter::HighResolution);

    TDPreviewDialog *dialog = new TDPreviewDialog(ui->lista, printer, "Reportes de Ventas", this);
    dialog->exec();
}
