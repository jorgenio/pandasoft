#include "reproductos.h"
#include "ui_reproductos.h"
#include <QtSql>
#include "qdatawidgetmapper.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"


QDataWidgetMapper mapper;

reproductos::reproductos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reproductos)
{
    ui->setupUi(this);

    productomodel = new QSqlRelationalTableModel();
    productomodel->setTable("Producto");
    productomodel->select();

    ui->productocomboBox->setModel(productomodel);
    ui->productocomboBox->setModelColumn(1);

    connect( ui->aceptar, SIGNAL(clicked()), this, SLOT(guardar()) );
    connect(ui->productocomboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(cargar()));
cargar();
}

reproductos::~reproductos()
{
    delete ui;
}

void reproductos::changeEvent(QEvent *e)
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
void reproductos::guardar()
{
    int idcant = ui->spinBox->text().toInt()+ui->a->text().toInt();
    ui->spinBox->setValue(idcant);
    ui->a->setText(ui->spinBox->text());
    mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
    int accepted = add->exec();
    if (accepted == 1) {
        mapper->submit();
        accept();
    }

}
void reproductos::cargar()
{
    model = new QSqlRelationalTableModel(this);
    model->setTable("producto");
    model->select();
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new QSqlRelationalDelegate(mapper));
    mapper->addMapping(ui->a, 4, "text");
    mapper->setCurrentIndex(ui->productocomboBox->currentIndex());

}
