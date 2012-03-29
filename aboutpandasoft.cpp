#include "aboutpandasoft.h"
#include "ui_aboutpandasoft.h"

aboutPandasoft::aboutPandasoft(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutPandasoft)
{
    ui->setupUi(this);
}

aboutPandasoft::~aboutPandasoft()
{
    delete ui;
}
