#ifndef USERREITING_H
#define USERREITING_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QMultiMap>

class UserReiting : public QWidget
{
    Q_OBJECT
public:
    explicit UserReiting(QWidget *parent = nullptr);

signals:

public slots:
      void createTable(QMap<QString,QMultiMap<QString,int>> map);
private:
    QTableWidget *tabl;
    QVBoxLayout *CentralVLayout;
    QTableWidgetItem* itemGlobal;
    QTableWidgetItem* itemLocal;
    QTableWidgetItem* itemTypeLocal;
    QTableWidgetItem* itemTypeGlobal;
};

#endif // USERREITING_H
