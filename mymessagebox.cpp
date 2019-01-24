#include "mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget *parent) : QWidget(parent)
{
   CentralLayout = new QVBoxLayout(this);
   TopLayout = new QHBoxLayout(this);
   BottomLayout = new QHBoxLayout(this);
   CentralLayout->addLayout(TopLayout);
   CentralLayout->addLayout(BottomLayout);

   Ok = new QPushButton("Додати",this);
   Cancel = new QPushButton("Відмінити",this);
   name = new QLineEdit(this);
   pass = new QLineEdit(this);
   nameLabel = new QLabel(this);
   passLabel = new QLabel(this);
   nameLabel->setText("Прізвище та ініціали");
   passLabel->setText("Пароль");

   TopLayout->addWidget(nameLabel);
   TopLayout->addWidget(name);
   TopLayout->addWidget(passLabel);
   TopLayout->addWidget(pass);
   BottomLayout->addWidget(Ok);
   BottomLayout->addWidget(Cancel);
   connect(this->Ok,SIGNAL(clicked()),this,SLOT(NameAndPassSlot()));
}

void MyMessageBox::NameAndPassSlot()
{
    if(name->text() == "" || pass->text() == "")
    {
        messegeNotFill = new QMessageBox();
        messegeNotFill->setText("Заповніть усі поля");
        messegeNotFill->show();
    }
    else
    {
        emit NameAndPassSignal(name->text(),pass->text());
    }
}

void MyMessageBox::DoneOrNot(bool b)
{
    if(b == true)
    {
        messegeDone = new QMessageBox();
        messegeDone->setText("Реєстрація пройшла успішно");
        messegeDone->show();
        emit ResetTableUser();
        name->setText("");
        pass->setText("");
    }
    else
    {
        messegeNotDone = new QMessageBox();
        messegeNotDone->setText("Не вдалось зареєструвати");
        messegeNotDone->show();
    }
}
