#include "adminpanelforedit.h"

AdminPanelForEdit::AdminPanelForEdit(QWidget *parent) : QWidget(parent)
{
    tabl = new QTableWidget(this);
    globalLocal = new QComboBox(this);
    label = new QLabel("Введіть оцінку",this);
    insertPoint = new QPushButton("Додати оцінку",this);
    update = new QPushButton("Редагувати",this);
    windowForPoint = new QLineEdit(this);
    CentralLayout = new QVBoxLayout(this);
    BottomLayout = new QHBoxLayout(this);
    deletePoint = new QPushButton("Видалити оцінку",this);
    deleteALlPoint = new QPushButton("Видалити усі оцінки",this);

    CentralLayout->addWidget(tabl);
    CentralLayout->addLayout(BottomLayout);
    BottomLayout->addWidget(globalLocal);
    BottomLayout->addWidget(label);
    BottomLayout->addWidget(windowForPoint);
    BottomLayout->addWidget(insertPoint);
    BottomLayout->addWidget(deletePoint);
    BottomLayout->addWidget(deleteALlPoint);
    BottomLayout->addWidget(update);

    globalLocal->insertItem(0,"Поточна");
    globalLocal->insertItem(1,"Тематична");
    connect(this->deletePoint,SIGNAL(clicked()),this,SLOT(deletePointSlot()));
    connect(this->insertPoint,SIGNAL(clicked()),this,SLOT(editPointSlot()));
    connect(this->deleteALlPoint,SIGNAL(clicked()),this,SLOT(deleteAllPointSlot()));
    connect(this->update,SIGNAL(clicked()),this,SLOT(updatePoint()));
}
void AdminPanelForEdit::createTable(QMap<QString,QMultiMap<int,QPair<QString,int>>> map,QString flagLocal)
{
    Flag = flagLocal;
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

void AdminPanelForEdit::deletePointSlot()
{
    message = new QMessageBox();
    auto index = tabl->selectedItems();
    if(Flag == "onUser")
    {
        if(index.empty())
        {
            message->setText("Натисніть на оцінку");
            message->show();
        }
        else
        {
            QString Point = index[0]->text();
            QString Type = tabl->horizontalHeaderItem(index[0]->column())->text();
            QString NameDiscipline = tabl->verticalHeaderItem(index[0]->row())->text();
            QString idPoint = index[0]->data(Qt::UserRole).toString();

            emit deletePointSignal(idName,NameDiscipline,Type,Point,idPoint);
        }
    }
    else if(Flag == "onDiscp")
    {
        if(index.empty())
        {
            message->setText("Натисніть на оцінку");
            message->show();
        }
        else
        {
            QString Point = index[0]->text();
            QString Type = tabl->horizontalHeaderItem(index[0]->column())->text();
            QString NameUser = tabl->verticalHeaderItem(index[0]->row())->text();
            QString idPoint = index[0]->data(Qt::UserRole).toString();

            emit deletePointOnDiscpSignal(idName,NameUser,Type,Point,idPoint);
        }
    }
}

void AdminPanelForEdit::updatePoint()
{
    message = new QMessageBox();
    auto index = tabl->selectedItems();

        if(index.empty())
        {
            message->setText("Натисніть на оцінку");
            message->show();
        }
        else
        {
            if( windowForPoint->text().isEmpty())
            {
                message->setText("Введіть оцінку");
                message->show();
            }
            else
            {
                QString idPoint = index[0]->data(Qt::UserRole).toString();
                QString point = windowForPoint->text();
                windowForPoint->setText(NULL);

                if(Flag == "onUser")
                {

                    emit updatePointSignal(idPoint,idName,point);
                }
                else if(Flag == "onDiscp")
                {

                    emit updatePointSignalonDiscp(idPoint,idName,point);
                }
            }
        }
}

void AdminPanelForEdit::idUserSlot(QString nameUser)
{
    idName = nameUser;
}

void AdminPanelForEdit::idDiscpSlot(QString nameDiscp)
{
    idName = nameDiscp;
}

void AdminPanelForEdit::editPointSlot()
{
    message = new QMessageBox();

        auto index = tabl->selectedItems();
        if(index.empty() && Flag == "onUser")
        {
            message->setText("Натисніть на назву дисципліни");
            message->show();
        }
        else if(index.empty() && Flag == "onDiscp")
        {
            message->setText("Натисніть на прізвище учня");
            message->show();
        }
        else
        {
            QString Point;
            QString Type;
            QStringList PointArr;

            if( windowForPoint->text().isEmpty())
            {
                message->setText("Введіть оцінку, або декілька оцінок через пробіл");
                message->show();
            }
            else
            {
                 Point  = windowForPoint->text();
                 PointArr = Point.split(" ");
            }

            if(globalLocal->currentText() == "Поточна")
            {
                Type = "local";
            }
            else
            {
                Type = "global";
            }
            if(Flag == "onUser")
            {
                QString NameDiscipline = tabl->verticalHeaderItem(index[0]->row())->text();
                emit editPointSignal(idName,NameDiscipline,Type,PointArr);
                windowForPoint->setText(NULL);
            }
            else if( Flag == "onDiscp")
            {
                QString NameStudent = tabl->verticalHeaderItem(index[0]->row())->text();
                emit editPointSignalOnDiscp(idName,NameStudent,Type,PointArr);
                windowForPoint->setText(NULL);
            }
        }


}

void AdminPanelForEdit::deleteAllPointSlot()
{
    message = new QMessageBox();
    auto index = tabl->selectedItems();
    if(Flag == "onUser")
    {
        if(index.empty())
        {
            message->setText("Натисніть на назву дисципліни");
            message->show();
        }
        else
        {
            QString NameDiscipline = tabl->verticalHeaderItem(index[0]->row())->text();
            emit deleteAllPointSignal(idName,NameDiscipline);
        }
    }
    else if(Flag == "onDiscp")
    {
        if(index.empty())
        {
            message->setText("Натисніть на прізвище учня");
            message->show();
        }
        else
        {
            QString NameUser = tabl->verticalHeaderItem(index[0]->row())->text();
            emit deleteAllPointSignalOnDiscp(idName,NameUser);
        }
    }
}
