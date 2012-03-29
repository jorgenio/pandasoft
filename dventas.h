#ifndef DVENTAS_H
#define DVENTAS_H

#include "qdialog.h"

namespace Ui {
    class dventas;
}

class dventas : public QDialog
{
    Q_OBJECT

public:
    explicit dventas(QWidget *parent = 0);
    ~dventas();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dventas *ui;
};

#endif // DVENTAS_H
