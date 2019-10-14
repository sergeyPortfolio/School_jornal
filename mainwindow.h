#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authorform.h"
#include "database.h"
#include "topinterface.h"
#include "admininterface.h"
#include "moderreiting.h"
#include "userreiting.h"
#include <QFile>
#include <QTextStream>
#include <QMultiMap>
#include <QPair>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void CreateNewWindow(int id,QString law,QString accses,bool save);
    void ForSave(QString Ucity, QString Uschool,QString Uclass,QString Uname,QString Upass);
    void ReturnAuthorization();
private:
    QString forSavecity;
    QString ForSaveschool;
    QString ForSaveclass;
    QString ForSavename;
    QString ForSavepass;
    int ChoiseWindow;

    Ui::MainWindow *ui;
    authorForm *authorization;
    TopInterface *top;
    DataBase *dataBd;
    UserReiting *user;
    AdminInterface *admin;
    ModerReiting *moder;
    QMessageBox *message;

    void saveDataFile(QString Ucity, QString Uschool,QString Uclass,QString Uname,QString Upass);

};

#endif // MAINWINDOW_H
