#include "gventas.h"
#include "ui_gventas.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

#include "qlistwidget.h"

int idunicoventas=0;
double totalventa=0;

Gventas::Gventas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gventas)
{
    ui->setupUi(this);
    ui->costo2spinbox->hide();
    ui->codven2spinbox->hide();
    ui->id2spinbox->hide();
    ui->dventasw->setCurrentIndex(2);
    ui->informacionproductoadicionado->hide();
    ui->informaciondventasadicionado->hide();
    ui->total2->setDisabled(true);

    model = new QSqlRelationalTableModel(this);
    model->setTable("venta");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("codven"));

    connect( ui->addproductoDventas, SIGNAL(clicked()), this, SLOT(AddDventas()) );
    connect( ui->productocomboBox2, SIGNAL(currentIndexChanged(QString)), this, SLOT(CargarDventas()));
    connect( ui->addbutton2, SIGNAL(clicked()), this, SLOT(nuevoventas()));
    connect( ui->addventas, SIGNAL(clicked()), this, SLOT(Addventas()) );
    connect( ui->lista2, SIGNAL(clicked(QModelIndex)), this, SLOT(showventasDetails(QModelIndex)));
    connect( ui->cancelar, SIGNAL(clicked()), this, SLOT(CAncelar()) );

    ui->lista2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista2->setSortingEnabled(true);
    ui->lista2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista2->setShowGrid(false);
    ui->lista2->verticalHeader()->hide();
    ui->lista2->setAlternatingRowColors(true);
    ui->lista2->setModel(model);

    productomodel = new QSqlRelationalTableModel();
    productomodel->setTable("Producto");
    productomodel->select();
    ui->productocomboBox2->setModel(productomodel);
    ui->productocomboBox2->setModelColumn(1);


}

Gventas::~Gventas()
{
    delete ui;
}
void Gventas::AddDventas(){
    mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
    int accepted = add->exec();
    if (accepted == 1) {

        QSqlRecord record;

        QSqlField f1("Id_ven", QVariant::Int);
        QSqlField f2("Id_pro", QVariant::Int);
        QSqlField f3("Cantidad", QVariant::Int);
        QSqlField f4("Costo", QVariant::Double);
        totalventa =totalventa+(ui->costo2spinbox->value()*ui->cantidad2->value());
        f1.setValue(QVariant(idunicoventas));
        f2.setValue(QVariant(ui->id2spinbox->text().toInt(0, 10)));
        f3.setValue(QVariant(ui->cantidad2->value()));
        f4.setValue(QVariant(ui->costo2spinbox->value()*ui->cantidad2->value()));

        record.append(f1);
        record.append(f2);
        record.append(f3);
        record.append(f4);

        ui->total2->setValue(totalventa);;
        modelodventa->insertRecord(-1, record);
        ui->informacionproductoadicionado->show();

    }
}
void Gventas::CargarDventas(){
    QSqlQueryModel idunicomodel;
    QString selec="SELECT Id_pro, cantidad, Punitario FROM Producto where (nombre='"+ui->productocomboBox2->currentText()+"')";
    idunicomodel.setQuery(selec);
    int id_pro=idunicomodel.record(0).value("Id_pro").toInt();
    int cantidad=idunicomodel.record(0).value("cantidad").toInt();
    double precio=idunicomodel.record(0).value("Punitario").toDouble();
    ui->costo2spinbox->setValue(precio);
    ui->cantidad2->setRange(1, cantidad);
    ui->id2spinbox->setValue(id_pro);
}
void Gventas::nuevoventas(){
    ui->dventasw->setCurrentIndex(0);
    QSqlQueryModel idunicomodel;
    idunicomodel.setQuery("SELECT Id_ven FROM Venta ORDER by Id_ven DESC");
    idunicoventas=idunicomodel.record(0).value("Id_ven").toInt()+1;
    ui->codven2spinbox->setValue(idunicoventas);

    modelodventa = new QSqlRelationalTableModel(this);
    modelodventa->setTable("Dventas");
    modelodventa->setRelation(1, QSqlRelation("Producto", "Id_pro", "nombre"));
    modelodventa->setHeaderData(1, Qt::Horizontal, QObject::tr("Producto"));
    modelodventa->select();

    QString filtro="Id_ven = "+ui->codven2spinbox->text();
    modelodventa->setFilter(filtro);

    ui->listadventas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listadventas->setSortingEnabled(true);
    ui->listadventas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listadventas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listadventas->setShowGrid(false);
    ui->listadventas->verticalHeader()->hide();
    ui->listadventas->setAlternatingRowColors(true);
    ui->listadventas->setModel(modelodventa);



}
void Gventas::Addventas(){
    mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
    int accepted = add->exec();
    if (accepted == 1) {
        QSqlRecord record;
        QSqlField f1("Id_ven", QVariant::Int);
        QSqlField f2("Fecha", QVariant::Date);
        QSqlField f3("Total", QVariant::Double);
        f1.setValue(QVariant(idunicoventas));
        f2.setValue(QVariant(QDate::currentDate()));
        f3.setValue(QVariant(totalventa));

        record.append(f1);
        record.append(f2);
        record.append(f3);

        model->insertRecord(-1, record);
        totalventa=0;
        ui->informaciondventasadicionado->show();
        ui->dventasw->setCurrentIndex(2);

    }
}

void Gventas::showventasDetails(QModelIndex index)
{
    ui->dventasw->setCurrentIndex(1);
    QSqlRecord record = model->record(index.row());

    QString Id_ven = record.value("Id_ven").toString();
    QString fecha = record.value("fecha").toString();
    QString total = record.value("total").toString();

    ui->dventasid->setText(Id_ven);
    ui->dventasfecha->setText(fecha);
    ui->dventastotal->setText(total+" Bs.");


    modelodventa = new QSqlRelationalTableModel(this);
    modelodventa->setTable("Dventas");
    modelodventa->setRelation(1, QSqlRelation("Producto", "Id_pro", "nombre"));
    modelodventa->setHeaderData(1, Qt::Horizontal, QObject::tr("Producto"));
    modelodventa->select();
    QString filtro="Id_ven = "+Id_ven;
    modelodventa->setFilter(filtro);

    ui->dventasdetalle->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dventasdetalle->setSortingEnabled(true);
    ui->dventasdetalle->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dventasdetalle->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dventasdetalle->setShowGrid(false);
    ui->dventasdetalle->verticalHeader()->hide();
    ui->dventasdetalle->setAlternatingRowColors(true);
    ui->dventasdetalle->setModel(modelodventa);

}

void Gventas::CAncelar()
{
    QSqlQuery query;
    QString consulta="delete from dventas where Id_ven="+ui->codven2spinbox->text();
    query.exec(consulta);
    ui->label2->setText(consulta);
    ui->dventasw->setCurrentIndex(2);
}
