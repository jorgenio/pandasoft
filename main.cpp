#include "QtGui/qapplication.h"
#include "database.h"
#include "pandasoft.h"
#include "qlocale.h"
#include "qsplashscreen.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/pandasoft.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;


    splash->showMessage(QObject::tr("Cargando base de datos..."),
    topRight, Qt::red);
    if (!createConnection())
        return 1;
    splash->showMessage(QObject::tr("Cargando Login..."),
    topRight, Qt::red);
    pandasoft w;
    w.show();

    splash->finish(&w);

    delete splash;
    return app.exec();
}
