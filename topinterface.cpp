#include "topinterface.h"

TopInterface::TopInterface(QWidget *parent) : QWidget(parent)
{
    Layout = new QHBoxLayout(this);
    CityLabelTop = new QLabel(this);
    SchoolLabelTop = new QLabel(this);
    ClassLabelTop = new QLabel(this);
    FirstNameLabelTop = new QLabel(this);
    LogOutButtonTop = new QPushButton("Выйти",this);
    Layout->addWidget(CityLabelTop);
    Layout->addWidget(SchoolLabelTop);
    Layout->addWidget(ClassLabelTop);
    Layout->addWidget(FirstNameLabelTop);
    Layout->addWidget(LogOutButtonTop);
}

void TopInterface::author(QString Ucity, QString Uscholl, QString Uclass, QString Uname)
{
    CityLabelTop->setText(Ucity);
    SchoolLabelTop->setText(Uscholl);
    ClassLabelTop->setText(Uclass);
    FirstNameLabelTop->setText(Uname);
}
