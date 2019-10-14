#ifndef DATABASE_H
#define DATABASE_H


#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QMap>
#include <QPair>
#include <QMultiMap>
#include <QVariant>
#include <QMessageBox>

class DataBase : public QObject
{
    Q_OBJECT
private:
     QString dayToInt(QString day);

     QMap<QString,QPair<unsigned int,QString>> myMapUserList;
     QMap<QString,unsigned int> discip;
     QSqlDatabase    db;
     QSqlQuery query;
     int id;
     QString SchoolAdmin;
     QString ClassAdmin;
     QString CityAdmin;
     QMessageBox *message;
public:
    explicit DataBase(QObject *parent = nullptr);


signals:
     void OpenNewWindow(int,QString,QString,bool);
     void createTableListUserSignal(QMap<QString,QPair<unsigned int,QString>>);
     void createTableRaitingSignal(QMap<QString,QMultiMap<int,QPair<QString,int>>>, QString);
     void insertDoneOr(bool);
     void deleteDoneOr(bool);
     void createTableDisciplineSignal(QMap<QString,unsigned int>);
     void createTableDisciplineForHomeworkSignal(QMap<QString,unsigned int>, QString, QString, QString);
     void updateHomeWorkBoard(QMap < unsigned int, QPair<QString, QPair<QString, QString>>>);

public:
     void connectToDataBase();



public slots:
    void AuthorSql(const QString city,const QString school, const QString clas, const QString firstn,const QString pass,bool save);
    void InsertStudentSlot(QString nameStudent,QString PassStudent);
    void createTableListUser();
    void deleteUserList(QString key);
    void createTableRaiting(QString);
    void createTableRaitingOnDiscp(QString);
    void createTableDiscipline();
    void editDiscipline(QString);
    void deleteDiscipline(QString);
    void deletePointSlot(QString id,QString nameDisc,QString Type,QString Point, QString idPoint);
    void deletePointSlotOnDiscp(QString id,QString userName,QString Type,QString Point, QString idPoint);
    void editPointSlot(QString id,QString nameDisc,QString Type,QStringList Point);
    void editPointSlotOnDiscp(QString id,QString nameDisc,QString Type,QStringList Point);
    void deleteAllPointSlotOnDiscp(QString NameDiscp,QString NameUser);
    void deleteAllPointSlot(QString,QString);
    void updatePointSlot(QString,QString,QString);
    void updatePointSlotOnDiscp(QString,QString,QString);
    void updateUserLaw(QString);
    void createTableDiscipForHomework();
    void saveHomeWork(QMultiMap<QString, QPair<QString, QString>> listTask);
    void updateBoard();
    void updateTask(QString, QString);
    void deleteTask(QString);
};

#endif // DATABASE_H
