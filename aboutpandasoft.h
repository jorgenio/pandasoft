#ifndef ABOUTPANDASOFT_H
#define ABOUTPANDASOFT_H

#include <QDialog>

namespace Ui {
    class aboutPandasoft;
}

class aboutPandasoft : public QDialog
{
    Q_OBJECT

public:
    explicit aboutPandasoft(QWidget *parent = 0);
    ~aboutPandasoft();

private:
    Ui::aboutPandasoft *ui;
};

#endif // ABOUTPANDASOFT_H
