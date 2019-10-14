#include "admininterface.h"

AdminInterface::AdminInterface(QWidget *parent) : QWidget(parent)
{

    CentralLayout = new QHBoxLayout(this);
    RightLayout =new QVBoxLayout(this);

    tabl = new QTableWidget(this);
    tablDiscipline = new QTableWidget(this);
    CentralLayout->addWidget(tabl);
    CentralLayout->addWidget(tablDiscipline);
    CentralLayout->addLayout(RightLayout);

    EditPoint = new QPushButton("Додати оцінку",this);
    DeleteStudentButton = new QPushButton("Видалити учня",this);
    InsertStudentButton = new QPushButton("Додати учня",this);
    InsertDiscipline = new QPushButton("Додати дисципліни",this);
    DeleteDiscipline = new QPushButton("Видалити дисципліну",this);
    UseUser = new QPushButton("Обрати/зняти старосту",this);
    EditHomework = new QPushButton("Додати домашнє завдання", this);
    message = new MyMessageBox();
    panelForEdit = new AdminPanelForEdit();
    panelForEditDisc = new InsertDisciplineWidget();

    homeWorkBoard = new HomeWorkBoard();
    homeWorkBoard->setRures(true);

    RightLayout->addWidget(EditPoint);
    RightLayout->addWidget(InsertDiscipline);
    RightLayout->addWidget(DeleteDiscipline);
    RightLayout->addWidget(DeleteStudentButton);
    RightLayout->addWidget(InsertStudentButton);
    RightLayout->addWidget(UseUser);
    RightLayout->addWidget(EditHomework);
    connect(this->InsertStudentButton,SIGNAL(clicked()),this,SLOT(openEditWindowForInsert()));
    connect(this->DeleteStudentButton,SIGNAL(clicked()),this,SLOT(deleteUser()));
    connect(this->EditPoint,SIGNAL(clicked()),this,SLOT(editPointUser()));
    connect(this->InsertDiscipline,SIGNAL(clicked()),this,SLOT(insertDiscipline()));
    connect(this,SIGNAL(idUser(QString)),this->panelForEdit,SLOT(idUserSlot(QString)));
    connect(this,SIGNAL(idDiscp(QString)),this->panelForEdit,SLOT(idDiscpSlot(QString)));
    connect(this->DeleteDiscipline,SIGNAL(clicked()),this,SLOT(deleteDiscplineSlot()));
    connect(this->tabl,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(resetItemTabl(QTableWidgetItem*)));
    connect(this->tablDiscipline,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(resetItemTabl(QTableWidgetItem*)));
    connect(this->UseUser,SIGNAL(clicked()),this,SLOT(updateUserLaw()));
    connect(this->homeWorkBoard, SIGNAL(openBoard()), this, SLOT(openHomeWorkWindow()));

}

void AdminInterface::updateUserLaw()
{
    CheckUncheck = new QMessageBox();
    auto index = tabl->selectedItems();
    if(index.empty())
    {
        CheckUncheck->setText("Натисніть на ім'я школяра");
        CheckUncheck->show();
    }
    else
    {
         QString nameStudent = index[0]->text();
         emit updateUserLawSignal(nameStudent);
    }

}

void AdminInterface::createUserList(QMap<QString,QPair<unsigned int,QString>> UserListMap)
{
    List = UserListMap;
    tabl->clear();
    int row=0;
    tabl->setRowCount(row);
    int numberStudentCounter = 1;
    tabl->setColumnCount(1);
    QTableWidgetItem* HederName = new QTableWidgetItem;
    HederName->setText("Прізвище та ініціали");
    tabl->setHorizontalHeaderItem(0,HederName);
    tabl->setColumnWidth(0,200);
    for (QMap<QString,QPair<unsigned int,QString>>::iterator it=UserListMap.begin(); it!=UserListMap.end(); ++it)
     {
         QTableWidgetItem* numberStudent = new QTableWidgetItem;
         numberStudent->setText(QString::number(numberStudentCounter));
         row = tabl->rowCount()+1;
         tabl->setRowCount(row);
         tabl->setVerticalHeaderItem(row-1,numberStudent);
         tabl->setEditTriggers(QAbstractItemView::NoEditTriggers);
         numberStudentCounter++;

         QTableWidgetItem* nameStudent = new QTableWidgetItem();
         nameStudent->setText(it.key());
         tabl->setItem(row-1,0,nameStudent);
         if(it.value().second == "moder")
         {
             QColor color;
             color.setRgb(140,255,105);
             tabl->item(row-1,0)->setBackground(color);
         }
    }
    tabl->show();
}

void AdminInterface::openEditWindowForInsert()
{
    connect(this->message->Cancel,SIGNAL(clicked()),this,SLOT(closeEditWindowForInsert()));
    message->show();
}

void AdminInterface::closeEditWindowForInsert()
{
    message->close();
}

void AdminInterface::deleteUser()
{

    CheckUncheck = new QMessageBox();
    auto index = tabl->selectedItems();
    if(index.empty())
    {
        CheckUncheck->setText("Натисніть на ім'я школяра");
        CheckUncheck->show();
    }
    else
    {
        QAbstractButton *yes = CheckUncheck->addButton("Так",QMessageBox::YesRole);
        QAbstractButton *no = CheckUncheck->addButton("Ні",QMessageBox::NoRole);
        CheckUncheck->setText("\t\t\t\tВи впевнені ? \nПри видаленні учня, усі його данні, включаючи оцінки буде знищенно");
        CheckUncheck->exec();
        if(CheckUncheck->clickedButton() == yes)
        {
            QString nameStudent = index[0]->text();
            emit deleteUserSignal(nameStudent);
            CheckUncheck->close();
        }
        else
        {
            CheckUncheck->close();
        }
    }
}

void AdminInterface::deleteUserDone(bool b)
{
    DeleteOk = new QMessageBox();
    if (b == true)
    {
        DeleteOk->setText("Видалення завершено");
        emit repeatUserList();
        DeleteOk->show();
    }
    else
    {
        DeleteOk->setText("Помилка, спробуйте ще");
        DeleteOk->show();
    }
}

void AdminInterface::editPointUser()
{
    CheckUncheck = new QMessageBox();
    auto index = tabl->selectedItems();
    auto indexDisc = tablDiscipline->selectedItems();

       if(!index.empty())
       {
            QString nameStudent = index[0]->text();
            emit createTablePoint(nameStudent);
            emit idUser(nameStudent);
            panelForEdit->show();
       }
       else if(!indexDisc.empty())
       {
           QString nameDiscp = indexDisc[0]->text();
           emit createTablePointOnDiscp(nameDiscp);
           emit idDiscp(nameDiscp);
           panelForEdit->show();
       }
       else
       {
           CheckUncheck->setText("Натисніть на ім'я школяра, або на назву предмету");
           CheckUncheck->show();
       }

}

void AdminInterface::closeAdminPanelForEdit()
{
    panelForEdit->close();
}

void AdminInterface::insertDiscipline()
{
    emit createTableDiscipline();
    panelForEditDisc->show();
}

void AdminInterface::createTableDisciplineSlot(QMap<QString,unsigned int> list)
{
    tablDiscipline->clear();
    tablDiscipline->setRowCount(0);
    tablDiscipline->setColumnCount(1);
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText("Назва Дисциплін");
    tablDiscipline->setColumnWidth(0,200);
    tablDiscipline->setHorizontalHeaderItem(0,item);
    int row =0;
    int number = 1;
    for (QMap<QString,unsigned int>::iterator it=list.begin(); it!=list.end(); ++it)
    {
        QTableWidgetItem *itemNumber = new QTableWidgetItem;
        itemNumber->setText(QString::number(number));
        QTableWidgetItem *itemDiscipline = new QTableWidgetItem;
        itemDiscipline->setText(it.key());

        row = tablDiscipline->rowCount()+1;
        tablDiscipline->setRowCount(row);
        tablDiscipline->setVerticalHeaderItem(row-1,itemNumber);
        tablDiscipline->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablDiscipline->setItem(row-1,0,itemDiscipline);
        number++;
    }
    tablDiscipline->show();
}

void AdminInterface::deleteDiscplineSlot()
{
    messageDeliteDescipline = new QMessageBox();
    auto index = tablDiscipline->selectedItems();
    if(index.empty())
    {
        messageDeliteDescipline->setText("Натисніть на назву дисципліни");
        messageDeliteDescipline->show();
    }
    else
    {
        QAbstractButton *yes = messageDeliteDescipline->addButton("Так",QMessageBox::YesRole);
        QAbstractButton *no = messageDeliteDescipline->addButton("Ні",QMessageBox::NoRole);
        messageDeliteDescipline->setText("\t\t\t\tВи впевнені ? \nПри видаленні предмету, усі оцінки, які з ним зв'язані, буде знищенно");
        messageDeliteDescipline->exec();
        if(messageDeliteDescipline->clickedButton() == yes)
        {
            QString nameDisc = index[0]->text();
            emit deleteDisciplineSignal(nameDisc);
            messageDeliteDescipline->close();
        }
        else
        {
            messageDeliteDescipline->close();
        }
    }

}

void AdminInterface::resetItemTabl(QTableWidgetItem *Item)
{
    if(Item->tableWidget()->horizontalHeaderItem(0)->text() == "Прізвище та ініціали")
    {
        tablDiscipline->clearSelection();
        tablDiscipline->selectedItems().clear();
    }
    else
    {
        tabl->clearSelection();
        tabl->selectedItems().clear();
    }

}

void AdminInterface::openHomeWorkWindow()
{
    homeWorkBoard->show();
}

void AdminInterface::closeHomeWorkWindow()
{

}


