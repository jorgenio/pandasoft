#include "econsignatarios.h"
#include "ui_econsignatarios.h"
#include "QtSql"
#include "mensajebox.h"
#include "ui_mensajebox.h"

econsignatarios::econsignatarios(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::econsignatarios)
{
    ui->setupUi(this);

    this->setWindowTitle(titulo);
    model =modelo;
    ui->informacion->hide();
    QRegExp regExp("[A-Za-z]{1,15}");
    ui->b->setValidator(new QRegExpValidator(regExp, this));
    ui->c->setValidator(new QRegExpValidator(regExp, this));
    ui->d->setValidator(new QRegExpValidator(regExp, this));
    ui->e->setValidator(new QIntValidator(0, 79999999, this));
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
        mapper->addMapping(ui->i, 5, "text");
        mapper->setCurrentIndex(id);
        ui->zonacombobox->hide();
        ui->labelzona->hide();
    }else{
        sucursalmodel = new QSqlRelationalTableModel();
        sucursalmodel->setTable("zona");
        sucursalmodel->select();

        ui->zonacombobox->setModel(sucursalmodel);
        ui->zonacombobox->setModelColumn(1);
        ui->label10->hide();
        ui->i->hide();
        ui->editar->hide();
    }
}

econsignatarios::~econsignatarios()
{
    delete ui;
}

void econsignatarios::changeEvent(QEvent *e)
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

void econsignatarios::Aceptar()
{
    if (ui->b->text().isEmpty() ||
        ui->c->text().isEmpty() )
    {
        ui->informacion->show();
    } else {

        mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
        int accepted = add->exec();
        if (accepted == 1) {

            QSqlRecord record;

            QSqlField f1("Id_con", QVariant::Int);
            QSqlField f2("Nombre", QVariant::String);
            QSqlField f3("Ap", QVariant::String);
            QSqlField f4("Am", QVariant::String);
            QSqlField f5("Telefono", QVariant::Int);
            QSqlField f6("Id_zon", QVariant::Int);

            QSqlQueryModel idunicomodel;
            idunicomodel.setQuery("SELECT ID_con FROM Consignatario ORDER by id_con DESC");
            int idunico=idunicomodel.record(0).value("Id_con").toInt()+1;
            idunicomodel.clear();
            QString selec="SELECT Id_zon FROM zona where (nombre='"+ui->zonacombobox->currentText()+"')";
            idunicomodel.setQuery(selec);
            int id_zon=idunicomodel.record(0).value("Id_zon").toInt();



            f1.setValue(QVariant(idunico));
            f2.setValue(QVariant(ui->b->text()));
            f3.setValue(QVariant(ui->c->text()));
            f4.setValue(QVariant(ui->d->text()));
            f5.setValue(QVariant(ui->e->text().toInt()));
            f6.setValue(QVariant(id_zon));


            record.append(f1);
            record.append(f2);
            record.append(f3);
            record.append(f4);
            record.append(f5);
            record.append(f6);
            model->insertRecord(-1, record);

            accept();
        }

    }

}

void econsignatarios::Editar()
{
    if (ui->b->text().isEmpty() ||
        ui->c->text().isEmpty() )
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
