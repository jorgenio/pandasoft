#include "sproducto.h"
#include "ui_sproducto.h"
#include <QtSql>
#include "qdatawidgetmapper.h"
#include "mensajebox.h"
#include "ui_mensajebox.h"

sproducto::sproducto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sproducto)
{
    ui->setupUi(this);

    productomodel = new QSqlRelationalTableModel();
    productomodel->setTable("Producto");
    productomodel->select();

    ui->productocomboBox->setModel(productomodel);
    ui->productocomboBox->setModelColumn(1);
    connect( ui->aceptar, SIGNAL(clicked()), this, SLOT(guardar()) );
    connect(ui->productocomboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(cargar()));

}

sproducto::~sproducto()
{
    delete ui;
}

void sproducto::changeEvent(QEvent *e)
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
void sproducto::guardar()
{
    int idcant = ui->a->text().toInt(0, 10)-ui->spinBox->text().toInt(0, 10);
    ui->spinBox->setValue(idcant);
    ui->a->setText(ui->spinBox->text());
    mensajebox *add = new mensajebox("Guardar", "Esta seguro de guardar los datos?", this);
            int accepted = add->exec();
    if (accepted == 1) {
        mapper->submit();
        accept();
    }

}
void sproducto::cargar()
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
    int idcantmax = ui->a->text().toInt(0, 10);
    ui->spinBox->setRange(1, idcantmax);
    ui->horizontalSlider->setRange(1, idcantmax);
}
