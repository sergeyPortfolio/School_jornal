#include "userreiting.h"

UserReiting::UserReiting(QWidget *parent) : QWidget(parent)
{
   CentralVLayout = new QVBoxLayout(this);
   tabl = new QTableWidget(this);
   CentralVLayout->addWidget(tabl);
   homeWorkBoard = new HomeWorkBoard();
   EditHomework = new QPushButton("Домашнє завдання", this);
   CentralVLayout->addWidget(EditHomework);
   connect(this->homeWorkBoard, SIGNAL(openBoard()), this, SLOT(openHomeWorkWindow()));

   homeWorkBoard->setRures(false);
}

void UserReiting::createTable(QMap<QString,QMultiMap<int,QPair<QString,int>>> map, QString flagLocal)
{
    //Flag = flagLocal;
    tabl->clear();
    tabl->setRowCount(0);
    tabl->setColumnCount(0);
    QString key1;
    QString pointCast;
    int row =0;

    int columGlob =0;
    int columLoc = 0;

     for (QMap<QString,QMultiMap<int,QPair<QString,int>>>::iterator it=map.begin(); it!=map.end(); ++it)
      {
          key1 = it.key();
          //QPair<QString,int> pair
          QMultiMap<int,QPair<QString,int>> Multipair(it.value());
          //QMultiMap<QString,int> Multipair(it.value());
          QTableWidgetItem* itemDiscipline = new QTableWidgetItem;
          itemDiscipline->setText(key1);

          row = tabl->rowCount()+1;
          tabl->setRowCount(row);
          tabl->setVerticalHeaderItem(row-1,itemDiscipline);
          tabl->setEditTriggers(QAbstractItemView::NoEditTriggers);

          int countLocal =columGlob;
          int countGlobal = 0;

          for (QMultiMap<int,QPair<QString,int>>::iterator itt=Multipair.begin(); itt!=Multipair.end(); ++itt)
          {
                 QTableWidgetItem* itemTypePoint = new QTableWidgetItem;
                 QPair<QString,int> pair = itt.value();
                 if(pair.first == "global"){itemTypePoint->setText("Тематична");}
                 //if(itt.key()=="global"){itemTypePoint->setText("Тематична");}
                 else{itemTypePoint->setText("Поточна");}
                 //QString KeyForIF = itt.key();
                 QString KeyForIF = pair.first;

                 if(KeyForIF == "global")
                 {
                      if(tabl->columnCount() ==0)
                      {
                         columGlob = tabl->columnCount()+1;
                         tabl->setColumnCount(columGlob);
                         tabl->setHorizontalHeaderItem(columGlob-1,itemTypePoint);
                         QTableWidgetItem* itemPoint = new QTableWidgetItem;
                         pointCast = QString::number(pair.second);
                         itemPoint->setData(Qt::UserRole,itt.key());
                         //pointCast = QString::number(itt.value());
                         itemPoint->setText(pointCast);
                         tabl->setItem(row-1, columGlob-1, itemPoint);
                         tabl->setColumnWidth(columGlob-1,80);
                         itemPoint->setTextAlignment(Qt::AlignCenter);
                         columLoc++;
                         countLocal++;
                         countGlobal++;
                      }
                      else if(tabl->columnCount() !=0 && columGlob > countGlobal)
                      {
                          QTableWidgetItem* itemPoint = new QTableWidgetItem;
                          //pointCast = QString::number(itt.value());
                          pointCast = QString::number(pair.second);
                          itemPoint->setData(Qt::UserRole,itt.key());
                          itemPoint->setText(pointCast);
                          tabl->setItem(row-1, countGlobal, itemPoint);
                          itemPoint->setTextAlignment(Qt::AlignCenter);
                          countGlobal++;

                      }
                      else if(tabl->columnCount() !=0 && columGlob <= countGlobal)
                      {
                          tabl->insertColumn(columGlob);
                          tabl->setHorizontalHeaderItem(columGlob,itemTypePoint);
                          QTableWidgetItem* itemPoint = new QTableWidgetItem;
                          //pointCast = QString::number(itt.value());
                          pointCast = QString::number(pair.second);
                          itemPoint->setData(Qt::UserRole,itt.key());
                          itemPoint->setText(pointCast);
                          tabl->setItem(row-1, columGlob, itemPoint);
                          tabl->setColumnWidth(columGlob,80);
                          itemPoint->setTextAlignment(Qt::AlignCenter);
                          columGlob++;
                          columLoc++;
                          countLocal++;
                          countGlobal++;
                      }
                 }
                 else
                 {
                     if(tabl->columnCount() ==0)
                     {
                        columLoc = tabl->columnCount()+1;
                        tabl->setColumnCount(columLoc);
                        tabl->setHorizontalHeaderItem(columLoc-1,itemTypePoint);
                        QTableWidgetItem* itemPoint = new QTableWidgetItem;
                        //pointCast = QString::number(itt.value());
                        pointCast = QString::number(pair.second);
                        itemPoint->setData(Qt::UserRole,itt.key());
                        itemPoint->setText(pointCast);
                        tabl->setItem(row-1, columLoc-1, itemPoint);
                        tabl->setColumnWidth(columLoc-1,80);
                        itemPoint->setTextAlignment(Qt::AlignCenter);
                        countLocal++;
                     }
                     else if(tabl->columnCount() !=0 && columLoc > countLocal)
                     {
                         QTableWidgetItem* itemPoint = new QTableWidgetItem;
                         //pointCast = QString::number(itt.value());
                         pointCast = QString::number(pair.second);
                         itemPoint->setData(Qt::UserRole,itt.key());
                         itemPoint->setText(pointCast);
                         tabl->setItem(row-1, countLocal, itemPoint);
                         itemPoint->setTextAlignment(Qt::AlignCenter);
                         countLocal++;

                      }
                     else if(tabl->columnCount() !=0 && columLoc <= countLocal)
                     {
                         columLoc = tabl->columnCount()+1;
                         tabl->setColumnCount(columLoc);
                         tabl->setHorizontalHeaderItem(columLoc-1,itemTypePoint);
                         QTableWidgetItem* itemPoint = new QTableWidgetItem;
                         pointCast = QString::number(pair.second);
                         itemPoint->setData(Qt::UserRole,itt.key());
                         //pointCast = QString::number(itt.value());
                         itemPoint->setText(pointCast);
                         tabl->setItem(row-1, columLoc-1, itemPoint);
                         tabl->setColumnWidth(columLoc-1,80);
                         itemPoint->setTextAlignment(Qt::AlignCenter);
                         countLocal++;
                     }
                 }
  }
      }
     int countTabl = tabl->rowCount();
     if(tabl->columnCount()==0)
     {
         tabl->setColumnCount(1);
     }
     for(int i = 0; i < countTabl; i++)
     {
         if(tabl->item(i,0) == 0)
         {
              QTableWidgetItem* item = new QTableWidgetItem;
              item->setText("");
              tabl->setItem(i,0,item);
         }
     }
     tabl->show();
}

void UserReiting::openHomeWorkWindow()
{
            homeWorkBoard->show();
}
