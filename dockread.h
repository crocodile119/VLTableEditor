#ifndef DOCKREAD_H
#define DOCKREAD_H

#include <QDockWidget>
#include <QTableWidgetItem>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#endif

#include <QPrinter>
#include <QPrintDialog>

namespace Ui {
class DockRead;
}

class DockRead : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockRead(QWidget *parent = nullptr);
    ~DockRead();
    void clearAsciiDataTable();
    QTableWidgetItem* getTableItem(int, int);
    void setTableItem(int, int, QTableWidgetItem*);
    void setTableRowCount(int row);
    void setTableColumnCount(int column);
    void setTableHorizontalHeaderLabels(const QStringList &);
    void setLabel(const QString &);
    QString getLabel();

private:
    Ui::DockRead *ui;
};

#endif // DOCKREAD_H
