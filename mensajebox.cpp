#include "mensajebox.h"
#include "ui_mensajebox.h"

mensajebox::mensajebox(const QString &titulo,const QString &mensaje, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mensajebox)
{
    ui->setupUi(this);
    this->setWindowTitle(titulo);
    ui->imagelabel->setPixmap(QPixmap(":/images/system-help.png"));
    ui->pregunta->setText(mensaje);
}

mensajebox::~mensajebox()
{
    delete ui;
}
