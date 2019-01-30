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
#include <QTextCodec>

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
     void OpenNewWindow(int,QString,QString,bool);
     void createTableListUserSignal(QMap<QString,unsigned int>);
     void createTableRaitingSignal(QMap<QString,QMultiMap<QString,int>>);
     void insertDoneOr(bool);
     void deleteDoneOr(bool);
     void createTableDisciplineSignal(QMap<QString,unsigned int>);
public:
     void connectToDataBase();



public slots:
    void AuthorSql(const QString city,const QString school, const QString clas, const QString firstn,const QString pass,bool save);
    void InsertStudentSlot(QString nameStudent,QString PassStudent);
    void createTableListUser();
    void deleteUserList(QString key);
    void createTableRaiting(QString);
    void createTableDiscipline();
    void editDiscipline(QString);
    void deleteDiscipline(QString);
    void deletePointSlot(QString id,QString nameDisc,QString Type,QString Point);
    void editPointSlot(QString id,QString nameDisc,QString Type,QString Point);
    void deleteAllPointSlot(QString,QString);
};

#endif // DATABASE_H
