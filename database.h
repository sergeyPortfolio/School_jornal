#ifndef DATABASE_H
#define DATABASE_H


#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QMap>
#include <QMultiMap>

class DataBase : public QObject
{
    Q_OBJECT
private:
     QMap<QString,unsigned int> myMapUserList;
     QSqlDatabase    db;
     QSqlQuery query;
     int id;
     QString SchoolAdmin;
     QString ClassAdmin;
     QString CityAdmin;
public:
    explicit DataBase(QObject *parent = nullptr);
    signals:
     void OpenNewWindow(int,QString);
     void createTableListUserSignal(QMap<QString,unsigned int>);
     void createTableRaitingSignal(QMap<QString,QMultiMap<QString,int>>);
     void insertDoneOr(bool);
     void deleteDoneOr(bool);
public:
     void connectToDataBase();



public slots:
    void AuthorSql(const QString city,const QString school, const QString clas, const QString firstn,const QString pass);
    void InsertStudentSlot(QString nameStudent,QString PassStudent);
    void createTableListUser();
    void deleteUserList(QString key);
    void createTableRaiting(QString);
};

#endif // DATABASE_H
