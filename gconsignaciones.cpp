#include "gconsignaciones.h"
#include "ui_gconsignaciones.h"

#include "QtGui"
#include "QtSql"
#include "qstringlist.h"
#include "qstringlistmodel.h"
#include "database.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qlistwidget.h"

int idunicoasignar=0;
double total=0;
QString idasignar;
Gconsignaciones::Gconsignaciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gconsignaciones)
{
    ui->setupUi(this);
    ui->costo2spinbox->hide();
    ui->codven2spinbox->hide();
    ui->id2spinbox->hide();

    ui->dasignarw->setCurrentIndex(2);
    ui->informacionproductoadicionado->hide();
    ui->informaciondasignaradicionado->hide();
    ui->total2->setDisabled(true);



    connect( ui->addproductoDasignar, SIGNAL(clicked()), this, SLOT(AddDasignar()) );
    connect( ui->productocomboBox2, SIGNAL(currentIndexChanged(QString)), this, SLOT(CargarDasignar()));
    connect( ui->addbutton2, SIGNAL(clicked()), this, SLOT(nuevoasignar()));
    connect( ui->addasignar, SIGNAL(clicked()), this, SLOT(Addasignar()) );

    connect(ui->lista2, SIGNAL(clicked(QModelIndex)), this, SLOT(showasignarDetails(QModelIndex)));

    connect( ui->cancelar, SIGNAL(clicked()), this, SLOT(CAncelar()) );
    connect( ui->modificar, SIGNAL(clicked()), this, SLOT(modificarasignar()) );
    connect( ui->vendidobutton, SIGNAL(clicked()), this, SLOT(Vendido()) );
    connect( ui->pendiente, SIGNAL(clicked()), this, SLOT(Pendiente()) );
    connect( ui->eliminar, SIGNAL(clicked()), this, SLOT(Eliminar()) );

    model = new QSqlRelationalTableModel(this);
    model->setTable("Asignar");
    model->setRelation(4, QSqlRelation("Consignatario", "Id_con", "nombre"));
    model->select();
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Consignatario"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));

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

    consignatariomodel = new QSqlRelationalTableModel();
    consignatariomodel->setTable("Consignatario");
    consignatariomodel->select();
    ui->consignatariocombo2->setModel(consignatariomodel);
    ui->consignatariocombo2->setModelColumn(1);


}

Gconsignaciones::~Gconsignaciones()
{
    delete ui;
}
void Gconsignaciones::AddDasignar(){
    mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
    int accepted = add->exec();
    if (accepted == 1) {

        QSqlRecord record;

        QSqlField f1("Id_asig", QVariant::Int);
        QSqlField f2("Id_pro", QVariant::Int);
        QSqlField f3("Cantidad", QVariant::Int);
        QSqlField f4("Costo", QVariant::Double);
        total =total+(ui->costo2spinbox->value()*ui->cantidad2->value());
        f1.setValue(QVariant(idunicoasignar));
        f2.setValue(QVariant(ui->id2spinbox->text().toInt(0, 10)));
        f3.setValue(QVariant(ui->cantidad2->value()));
        f4.setValue(QVariant(ui->costo2spinbox->value()*ui->cantidad2->value()));

        record.append(f1);
        record.append(f2);
        record.append(f3);
        record.append(f4);

        ui->total2->setValue(total);;
        modelodasignar->insertRecord(-1, record);
        ui->informacionproductoadicionado->show();

    }
}
void Gconsignaciones::CargarDasignar(){
    QSqlQueryModel idunicomodel;
    QString selec="SELECT Id_pro, cantidad, Pconsig FROM Producto where (nombre='"+ui->productocomboBox2->currentText()+"')";
    idunicomodel.setQuery(selec);
    int id_pro=idunicomodel.record(0).value("Id_pro").toInt();
    int cantidad=idunicomodel.record(0).value("cantidad").toInt();
    double precio=idunicomodel.record(0).value("Pconsig").toDouble();
    ui->costo2spinbox->setValue(precio);
    ui->cantidad2->setRange(1, cantidad);
    ui->id2spinbox->setValue(id_pro);
}
void Gconsignaciones::nuevoasignar(){
    ui->pendienteradio->show();
    ui->realizadoradio->show();
    ui->estadolabel->show();
    ui->dasignarw->setCurrentIndex(0);
    ui->pendiente->hide();
    ui->vendidobutton->hide();
    ui->consignatario->hide();
    ui->consignatariocombo2->show();
    ui->addasignar->show();
    ui->cancelar->show();
    ui->eliminar->hide();
    QSqlQueryModel idunicomodel;
    idunicomodel.setQuery("SELECT Id_asig FROM Asignar ORDER by Id_asig DESC");
    idunicoasignar=idunicomodel.record(0).value("Id_asig").toInt()+1;
    ui->codven2spinbox->setValue(idunicoasignar);


    modelodasignar = new QSqlRelationalTableModel(this);
    modelodasignar->setTable("Dasignar");
    modelodasignar->setRelation(1, QSqlRelation("Producto", "Id_pro", "nombre"));
    modelodasignar->setHeaderData(1, Qt::Horizontal, QObject::tr("Producto"));
    modelodasignar->select();

    QString filtro="Id_asig = "+ui->codven2spinbox->text();
    modelodasignar->setFilter(filtro);

    ui->listadasignar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listadasignar->setSortingEnabled(true);
    ui->listadasignar->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listadasignar->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listadasignar->setShowGrid(false);
    ui->listadasignar->verticalHeader()->hide();
    ui->listadasignar->setAlternatingRowColors(true);
    ui->listadasignar->setModel(modelodasignar);



}
void Gconsignaciones::modificarasignar(){
    ui->pendienteradio->hide();
    ui->realizadoradio->hide();
    ui->estadolabel->hide();
    ui->eliminar->show();
    QModelIndexList selection = ui->lista2->selectionModel()->selectedRows(0);
    if (!selection.empty()) {
        QModelIndex index = selection.at(0);

        ui->dasignarw->setCurrentIndex(0);
        ui->pendiente->show();
        ui->vendidobutton->show();
        ui->consignatario->show();
        ui->consignatariocombo2->hide();
        ui->addasignar->hide();
        ui->cancelar->hide();
        QSqlRecord record = model->record(index.row());
        QString Id_asig = record.value("Id_asig").toString();
        QString consignatario = record.value("nombre").toString();
        QString total=record.value("total").toString();
        QString estado=record.value("estado").toString();
        if(estado!="Pendiente"){
        ui->dasignarw->setCurrentIndex(1);
        }
        ui->total2->setValue(total.toInt());
        ui->codven2spinbox->setValue(Id_asig.toInt());
        ui->consignatario->setText(consignatario);

        modelodasignar = new QSqlRelationalTableModel(this);
        modelodasignar->setTable("Dasignar");
        modelodasignar->setRelation(1, QSqlRelation("Producto", "Id_pro", "nombre"));
        modelodasignar->setHeaderData(1, Qt::Horizontal, QObject::tr("Producto"));
        modelodasignar->select();

        QString filtro="Id_asig = "+Id_asig;
        modelodasignar->setFilter(filtro);

        ui->listadasignar->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->listadasignar->setSortingEnabled(true);
        ui->listadasignar->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->listadasignar->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->listadasignar->setShowGrid(false);
        ui->listadasignar->verticalHeader()->hide();
        ui->listadasignar->setAlternatingRowColors(true);
        ui->listadasignar->setModel(modelodasignar);




        model = new QSqlRelationalTableModel(this);
        model->setTable("Asignar");
        model->select();
        mapper = new QDataWidgetMapper(this);
        mapper->setModel(model);
        mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
        mapper->setItemDelegate(new QSqlRelationalDelegate(mapper));
        mapper->addMapping(ui->estado, 1, "text");
        mapper->setCurrentIndex(index.row());

    }






}
void Gconsignaciones::Addasignar(){
    mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
    int accepted = add->exec();
    if (accepted == 1) {
        QSqlRecord record;
        QSqlField f1("Id_asig", QVariant::Int);
        QSqlField f2("Estado", QVariant::String);
        QSqlField f3("Fecha", QVariant::Date);
        QSqlField f4("Total", QVariant::Double);
        QSqlField f5("Id_con", QVariant::Int);
        QSqlQueryModel idunicomodel;
        QString selec="SELECT Id_con FROM Consignatario where (Nombre='"+ui->consignatariocombo2->currentText()+"')";
        idunicomodel.setQuery(selec);
        int consignatarioid=idunicomodel.record(0).value("Id_con").toInt();
        QString estado="";
        if(ui->realizadoradio->isChecked()==true)
        {
            estado=ui->realizadoradio->text();
        }else{
        estado=ui->pendienteradio->text();
        }
        f1.setValue(QVariant(idunicoasignar));
        f2.setValue(QVariant(estado));
        f3.setValue(QVariant(QDate::currentDate()));
        f4.setValue(QVariant(total));
        f5.setValue(QVariant(consignatarioid));


        record.append(f1);
        record.append(f2);
        record.append(f3);
        record.append(f4);
        record.append(f5);

        model->insertRecord(-1, record);
        total=0;
        ui->informaciondasignaradicionado->show();
        ui->dasignarw->setCurrentIndex(2);

    }
}

void Gconsignaciones::showasignarDetails(QModelIndex index)
{
    ui->dasignarw->setCurrentIndex(1);
    QSqlRecord record = model->record(index.row());

    QString Id_asig = record.value("Id_asig").toString();
    QString fecha = record.value("fecha").toString();
    QString total = record.value("total").toString();
    QString consignatario = record.value("nombre").toString();
    QString estado = record.value("estado").toString();


    ui->dasignarid->setText(Id_asig);
    ui->dasignarfecha->setText(fecha);
    ui->dasignartotal->setText(total+" Bs.");
    ui->dasignarconsignatario->setText(consignatario);
    ui->estado->setText(estado);

    modelodasignar = new QSqlRelationalTableModel(this);
    modelodasignar->setTable("Dasignar");
    modelodasignar->setRelation(1, QSqlRelation("Producto", "Id_pro", "nombre"));
    modelodasignar->setHeaderData(1, Qt::Horizontal, QObject::tr("Producto"));
    modelodasignar->select();
    QString filtro="Id_asig = "+Id_asig;
    modelodasignar->setFilter(filtro);

    ui->dasignardetalle->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dasignardetalle->setSortingEnabled(true);
    ui->dasignardetalle->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dasignardetalle->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dasignardetalle->setShowGrid(false);
    ui->dasignardetalle->verticalHeader()->hide();
    ui->dasignardetalle->setAlternatingRowColors(true);
    ui->dasignardetalle->setModel(modelodasignar);

}

void Gconsignaciones::CAncelar()
{
    QSqlQuery query;
    QString consulta="delete from dasignar where Id_asig="+ui->codven2spinbox->text();
    query.exec(consulta);

    ui->dasignarw->setCurrentIndex(2);
}
void Gconsignaciones::Eliminar()
{
    QSqlQuery query;
    QString consulta="delete from asignar where Id_asig="+ui->codven2spinbox->text();
    query.exec(consulta);
    consulta="delete from dasignar where Id_asig="+ui->codven2spinbox->text();
    query.exec(consulta);
    ui->label2->setText(consulta);
    ui->dasignarw->setCurrentIndex(2);

    model = new QSqlRelationalTableModel(this);
    model->setTable("Asignar");
    model->setRelation(4, QSqlRelation("Consignatario", "Id_con", "nombre"));
    model->select();
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Consignatario"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));

    ui->lista2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lista2->setSortingEnabled(true);
    ui->lista2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lista2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lista2->setShowGrid(false);
    ui->lista2->verticalHeader()->hide();
    ui->lista2->setAlternatingRowColors(true);
    ui->lista2->setModel(model);
}

void Gconsignaciones::Vendido(){
    ui->estado->setText("Realizado");
    mapper->submit();
    ui->dasignarw->setCurrentIndex(2);
    model->select();
    ui->lista2->setModel(model);
}

void Gconsignaciones::Pendiente(){
ui->dasignarw->setCurrentIndex(2);
}


