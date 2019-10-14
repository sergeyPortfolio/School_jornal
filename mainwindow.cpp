#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo;
    authorization = new authorForm(parent);
    logo = QPixmap(QCoreApplication::applicationDirPath()+"/src/picture/Log.bmp");

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
            connect(dataBd,SIGNAL(createTableRaitingSignal(QMap<QString,QMultiMap<int,QPair<QString,int>>>,QString)),user,SLOT(createTable(QMap<QString,QMultiMap<int,QPair<QString,int>>>,QString)));

            top = new TopInterface();
            connect(authorization,SIGNAL(TextForTopInterf(QString,QString,QString,QString)),top,SLOT(author(QString,QString,QString,QString)));
            connect(top->LogOutButtonTop,SIGNAL(clicked()),this,SLOT(ReturnAuthorization()));

            connect(user->EditHomework, SIGNAL(clicked()), dataBd, SLOT(createTableDiscipForHomework()));
            connect(dataBd, SIGNAL(createTableDisciplineForHomeworkSignal(QMap<QString,unsigned int>, QString, QString, QString)), user->homeWorkBoard, SLOT(createTableDisciplineForHomeworkSlot(QMap<QString, unsigned int>, QString, QString, QString)));

            authorization->close();
            ui->verticalLayout->addWidget(user);
            ui->horizontalLayout_2->addWidget(top);
            ui->verticalSpacer_2->changeSize(0,0,QSizePolicy::Minimum);
            ui->verticalSpacer->changeSize(0,0,QSizePolicy::Minimum);
            ChoiseWindow = 1;
        }
        else if(law == "admin")
        {
           admin = new AdminInterface();
           connect(dataBd,SIGNAL(createTableListUserSignal(QMap<QString,QPair<unsigned int,QString>>)),admin,SLOT(createUserList(QMap<QString,QPair<unsigned int,QString>>)));
           connect(admin->message,SIGNAL(NameAndPassSignal(QString, QString)),dataBd,SLOT(InsertStudentSlot(QString, QString)));
           connect(dataBd,SIGNAL(insertDoneOr(bool)),admin->message,SLOT(DoneOrNot(bool)));
           connect(admin->message,SIGNAL(ResetTableUser()),dataBd,SLOT(createTableListUser()));
           connect(admin,SIGNAL(deleteUserSignal(QString)),dataBd,SLOT(deleteUserList(QString)));
           connect(dataBd,SIGNAL(deleteDoneOr(bool)),admin,SLOT(deleteUserDone(bool)));
           connect(admin,SIGNAL(repeatUserList()),dataBd,SLOT(createTableListUser()));
           connect(admin,SIGNAL(createTablePoint(QString)),dataBd,SLOT(createTableRaiting(QString)));
           connect(admin,SIGNAL(createTablePointOnDiscp(QString)),dataBd,SLOT(createTableRaitingOnDiscp(QString)));
           connect(dataBd,SIGNAL(createTableRaitingSignal(QMap<QString,QMultiMap<int,QPair<QString,int>>>,QString)),admin->panelForEdit,SLOT(createTable(QMap<QString,QMultiMap<int,QPair<QString,int>>>,QString)));
           connect(admin->panelForEdit,SIGNAL(deletePointSignal(QString,QString,QString,QString,QString)),dataBd,SLOT(deletePointSlot(QString,QString,QString,QString,QString)));
           connect(admin->panelForEdit,SIGNAL(deletePointOnDiscpSignal(QString,QString,QString,QString,QString)),dataBd,SLOT(deletePointSlotOnDiscp(QString,QString,QString,QString,QString)));
           connect(admin,SIGNAL(createTableDiscipline()),dataBd,SLOT(createTableDiscipline()));
           connect(dataBd,SIGNAL(createTableDisciplineSignal(QMap<QString,unsigned int>)),admin,SLOT(createTableDisciplineSlot(QMap<QString,unsigned int>)));
           connect(admin->panelForEditDisc,SIGNAL(editDisciplineSignal(QString)),dataBd,SLOT(editDiscipline(QString)));
           connect(admin,SIGNAL(deleteDisciplineSignal(QString)),dataBd,SLOT(deleteDiscipline(QString)));
           connect(admin->panelForEdit,SIGNAL(editPointSignal(QString,QString,QString,QStringList)),dataBd,SLOT(editPointSlot(QString,QString,QString,QStringList)));
           connect(admin->panelForEdit,SIGNAL(editPointSignalOnDiscp(QString,QString,QString,QStringList)),dataBd,SLOT(editPointSlotOnDiscp(QString,QString,QString,QStringList)));
           connect(admin->panelForEdit,SIGNAL(deleteAllPointSignal(QString,QString)),dataBd,SLOT(deleteAllPointSlot(QString,QString)));
           connect(admin->panelForEdit,SIGNAL(deleteAllPointSignalOnDiscp(QString,QString)),dataBd,SLOT(deleteAllPointSlotOnDiscp(QString,QString)));
           connect(admin->panelForEdit,SIGNAL(updatePointSignal(QString,QString,QString)),dataBd,SLOT(updatePointSlot(QString,QString,QString)));
           connect(admin->panelForEdit,SIGNAL(updatePointSignalonDiscp(QString,QString,QString)),dataBd,SLOT(updatePointSlotOnDiscp(QString,QString,QString)));
           connect(admin,SIGNAL(updateUserLawSignal(QString)),dataBd,SLOT(updateUserLaw(QString)));

           connect(admin->EditHomework, SIGNAL(clicked()), dataBd, SLOT(createTableDiscipForHomework()));
           connect(dataBd, SIGNAL(createTableDisciplineForHomeworkSignal(QMap<QString,unsigned int>, QString, QString, QString)), admin->homeWorkBoard, SLOT(createTableDisciplineForHomeworkSlot(QMap<QString, unsigned int>, QString, QString, QString)));
           connect(admin->homeWorkBoard, SIGNAL(sendHomeWork(QMultiMap<QString, QPair<QString, QString>>)), dataBd, SLOT(saveHomeWork(QMultiMap<QString, QPair<QString, QString>>)));
           connect(admin->homeWorkBoard, SIGNAL(addTaskToBoard()), dataBd, SLOT(updateBoard()));
           connect(dataBd,SIGNAL(updateHomeWorkBoard(QMap < unsigned int, QPair<QString, QPair<QString, QString>>>)), admin->homeWorkBoard, SLOT(updateHomeWorkBoard(QMap < unsigned int, QPair<QString, QPair<QString, QString>>>)));
           connect(admin->homeWorkBoard, SIGNAL(updateTask(QString, QString)), dataBd ,SLOT(updateTask(QString, QString)));
           connect(admin->homeWorkBoard, SIGNAL(deleteTask(QString)), dataBd ,SLOT(deleteTask(QString)));

           top = new TopInterface();
           connect(authorization,SIGNAL(TextForTopInterf(QString,QString,QString,QString)),top,SLOT(author(QString,QString,QString,QString)));
           connect(top->LogOutButtonTop,SIGNAL(clicked()),this,SLOT(ReturnAuthorization()));

           authorization->close();
           ui->horizontalLayout_2->addWidget(top);
           ui->verticalLayout->addWidget(admin);
           ui->verticalSpacer_2->changeSize(0,0,QSizePolicy::Minimum);
           ui->verticalSpacer->changeSize(0,0,QSizePolicy::Minimum);
           ChoiseWindow = 2;
        }
        else if(law == "moder")
        {
            moder = new ModerReiting();
            connect(dataBd,SIGNAL(createTableRaitingSignal(QMap<QString,QMultiMap<int,QPair<QString,int>>>,QString)),moder,SLOT(createTable(QMap<QString,QMultiMap<int,QPair<QString,int>>>,QString)));

            top = new TopInterface();
            connect(authorization,SIGNAL(TextForTopInterf(QString,QString,QString,QString)),top,SLOT(author(QString,QString,QString,QString)));
            connect(top->LogOutButtonTop,SIGNAL(clicked()),this,SLOT(ReturnAuthorization()));

            connect(moder->EditHomework, SIGNAL(clicked()), dataBd, SLOT(createTableDiscipForHomework()));
            connect(dataBd, SIGNAL(createTableDisciplineForHomeworkSignal(QMap<QString,unsigned int>, QString, QString, QString)), moder->homeWorkBoard, SLOT(createTableDisciplineForHomeworkSlot(QMap<QString, unsigned int>, QString, QString, QString)));
            connect(moder->homeWorkBoard, SIGNAL(sendHomeWork(QMultiMap<QString, QPair<QString, QString>>)), dataBd, SLOT(saveHomeWork(QMultiMap<QString, QPair<QString, QString>>)));
            connect(moder->homeWorkBoard, SIGNAL(addTaskToBoard()), dataBd, SLOT(updateBoard()));
            connect(dataBd,SIGNAL(updateHomeWorkBoard(QMap < unsigned int, QPair<QString, QPair<QString, QString>>>)), moder->homeWorkBoard, SLOT(updateHomeWorkBoard(QMap < unsigned int, QPair<QString, QPair<QString, QString>>>)));
            connect(moder->homeWorkBoard, SIGNAL(updateTask(QString, QString)), dataBd ,SLOT(updateTask(QString, QString)));
            connect(moder->homeWorkBoard, SIGNAL(deleteTask(QString)), dataBd ,SLOT(deleteTask(QString)));


            authorization->close();
            ui->verticalLayout->addWidget(moder);
            ui->horizontalLayout_2->addWidget(top);
            ui->verticalSpacer_2->changeSize(0,0,QSizePolicy::Minimum);
            ui->verticalSpacer->changeSize(0,0,QSizePolicy::Minimum);
            ChoiseWindow = 3;
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
    else if(ChoiseWindow == 3)
    {
        moder->close();
    }
    ui->verticalSpacer_2->changeSize(100,100,QSizePolicy::Maximum);
    ui->verticalSpacer->changeSize(100,100,QSizePolicy::Maximum);
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


