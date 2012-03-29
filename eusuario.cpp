#include "eusuario.h"
#include "ui_eusuario.h"
#include "QtSql"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include "qdatawidgetmapper.h"

eusuario::eusuario(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eusuario)
{
    ui->setupUi(this);
    this->setWindowTitle(titulo);
    model =modelo;
    ui->informacion->hide();
    QRegExp regExp("[A-Za-z]{1,15}");
    ui->a->setValidator(new QIntValidator(0, 9999999, this));
    ui->b->setValidator(new QRegExpValidator(regExp, this));
    ui->c->setValidator(new QRegExpValidator(regExp, this));
    ui->d->setValidator(new QRegExpValidator(regExp, this));
    ui->f->setValidator(new QIntValidator(0, 79999999, this));

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
        mapper->addMapping(ui->d, 3, "text");
        mapper->addMapping(ui->e, 4, "text");
        mapper->addMapping(ui->f, 5, "text");
        //mapper->addMapping(ui->g, 6, "text");
        mapper->addMapping(ui->h, 7, "text");

        mapper->setCurrentIndex(id);

    }else{
        sucursalmodel = new QSqlRelationalTableModel();
        sucursalmodel->setTable("sucursal");
        sucursalmodel->select();

        ui->editar->hide();
    }

}

eusuario::~eusuario()
{
    delete ui;
}

void eusuario::changeEvent(QEvent *e)
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

void eusuario::Aceptar()
{
    if (ui->a->text().isEmpty() || ui->b->text().isEmpty() ||
        ui->c->text().isEmpty() || ui->d->text().isEmpty() ||
        ui->e->text().isEmpty() || ui->f->text().isEmpty() ||
        ui->h->text().isEmpty())
    {
        ui->informacion->show();
    } else {
        mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
        int accepted = add->exec();
        if (accepted == 1) {

            QSqlRecord record;

            QSqlField f1("CI", QVariant::Int);
            QSqlField f2("Nombre", QVariant::String);
            QSqlField f3("Ap", QVariant::String);
            QSqlField f4("Am", QVariant::String);
            QSqlField f5("Direccion", QVariant::String);
            QSqlField f6("Telefono", QVariant::Int);
            QSqlField f7("Rol", QVariant::Int);
            QSqlField f8("Contrasena", QVariant::String);


            f1.setValue(QVariant(ui->a->text().toInt()));
            f2.setValue(QVariant(ui->b->text()));
            f3.setValue(QVariant(ui->c->text()));
            f4.setValue(QVariant(ui->d->text()));
            f5.setValue(QVariant(ui->e->text()));
            f6.setValue(QVariant(ui->f->text().toInt()));
            f7.setValue(QVariant(1));
            f8.setValue(QVariant(ui->h->text()));

            record.append(f1);
            record.append(f2);
            record.append(f3);
            record.append(f4);
            record.append(f5);
            record.append(f6);
            record.append(f7);
            record.append(f8);

            model->insertRecord(-1, record);
            accept();
        }

    }

}

void eusuario::Editar()
{
    if (ui->a->text().isEmpty() || ui->b->text().isEmpty() ||
        ui->c->text().isEmpty() || ui->d->text().isEmpty() ||
        ui->e->text().isEmpty() || ui->f->text().isEmpty() ||
        ui->h->text().isEmpty())
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
