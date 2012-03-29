#ifndef TDPREVIEWDIALOG_H
#define TDPREVIEWDIALOG_H
    #include <QtGui/QDialog>
    #include <ui_tdpreviewdialog.h>
    #include <QtGui/QTableView> //checked
    #include <QtGui/QPrinter> //checked
    #include <QtGui/QTextLength> //checked
    #include <QtGui/QFileDialog> //checked
    #include <QtGui/QGraphicsView> //checked

class QGraphicsScene;
class QAbstractItemModel;

// Text preview widget
class TDPreviewDialog : public QDialog
{
        Q_OBJECT
        Q_ENUMS (Grids)
public:
        enum Grids {
                NoGrid=0x0,
                NormalGrid=0x1,
                AlternateColor=0x2,
                AlternateWithGrid=0x3
        };

        TDPreviewDialog(QTableView *p_tableView, QPrinter * p_printer, const QString &titulo,  QWidget *parent=0);
        virtual ~TDPreviewDialog();
        virtual void setHeaderText(const QString &text);
        virtual void setGridMode(Grids);

        virtual int exec();

private slots:
        virtual void on_setupToolButton_clicked();
        virtual void on_zoomInToolButton_clicked();
        virtual void on_zoomOutToolButton_clicked();
        virtual void on_pageSpinBox_valueChanged(int value);
        virtual void print();
        virtual void exportPdf();


private:
        Ui_TDPreviewDialog ui;
        virtual void setupPage();
        virtual void paintPage(int pagenum);
        virtual void setupSpinBox();
        QGraphicsView *view;
        QTableView *tableView;
        QPrinter *printer;
        TDPreviewDialog::Grids gridMode;
        int lines;
        int pages;
        int leftMargin;
        int rightMargin;
        int topMargin;
        int bottomMargin;
        int spacing;
        int headerSize;
        int footerSize;
        int sceneZoomFactor;
        double columnZoomFactor;
        double rowHeight;
        double columnMultiplier;
        QString headerText;
        QString footerText;
        QVector<QTextLength> colSizes;
        QAbstractItemModel *model;
        QGraphicsScene pageScene;
        QFont titleFont;
        QFont headerFont;
        QFont font;
        QFontMetrics *titleFmt;
        QFontMetrics *headerFmt;
        QFontMetrics *fmt;
        QString headerStdText;
};

#endif
