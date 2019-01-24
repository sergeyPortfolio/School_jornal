#include "userreiting.h"
#include <QStringList>
UserReiting::UserReiting(QWidget *parent) : QWidget(parent)
{
   CentralVLayout = new QVBoxLayout(this);
   tabl = new QTableWidget(this);
   CentralVLayout->addWidget(tabl);
}

void UserReiting::createTable(QMap<QString,QMultiMap<QString,int>> map)
{

   QString key1;
   QString pointCast;
   int row =0;

   int columGlob =0;
   int columLoc = 0;

    for (QMap<QString,QMultiMap<QString,int>>::iterator it=map.begin(); it!=map.end(); ++it)
     {
         key1 = it.key();
         QMultiMap<QString,int> Multipair(it.value());
         QTableWidgetItem* itemDiscipline = new QTableWidgetItem;
         itemDiscipline->setText(key1);
         row = tabl->rowCount()+1;
         tabl->setRowCount(row);
         tabl->setVerticalHeaderItem(row-1,itemDiscipline);
         tabl->setEditTriggers(QAbstractItemView::NoEditTriggers);          //редактирование

         int countLocal =columGlob;
         int countGlobal = 0;

         for (QMultiMap<QString,int>::iterator itt=Multipair.begin(); itt!=Multipair.end(); ++itt)
         {
                QTableWidgetItem* itemTypePoint = new QTableWidgetItem;
                if(itt.key()=="global"){itemTypePoint->setText("Тематична");}
                else{itemTypePoint->setText("Поточна");}
                QString KeyForIF = itt.key();

                if(KeyForIF == "global")
                {
                     if(tabl->columnCount() ==0)
                     {
                        columGlob = tabl->columnCount()+1;
                        tabl->setColumnCount(columGlob);
                        tabl->setHorizontalHeaderItem(columGlob-1,itemTypePoint);
                        QTableWidgetItem* itemPoint = new QTableWidgetItem;
                        pointCast = QString::number(itt.value());
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
                         pointCast = QString::number(itt.value());
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
                         pointCast = QString::number(itt.value());
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
                       pointCast = QString::number(itt.value());
                       itemPoint->setText(pointCast);
                       tabl->setItem(row-1, columLoc-1, itemPoint);
                       tabl->setColumnWidth(columLoc-1,80);
                       itemPoint->setTextAlignment(Qt::AlignCenter);
                    }
                    else if(tabl->columnCount() !=0 && columLoc > countLocal)
                    {
                        QTableWidgetItem* itemPoint = new QTableWidgetItem;
                        pointCast = QString::number(itt.value());
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
                        pointCast = QString::number(itt.value());
                        itemPoint->setText(pointCast);
                        tabl->setItem(row-1, columLoc-1, itemPoint);
                        tabl->setColumnWidth(columLoc-1,80);
                        itemPoint->setTextAlignment(Qt::AlignCenter);
                        countLocal++;
                    }
                }
 }
     }
   tabl->show();
}
