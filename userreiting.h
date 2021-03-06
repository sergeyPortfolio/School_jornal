#ifndef USERREITING_H
#define USERREITING_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QMultiMap>
#include <QPushButton>
#include "homeworkboard.h"

class UserReiting : public QWidget
{
    Q_OBJECT
public:
    explicit UserReiting(QWidget *parent = nullptr);
    HomeWorkBoard *homeWorkBoard;
    QPushButton *EditHomework;

signals:

public slots:
      void createTable(QMap<QString,QMultiMap<int,QPair<QString,int>>> map, QString);
      void openHomeWorkWindow();
private:
    QTableWidget *tabl;
    QVBoxLayout *CentralVLayout;
    QTableWidgetItem* itemGlobal;
    QTableWidgetItem* itemLocal;
    QTableWidgetItem* itemTypeLocal;
    QTableWidgetItem* itemTypeGlobal;
};

#endif // USERREITING_H
