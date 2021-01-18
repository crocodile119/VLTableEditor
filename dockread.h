#ifndef DOCKREAD_H
#define DOCKREAD_H

#include <QDockWidget>
#include <QTableWidgetItem>

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
    void setTableHorizontalHeaderItem(int, QTableWidgetItem*);
    void setLabel(QString);
    QString getLabel();

private:
    Ui::DockRead *ui;
};

#endif // DOCKREAD_H
