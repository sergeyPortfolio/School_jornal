#include "database.h"


DataBase::DataBase(QObject *parent) : QObject(parent)
{

}
void DataBase::connectToDataBase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("school_jor");
    db.setUserName("root");
    db.setPassword("root");
    if(!db.open()){
        qDebug() << db.lastError().text() << "V KONECTION";

    }
    else
    {
         query = db.exec("SET NAMES 'utf8'");
        qDebug() << "sucsec" ;
    }
}

void DataBase::createTableRaiting(QString nameUserKey)
{
    QString idText = "";
    if(nameUserKey == "user")
    {
        idText = QString::number(id);
    }
    else
    {
        unsigned int id_user = myMapUserList[nameUserKey];
        idText = QString::number(id_user);
    }
   if(query.exec("SELECT disc_name,type_point,point FROM point WHERE id_user = "+idText+" " "ORDER BY FIELD (type_point, 'global','local')"))
   {

       QMap<QString,QMultiMap<QString,int>> myMap;
       QString key;

        while(query.next())
        {
            key=query.value(0).toString();
            QMultiMap<QString,int> pairMap;
            const auto found = myMap.find(key);
            if(found==myMap.cend())
            {

                pairMap.insert(query.value(1).toString(),query.value(2).toInt());
                 myMap.insert(key,pairMap);
            }
            else
            {
                QMultiMap<QString,int> pairMapProm;
                pairMapProm = myMap[key];
                pairMapProm.insert(query.value(1).toString(),query.value(2).toInt());
                myMap[key] = pairMapProm;
                //qDebug() << pairMapProm;
            }

       }
        //qDebug() << myMap;
        emit  createTableRaitingSignal(myMap);

   }
   else
   {
        qDebug() << "no Point";
   }
}

void DataBase::createTableListUser()
{
    myMapUserList.clear();
    //qDebug() << CityAdmin;
    //qDebug() << SchoolAdmin.toInt();
    //qDebug() << ClassAdmin;
  if(query.exec("SELECT id_user,name FROM users "
                "WHERE city='"+CityAdmin+
                "'AND school='"+SchoolAdmin+
                "'AND class='"+ClassAdmin+
                "'AND law ='user'"))
  {


       while(query.next())
       {
           myMapUserList.insert(query.value(1).toString(),query.value(0).toUInt());
           //qDebug()<<query.value(0) << "qury";
       }

       emit  createTableListUserSignal(myMapUserList);
  }
  else
  {
       qDebug() << "no User";
  }
}

void DataBase::deleteUserList(QString key)
{
    unsigned int id_user = myMapUserList[key];
    if(query.exec("DELETE FROM users WHERE id_user ='"+QString::number(id_user)+"'"))
    {
        emit deleteDoneOr(true);
    }
    else
    {
        emit deleteDoneOr(false);
    }


}


void DataBase::AuthorSql(const QString city, const QString school, const QString clas, const QString firstn, const QString pass)
{

    if(query.exec( "SELECT id_user,law FROM users "
                   "WHERE city='"+city+"' "
                   "AND school='"+school+"' "
                   "AND class='"+clas+"' "
                   "AND name='"+firstn+"'"
                   "AND pass='"+pass+"'" ))
    {

        CityAdmin = city;
        SchoolAdmin = school;
        ClassAdmin = clas;
        QString law;

        while(query.next())
        {
           id = query.value(0).toInt();
           law = query.value(1).toString();
        }

        //qDebug() << law;
        emit OpenNewWindow(id,law);

        if(law == "user")
        {
            createTableRaiting("user");
        }
        else
        {
            createTableListUser();
        }
    }
    else
    {
        qDebug() << "no Autor";
    }
}

void DataBase::InsertStudentSlot(QString nameStudent,QString PassStudent)
{

    if(query.exec( "INSERT INTO users (id_user,city,school,class,name,law,pass) values(default, '"+CityAdmin+"','"+SchoolAdmin+"','"+ClassAdmin+"','"+nameStudent+"','user','"+PassStudent+"')"))
    {
        emit insertDoneOr(true);
    }
    else
    {
        emit insertDoneOr(false);

    }
}
