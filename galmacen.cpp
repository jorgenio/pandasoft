#include "galmacen.h"
#include "ui_galmacen.h"
#include "reproductos.h"
#include "ui_reproductos.h"
#include "sproducto.h"
#include "ui_sproducto.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qlistwidget.h"
Galmacen::Galmacen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Galmacen)
{
    ui->setupUi(this);
    ui->informacion1->hide();

    connect( ui->reproducto, SIGNAL(clicked()), this, SLOT(REproductos()) );
    connect( ui->sproducto, SIGNAL(clicked()), this, SLOT(SProductos()) );

}

Galmacen::~Galmacen()
{
    delete ui;
}
void Galmacen::REproductos()
{
    reproductos dlg(this);
dlg.exec();
}
void Galmacen::SProductos()
{
    sproducto dlg( this );
    dlg.exec();
}
