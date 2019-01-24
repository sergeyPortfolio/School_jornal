#include "authorform.h"
#include <QDebug>
#include <QFile>

authorForm::authorForm(QWidget *parent) : QWidget(parent)
{
    QFile file("MySettings.txt");
        if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
               ForReadcity = file.readLine();
               ForReadschool = file.readLine();
               ForReadclass = file.readLine();
               ForReadname = file.readLine();
               ForReadpass = file.readLine();
               file.close();
               ForReadcity.remove("\n");
               ForReadschool.remove("\n");
               ForReadclass.remove("\n");
               ForReadname.remove("\n");
               ForReadpass.remove("\n");
        }
        else
        {
            qDebug()<< "don't open file";
        }

    m_backGroundColor = Qt::white;

    CentralVLayout = new QVBoxLayout(this);
    LabelVLayout = new QVBoxLayout(this);
    LineEditVLayout = new QVBoxLayout(this);
    DataAutorHLayout = new QHBoxLayout(this);
    EnterHLayout = new QHBoxLayout(this);

    EnterHLayout->setAlignment(Qt::AlignCenter);

    CityLabel = new QLabel("Город",this);
    SchoolLabel = new QLabel("Школа",this);
    ClassLabel = new QLabel("Класс",this);
    FirstNameLabel = new QLabel("Фамилия и инициалы",this);
    PassLabel = new QLabel("Пароль",this);

    CityLabel->setFixedWidth(150);
    SchoolLabel->setFixedWidth(150);
    ClassLabel->setFixedWidth(150);
    FirstNameLabel->setFixedWidth(150);
    PassLabel->setFixedWidth(150);



    CityLineEdit = new QLineEdit(ForReadcity,this);
    SchoolLineEdit = new QLineEdit(ForReadschool,this);
    ClassLineEdit = new QLineEdit(ForReadclass,this);
    FirstNameLineEdit = new QLineEdit(ForReadname,this);
    PassLineEdit = new QLineEdit(ForReadpass,this);
    CityLineEdit->setFixedWidth(250);
    SchoolLineEdit->setFixedWidth(250);
    ClassLineEdit->setFixedWidth(250);
    FirstNameLineEdit->setFixedWidth(250);
    PassLineEdit->setFixedWidth(250);
    CityLineEdit->setAlignment(Qt::AlignLeft);
    SchoolLineEdit->setAlignment(Qt::AlignLeft);
    ClassLineEdit->setAlignment(Qt::AlignLeft);
    FirstNameLineEdit->setAlignment(Qt::AlignLeft);
    PassLineEdit->setAlignment(Qt::AlignLeft);


    EnterButton = new QPushButton("Вход",this);
    SaveDataCheckBox = new QCheckBox("Сохранить пароль",this);
    EnterButton->setFixedWidth(100);


    CentralVLayout->addLayout(DataAutorHLayout);
    CentralVLayout->addLayout(EnterHLayout);
    DataAutorHLayout->addLayout(LabelVLayout);
    DataAutorHLayout->addLayout(LineEditVLayout);

    LabelVLayout->addWidget(CityLabel);
    LabelVLayout->addWidget(SchoolLabel);
    LabelVLayout->addWidget(ClassLabel);
    LabelVLayout->addWidget(FirstNameLabel);
    LabelVLayout->addWidget(PassLabel);


    LineEditVLayout->addWidget(CityLineEdit);
    LineEditVLayout->addWidget(SchoolLineEdit);
    LineEditVLayout->addWidget(ClassLineEdit);
    LineEditVLayout->addWidget(FirstNameLineEdit);
    LineEditVLayout->addWidget(PassLineEdit);


    EnterHLayout->addWidget(EnterButton);
    EnterHLayout->addWidget(SaveDataCheckBox);

    CityLabel->show();
    SchoolLabel->show();
    FirstNameLabel->show();
    PassLabel->show();

    CityLineEdit->show();
    SchoolLineEdit->show();
    FirstNameLineEdit->show();
    PassLineEdit->show();

    EnterButton->show();
    SaveDataCheckBox->setCheckState(Qt::Checked);
    SaveDataCheckBox->show();
}

void authorForm::MyClikc()
{
    if(SaveDataCheckBox->isChecked()){
    emit TestDataSave(CityLineEdit->text(),SchoolLineEdit->text(),
                      ClassLineEdit->text(),FirstNameLineEdit->text(),
                      PassLineEdit->text());
}
    emit MyAuthorization(CityLineEdit->text(),SchoolLineEdit->text(),
                         ClassLineEdit->text(),FirstNameLineEdit->text(),
                         PassLineEdit->text());

    emit TextForTopInterf(CityLineEdit->text(),SchoolLineEdit->text(),
                          ClassLineEdit->text(),FirstNameLineEdit->text());


}
