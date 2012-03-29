#include "dventas.h"
#include "ui_dventas.h"

dventas::dventas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dventas)
{
    ui->setupUi(this);
}

dventas::~dventas()
{
    delete ui;
}

void dventas::changeEvent(QEvent *e)
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
