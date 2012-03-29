#include "pandasoft.h"

#include "ui_pandasoft.h"
#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"

#include "qmessagebox.h"
#include "QtSql"
#include "qlistwidget.h"

#include "eusuario.h"
#include "ui_eusuario.h"
#include "esucursal.h"
#include "ui_esucursal.h"

#include "eproducto.h"
#include "ui_eproducto.h"
#include "aboutpandasoft.h"
#include "ui_aboutpandasoft.h"

#include "galmacen.h"
#include "gconsignaciones.h"
#include "gconsignatarios.h"
#include "gempleados.h"
#include "gproductos.h"
#include "greportes.h"
#include "gsucursal.h"
#include "gusuarios.h"
#include "gventas.h"
#include "gzonas.h"
#include "ui_galmacen.h"
#include "ui_gconsignaciones.h"
#include "ui_gconsignatarios.h"
#include "ui_gempleados.h"
#include "ui_gproductos.h"
#include "ui_greportes.h"
#include "ui_gsucursal.h"
#include "ui_gusuarios.h"
#include "ui_gventas.h"
#include "ui_gzonas.h"
#include "qsqlquerymodel.h"
QString rolusu="";

pandasoft::pandasoft(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pandasoft)
{
    ui->setupUi(this);

    this->setWindowTitle("Acceso al Sistema - Pandasoft");
    ui->pandasoftstackedWidget->setCurrentIndex(0);
    ui->error->hide();
    ui->error0->hide();
    sucursalmodel = new QSqlRelationalTableModel();
    sucursalmodel->setTable("sucursal");
    sucursalmodel->select();

    ui->sucursalcombo->setModel(sucursalmodel);
    ui->sucursalcombo->setModelColumn(4);
    connect( ui->aceptar, SIGNAL(clicked()), this, SLOT(Principal()) );
    connect( ui->cancelar, SIGNAL(clicked()), this, SLOT(close()) );
    connect( ui->salir, SIGNAL(clicked()), this, SLOT(close()) );




    //principal
    ui->imagelabel->setPixmap(QPixmap(":/images/pandasoft2.png"));

    connect( ui->action_Salir, SIGNAL(triggered()), this, SLOT(close()) );
    connect( ui->actionAcerca_de_Pandasoft, SIGNAL(triggered()), this, SLOT(aboutpandasoft()) );
    connect( ui->actionGestionar_Almacen, SIGNAL(triggered()), this, SLOT(GAlmacen()) );
    connect( ui->actionGestionar_Empleado, SIGNAL(triggered()), this, SLOT(GEmpleado()) );
    connect( ui->actionGestionar_Productos, SIGNAL(triggered()), this, SLOT(GProductos()) );
    connect( ui->actionGestionar_Reportes, SIGNAL(triggered()), this, SLOT(GReportes()) );
    connect( ui->actionGestion_de_Sucursal, SIGNAL(triggered()), this, SLOT(GSucursal()) );
    connect( ui->actionGestionar_Usuarios, SIGNAL(triggered()), this, SLOT(GUsuarios()) );
    connect( ui->actionGestionar_Ventas, SIGNAL(triggered()), this, SLOT(GVentas()) );
    connect( ui->actionGestionar_Zona, SIGNAL(triggered()), this, SLOT(GZona()) );
    connect( ui->actionGestionar_Consignatario, SIGNAL(triggered()), this, SLOT(GConsignatario()));
    connect( ui->actionGestionar_Consignacion, SIGNAL(triggered()), this, SLOT(GConsignaciones()));

    ui->menubar->hide();

}

pandasoft::~pandasoft()
{

    delete ui;
}
void pandasoft::Principal()
{
    ui->error->hide();
    ui->error0->hide();
    ui->usuario->setStyleSheet("background-color: none;");
    ui->clave->setStyleSheet("background-color: none;");

    if(ui->usuario->text().isEmpty()||ui->clave->text().isEmpty()){
        if(ui->usuario->text().isEmpty()){
            ui->error->show();
            ui->usuario->setStyleSheet("background-color: red;");
        }
        if(ui->clave->text().isEmpty()){
            ui->error->show();
            ui->clave->setStyleSheet("background-color: red;");
        }
    }
    else {
    QSqlQueryModel model;
    QString consulta="select Nombre, Ap, Am, Rol from Usuario where (Nombre='"+ui->usuario->text()+"' and Contrasena='"+ui->clave->text()+"' )";
    model.setQuery(consulta);

    if(model.record(0).value("Rol").toString()==""){
    ui->error0->show();
    }else{
    QString rol = model.record(0).value("Rol").toString();
    rolusu=rol;
    QString usuario = model.record(0).value("Nombre").toString()+" "+model.record(0).value("Ap").toString()+" "+model.record(0).value("Am").toString();
    this->setWindowTitle("Principal");
    ui->pandasoftstackedWidget->setCurrentIndex(1);
    ui->menubar->show();
    if(rolusu=="1"){
    ui->menuMenu_Gerente->setEnabled(false);
    ui->cabecera->setText("Bienvenido Usuario: "+usuario+"           Rol : Jefe de Almacen");

    }else{
        ui->cabecera->setText("Bienvenido Usuario: "+usuario+"            Rol : Gerente");
    }
    }
    ui->alertalista->setEnabled(false);
    QString alerta="select Nombre from Producto where Cantidad<Lim_stock";
    model.setQuery(alerta);
    ui->alertalista->setText(model.record(0).value("Nombre").toString());

}
}
void pandasoft::GAlmacen()
{
Galmacen *dialogo = new Galmacen(this);
dialogo->exec();
}
void pandasoft::GEmpleado()
{
    Gempleados *dialogo = new Gempleados(this);
    dialogo->exec();
}
void pandasoft::GProductos()
{

    Gproductos *dialogo = new Gproductos(this);
    dialogo->exec();

}
void pandasoft::GReportes()
{
    Greportes *dialogo = new Greportes(rolusu, this);
    dialogo->exec();
}
void pandasoft::GSucursal()
{

    Gsucursal *dialogo = new Gsucursal(this);
    dialogo->exec();
}
void pandasoft::GUsuarios()
{
    Gusuarios *dialogo = new Gusuarios(this);
    dialogo->exec();
}
void pandasoft::GVentas()
{
    Gventas *dialogo = new Gventas(this);
    dialogo->exec();
}
void pandasoft::GZona()
{
    Gzonas *dialogo = new Gzonas(this);
    dialogo->exec();
}
void pandasoft::GConsignatario()
{

    Gconsignatarios *dialogo = new Gconsignatarios(this);
    dialogo->exec();
}
void pandasoft::GConsignaciones()
{

    Gconsignaciones *dialogo = new Gconsignaciones(this);
    dialogo->exec();
}

void pandasoft::aboutpandasoft(){
    aboutPandasoft *add = new aboutPandasoft(this);
    add->exec();
}
