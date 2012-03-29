#include "eproducto.h"
#include "ui_eproducto.h"
#include "QtSql"
#include "mensajebox.h"
#include "ui_mensajebox.h"
#include <QFileDialog>
eproducto::eproducto(int id, QSqlRelationalTableModel *modelo, const QString &titulo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eproducto)
{
    ui->setupUi(this);

    this->setWindowTitle(titulo);
    model =modelo;
    ui->informacion->hide();
    ui->c->setValidator(new QIntValidator(0, 999, this));
    ui->d->setValidator(new QIntValidator(0, 999, this));
    connect( ui->aceptar, SIGNAL(clicked()), this, SLOT(Aceptar()) );
    connect( ui->editar, SIGNAL(clicked()), this, SLOT(Editar()) );
    connect( ui->eabrir, SIGNAL(clicked()), this, SLOT(openFile()) );

    if(id!=-1){
        ui->aceptar->hide();;
        mapper = new QDataWidgetMapper(this);
        mapper->setModel(modelo);
        mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
        mapper->setItemDelegate(new QSqlRelationalDelegate(mapper));
        mapper->addMapping(ui->a, 0, "text");
        mapper->addMapping(ui->b, 1, "text");
        mapper->addMapping(ui->c, 2, "text");
        mapper->addMapping(ui->pconsig, 3, "text");
        mapper->addMapping(ui->d, 5, "text");
        mapper->addMapping(ui->e, 6, "text");
        mapper->addMapping(ui->f, 7, "text");
        //mapper->addMapping(ui->i, 8, "text");

        mapper->setCurrentIndex(id);

    }else{
        sucursalmodel = new QSqlRelationalTableModel();
        sucursalmodel->setTable("sucursal");
        sucursalmodel->select();



        ui->editar->hide();
    }
}

eproducto::~eproducto()
{
    delete ui;
}

void eproducto::changeEvent(QEvent *e)
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

void eproducto::Aceptar()
{
    if (ui->b->text().isEmpty() ||
        ui->c->text().isEmpty() || ui->d->text().isEmpty() ||
        ui->f->text().isEmpty() )
    {
        ui->informacion->show();
    } else {

        mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
        int accepted = add->exec();
        if (accepted == 1) {

            QSqlRecord record;

            QSqlField f1("ID_pro", QVariant::Int);
            QSqlField f2("Nombre", QVariant::String);
            QSqlField f3("Punitario", QVariant::Double);
            QSqlField f4("Pconsig", QVariant::Double);
            QSqlField f5("cantidad", QVariant::Int);
            QSqlField f6("Lim_stock", QVariant::Int);
            QSqlField f7("Foto", QVariant::String);
            QSqlField f8("Descripcion", QVariant::String);

            QSqlQueryModel idunicomodel;
            idunicomodel.setQuery("SELECT Id_pro FROM Producto ORDER by id_pro DESC");

            int idunico=idunicomodel.record(0).value("Id_pro").toInt()+1;
            idunicomodel.clear();

            f1.setValue(QVariant(idunico));
            f2.setValue(QVariant(ui->b->text()));
            f3.setValue(QVariant(ui->c->text()).toDouble());
            f4.setValue(QVariant(ui->pconsig->text()).toDouble());
            f5.setValue(QVariant(0));
            f6.setValue(QVariant(ui->d->text().toInt()));
            f7.setValue(QVariant(""));
            f8.setValue(QVariant(ui->f->text()));

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


void eproducto::Editar()
{
    if (ui->a->text().isEmpty() || ui->b->text().isEmpty() ||
        ui->c->text().isEmpty() || ui->d->text().isEmpty() ||
        ui->e->text().isEmpty() )
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
void  eproducto::openFile()
{
  QString filename = QFileDialog::getOpenFileName(this, tr("Abrir Imagen"), QDir::currentPath(), tr("Tipo de Archivos (*.png *.jpg);;Todos los tipos (*.*)"), 0, QFileDialog::DontUseNativeDialog );
  ui->imagenlabel->setWordWrap(true);
  ui->imagenlabel->setAlignment(Qt::AlignCenter);
  ui->imagenlabel->setPixmap(QPixmap(filename));

  ui->e->setText(filename);

}
