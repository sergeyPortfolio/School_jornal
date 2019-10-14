#ifndef MODERREITING_H
#define MODERREITING_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QMultiMap>
#include "homeworkboard.h"

class ModerReiting : public QWidget
{
    Q_OBJECT
public:
    explicit ModerReiting(QWidget *parent = nullptr);
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


#endif // MODERREITING_H
