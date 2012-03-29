#include "ezona.h"
#include "ui_ezona.h"
#include "QtSql"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qsqlquerymodel.h"

ezona::ezona(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ezona)
{
    ui->setupUi(this);

    this->setWindowTitle(titulo);
    model =modelo;
    ui->informacion->hide();
    QRegExp regExp("[A-Za-z]{1,15}");

    ui->c->setValidator(new QIntValidator(0, 99999, this));

    connect( ui->aceptar, SIGNAL(clicked()), this, SLOT(Aceptar()) );
    connect( ui->editar, SIGNAL(clicked()), this, SLOT(Editar()) );
    if(id!=-1){
        ui->aceptar->hide();;
        mapper = new QDataWidgetMapper(this);
        mapper->setModel(modelo);
        mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
        mapper->setItemDelegate(new QSqlRelationalDelegate(mapper));
        mapper->addMapping(ui->a, 0, "text");
        mapper->addMapping(ui->b, 1, "text");
        mapper->addMapping(ui->c, 2, "text");

        mapper->setCurrentIndex(id);

    }else{
        sucursalmodel = new QSqlRelationalTableModel();
        sucursalmodel->setTable("sucursal");
        sucursalmodel->select();


        ui->editar->hide();
    }
}

ezona::~ezona()
{
    delete ui;
}

void ezona::changeEvent(QEvent *e)
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

void ezona::Aceptar()
{
    if (ui->b->text().isEmpty() ||
        ui->c->text().isEmpty())
    {
        ui->informacion->show();
    } else {
        mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
                int accepted = add->exec();
        if (accepted == 1) {
            QSqlRecord record;

            QSqlField f1("ID_zon", QVariant::Int);
            QSqlField f2("Nombre", QVariant::String);
            QSqlField f3("Alcance", QVariant::Int);

            QSqlQueryModel idunicomodel;
            idunicomodel.setQuery("SELECT Id_zon FROM Zona ORDER by id_zon DESC");
            int idunico=idunicomodel.record(0).value("Id_zon").toInt()+1;
            idunicomodel.clear();


            f1.setValue(QVariant(idunico));
            f2.setValue(QVariant(ui->b->text()));
            f3.setValue(QVariant(ui->c->text().toInt()));

            record.append(f1);
            record.append(f2);
            record.append(f3);
            model->insertRecord(-1, record);
            accept();
        }

    }

}


void ezona::Editar()
{
    if (ui->a->text().isEmpty() || ui->b->text().isEmpty() ||
        ui->c->text().isEmpty())
    {
        ui->informacion->show();
    } else {

        mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
        int accepted = add->exec();
        if (accepted == 1) {
            mapper->submit();
            accept();
        }

    }

}
