#include "admininterface.h"
#include <QList>
#include<QDebug>
AdminInterface::AdminInterface(QWidget *parent) : QWidget(parent)
{

    CentralLayout = new QHBoxLayout(this);
    RightLayout =new QVBoxLayout(this);

    tabl = new QTableWidget(this);
    CentralLayout->addWidget(tabl);
    CentralLayout->addLayout(RightLayout);

    EditPoint = new QPushButton("Додати оцінку",this);
    DeleteStudentButton = new QPushButton("Видалити учня",this);
    InsertStudentButton = new QPushButton("Додати учня",this);
    message = new MyMessageBox();
    panelForEdit = new AdminPanelForEdit();

    RightLayout->addWidget(EditPoint);
    RightLayout->addWidget(DeleteStudentButton);
    RightLayout->addWidget(InsertStudentButton);
    connect(this->InsertStudentButton,SIGNAL(clicked()),this,SLOT(openEditWindowForInsert()));
    connect(this->DeleteStudentButton,SIGNAL(clicked()),this,SLOT(deleteUser()));
    connect(this->EditPoint,SIGNAL(clicked()),this,SLOT(editPointUser()));
    connect(this->panelForEdit->cancel,SIGNAL(clicked()),this,SLOT(closeAdminPanelForEdit()));

    //qDebug()<<"f";
}

void AdminInterface::createUserList(QMap<QString, unsigned int> UserListMap)
{
    //qDebug()<<UserListMap;
    tabl->clear();
    int row=0;
    tabl->setRowCount(row);
    int numberStudentCounter = 1;
    tabl->setColumnCount(1);
    QTableWidgetItem* HederName = new QTableWidgetItem;
    HederName->setText("Прізвище та ініціали");
    tabl->setHorizontalHeaderItem(0,HederName);
    tabl->setColumnWidth(0,140);
    for (QMap<QString,unsigned int>::iterator it=UserListMap.begin(); it!=UserListMap.end(); ++it)
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
       QString nameStudent = index[0]->text();
       emit deleteUserSignal(nameStudent);

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
    if(index.empty())
    {
        CheckUncheck->setText("Натисніть на ім'я школяра");
        CheckUncheck->show();
    }
    else
    {
       QString nameStudent = index[0]->text();
       emit createTablePoint(nameStudent);
       panelForEdit->show();
    }



}

void AdminInterface::closeAdminPanelForEdit()
{
    panelForEdit->close();
}


