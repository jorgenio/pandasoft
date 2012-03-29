#ifndef MENSAJEBOX_H
#define MENSAJEBOX_H

#include <QDialog>

namespace Ui {
    class mensajebox;
}

class mensajebox : public QDialog
{
    Q_OBJECT

public:
    explicit mensajebox(const QString &titulo,const QString &mensaje, QWidget *parent = 0);
    ~mensajebox();

private:
    Ui::mensajebox *ui;
};

#endif // MENSAJEBOX_H
