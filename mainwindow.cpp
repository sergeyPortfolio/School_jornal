#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo;
    authorization = new authorForm(parent);
    logo = QPixmap(QDir::currentPath()+ "/src/picture/Log.bmp");

    ui->label->setPixmap(logo);
    ui->verticalLayout->addWidget(authorization);
    dataBd = new DataBase();
    dataBd->connectToDataBase();
    connect(authorization->EnterButton,SIGNAL(clicked()),authorization,SLOT(MyClikc()));
    connect(authorization,SIGNAL(MyAuthorization(QString,QString,QString,QString,QString,bool)),dataBd,SLOT(AuthorSql(QString,QString,QString,QString,QString,bool)));

    connect(dataBd,SIGNAL(OpenNewWindow(int,QString,QString,bool)),this,SLOT(CreateNewWindow(int ,QString,QString,bool)));
    connect(authorization,SIGNAL(TestDataSave(QString,QString,QString,QString,QString)),this,SLOT(ForSave(QString,QString,QString,QString,QString)));

    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateNewWindow(int id,QString law,QString accses,bool save)
{
    if(id != 0 && accses == "on")
    {
        if(save == true)
        {
            saveDataFile(forSavecity,ForSaveschool,ForSaveclass,ForSavename,ForSavepass);
        }
        if(law =="user")
        {
            user = new UserReiting();
            connect(dataBd,SIGNAL(createTableRaitingSignal(QMap<QString,QMultiMap<QString,int>>)),user,SLOT(createTable(QMap<QString,QMultiMap<QString,int>>)));

            top = new TopInterface();
            connect(authorization,SIGNAL(TextForTopInterf(QString,QString,QString,QString)),top,SLOT(author(QString,QString,QString,QString)));
            connect(top->LogOutButtonTop,SIGNAL(clicked()),this,SLOT(ReturnAuthorization()));

            authorization->close();
            ui->verticalLayout->addWidget(user);
            ui->horizontalLayout_2->addWidget(top);
            ChoiseWindow = 1;
        }
        else if(law == "admin")
        {
           admin = new AdminInterface();
           connect(dataBd,SIGNAL(createTableListUserSignal(QMap<QString,unsigned int>)),admin,SLOT(createUserList(QMap<QString,unsigned int>)));
           connect(admin->message,SIGNAL(NameAndPassSignal(QString, QString)),dataBd,SLOT(InsertStudentSlot(QString, QString)));
           connect(dataBd,SIGNAL(insertDoneOr(bool)),admin->message,SLOT(DoneOrNot(bool)));
           connect(admin->message,SIGNAL(ResetTableUser()),dataBd,SLOT(createTableListUser()));
           connect(admin,SIGNAL(deleteUserSignal(QString)),dataBd,SLOT(deleteUserList(QString)));
           connect(dataBd,SIGNAL(deleteDoneOr(bool)),admin,SLOT(deleteUserDone(bool)));
           connect(admin,SIGNAL(repeatUserList()),dataBd,SLOT(createTableListUser()));
           connect(admin,SIGNAL(createTablePoint(QString)),dataBd,SLOT(createTableRaiting(QString)));
           connect(dataBd,SIGNAL(createTableRaitingSignal(QMap<QString,QMultiMap<QString,int>>)),admin->panelForEdit,SLOT( createTable(QMap<QString,QMultiMap<QString,int>>)));
           connect(admin->panelForEdit,SIGNAL(deletePointSignal(QString,QString,QString,QString)),dataBd,SLOT(deletePointSlot(QString,QString,QString,QString)));
           connect(admin,SIGNAL(createTableDiscipline()),dataBd,SLOT(createTableDiscipline()));
           connect(dataBd,SIGNAL(createTableDisciplineSignal(QMap<QString,unsigned int>)),admin->panelForEditDisc,SLOT(createTableDiscipline(QMap<QString,unsigned int>)));
           connect(admin->panelForEditDisc,SIGNAL(editDisciplineSignal(QString)),dataBd,SLOT(editDiscipline(QString)));
           connect(admin->panelForEditDisc,SIGNAL(deleteDisciplineSignal(QString)),dataBd,SLOT(deleteDiscipline(QString)));
           connect(admin->panelForEdit,SIGNAL(editPointSignal(QString,QString,QString,QString)),dataBd,SLOT( editPointSlot(QString,QString,QString,QString)));
           connect(admin->panelForEdit,SIGNAL(deleteAllPointSignal(QString,QString)),dataBd,SLOT(deleteAllPointSlot(QString,QString)));

           top = new TopInterface();
           connect(authorization,SIGNAL(TextForTopInterf(QString,QString,QString,QString)),top,SLOT(author(QString,QString,QString,QString)));
           connect(top->LogOutButtonTop,SIGNAL(clicked()),this,SLOT(ReturnAuthorization()));

           authorization->close();
           ui->horizontalLayout_2->addWidget(top);
           ui->verticalLayout->addWidget(admin);
           ChoiseWindow = 2;
        }
    }
    else
    {
         message = new QMessageBox();
        if(accses == "off")
        {
           message->setText("Доступ обмежено");
           message->show();
        }
        else if(id == 0)
        {
            message->setText("Дані вказані не вірно");
            message->show();
        }
    }
}

void MainWindow::ForSave(QString Ucity, QString Uschool, QString Uclass, QString Uname, QString Upass)
{
    forSavecity = Ucity;
    ForSaveschool = Uschool;
    ForSaveclass = Uclass;
    ForSavename =Uname;
    ForSavepass = Upass;
}

void MainWindow::ReturnAuthorization()
{
    if(ChoiseWindow == 1)
    {
        user->close();
    }
    else if(ChoiseWindow == 2)
    {
        admin->close();
    }
    authorization->show();
    top->close();
}

void MainWindow::saveDataFile(QString Ucity, QString Uschool,QString Uclass,QString Uname,QString Upass)
{
    QFile fileOut("MySettings.txt");
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream writeStream(&fileOut);
            writeStream.setCodec("utf-8");
            writeStream << Ucity << "\n";
            writeStream << Uschool << "\n";
            writeStream << Uclass << "\n";
            writeStream << Uname << "\n";
            writeStream << Upass << "\n";
            fileOut.close();
        }
}
