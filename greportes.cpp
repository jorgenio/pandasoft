#include "greportes.h"
#include "ui_greportes.h"

#include "ralmacen.h"
#include "ui_ralmacen.h"
#include "rempleado.h"
#include "ui_rempleado.h"
#include "rproducto.h"
#include "ui_rproducto.h"
#include "rsucursal.h"
#include "ui_rsucursal.h"
#include "rusuario.h"
#include "ui_rusuario.h"
#include "rventas.h"
#include "ui_rventas.h"
#include "rzona.h"
#include "ui_rzona.h"
#include "rconsignatario.h"
#include "ui_rconsignatario.h"
#include "rconsignaciones.h"
#include "ui_rconsignaciones.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "qlistwidget.h"

Greportes::Greportes(const QString &usurol,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Greportes)
{
    ui->setupUi(this);

    connect(ui->almacen, SIGNAL(clicked()), this, SLOT(Ralmacen()));
    connect(ui->empleado, SIGNAL(clicked()), this, SLOT(Rempleado()));
    connect(ui->productos, SIGNAL(clicked()), this, SLOT(Rproducto()));

    connect(ui->usuarior, SIGNAL(clicked()), this, SLOT(Rusuario()));
    connect(ui->ventas, SIGNAL(clicked()), this, SLOT(Rventas()));
    connect(ui->zona, SIGNAL(clicked()), this, SLOT(Rzona()));
    connect(ui->consignatario, SIGNAL(clicked()), this, SLOT(Rconsignatario()));
    connect(ui->consignaciones, SIGNAL(clicked()), this, SLOT(Rconsignaciones()));

    if(usurol=="1"){
    ui->empleado->hide();
    ui->zona->hide();
    ui->usuarior->hide();
    ui->consignatario->hide();
    }

}

Greportes::~Greportes()
{
    delete ui;
}
void Greportes::Ralmacen()
{

    ralmacen *dialogo = new ralmacen(this);
    dialogo->exec();
}
void Greportes::Rempleado()
{
    rempleado dlg( this );
    dlg.exec();
}
void Greportes::Rproducto()
{
    rproducto dlg( this );
    dlg.exec();
}

void Greportes::Rusuario()
{
    rusuario dlg( this );
    dlg.exec();
}
void Greportes::Rventas()
{
    rventas dlg( this );
    dlg.exec();
}
void Greportes::Rzona()
{
    rzona dlg( this );
    dlg.exec();
}
void Greportes::Rconsignatario()
{
    rconsignatario dlg( this );
    dlg.exec();
}
void Greportes::Rconsignaciones()
{
    rconsignaciones dlg( this );
    dlg.exec();
}
