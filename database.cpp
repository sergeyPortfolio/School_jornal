#include "database.h"


DataBase::DataBase(QObject *parent) : QObject(parent)
{

}
void DataBase::connectToDataBase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("95.46.99.156");
    db.setPort(3306);

    db.setDatabaseName("school_jornal");
    db.setUserName("user");
    db.setPassword("root");
    if(!db.open()){
       // qDebug() << db.lastError().text() << "V KONECTION"
        message = new QMessageBox();
        message->setText(db.lastError().text());
        message->show();

    }
    else
    {
         query = db.exec("SET NAMES 'utf8'");
       // qDebug() << "sucsec" ;
    }
}

void DataBase::createTableRaiting(QString nameUserKey)
{
    QMap<QString,QMultiMap<QString,int>> myMap;
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

    if(query.exec("SELECT name_disc FROM discipline WHERE city ='"+CityAdmin+"'AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
       QString key;
       QMultiMap<QString,int> pairMap;
       while(query.next())
       {

           key = query.value(0).toString();
           myMap.insert(key,pairMap);
       }

    }
    else
    {
       // qDebug() << "no discipline";
    }
   if(query.exec("SELECT disc_name,type_point,point FROM point WHERE id_user = "+idText+" ORDER BY id DESC"))
   {


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
        emit  createTableRaitingSignal(myMap);

   }
   else
   {
       // qDebug() << "no Point";
   }
}

void DataBase::createTableDiscipline()
{
    if(query.exec("SELECT id_disc,name_disc FROM discipline WHERE city ='"+CityAdmin+"'AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
        QMap<QString,unsigned int> discip;
        while(query.next())
        {
            discip.insert(query.value(1).toString(),query.value(0).toUInt());
        }
        emit createTableDisciplineSignal(discip);
    }
    else
    {
        //qDebug() << "no discip";
    }
}

void DataBase::editDiscipline(QString name_disc)
{

    if(query.exec( "INSERT INTO discipline (id_disc,name_disc,city,school,class) values(default, '"+name_disc+"','"+CityAdmin+"','"+SchoolAdmin+"','"+ClassAdmin+"')"))
    {
        createTableDiscipline();
    }

}

void DataBase::deleteDiscipline(QString nameDisc)
{
    if(query.exec("DELETE FROM discipline WHERE name_disc ='"+nameDisc+"' AND city = '"+CityAdmin+"' AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
        createTableDiscipline();
    }
}

void DataBase::deletePointSlot(QString idName,QString nameDisc, QString Type, QString Point)
{
    QString t;
    if(Type == "Тематична")
    {
        t = "global";
    }
    else if( Type == "Поточна")
    {
        t = "local";
    }
    unsigned int id = myMapUserList[idName];

    if(query.exec("DELETE FROM point WHERE id_user ='"+QString::number(id)+"' AND disc_name ='"+nameDisc+"' AND type_point = '"+t+"' AND point ='"+Point+"'"))
    {
        createTableRaiting(idName);
    }
}

void DataBase::editPointSlot(QString idName, QString nameDisc, QString Type, QString Point)
{
    unsigned int id = myMapUserList[idName];

    if(query.exec("INSERT INTO point (id,id_user,disc_name,type_point,point) values(default, '"+QString::number(id)+"','"+nameDisc+"','"+Type+"','"+Point+"')"))
    {
        createTableRaiting(idName);
    }
}

void DataBase::deleteAllPointSlot(QString idName, QString nameDisc)
{
    //qDebug() <<idName << nameDisc;
    unsigned int id = myMapUserList[idName];
    if(query.exec("DELETE FROM point WHERE id_user ='"+QString::number(id)+"' AND disc_name ='"+nameDisc+"' AND type_point = 'local'"))
    {
        createTableRaiting(idName);
    }
}

void DataBase::createTableListUser()
{
    myMapUserList.clear();

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
       //qDebug() << "no User";
  }
}

void DataBase::deleteUserList(QString key)
{
    unsigned int id_user = myMapUserList[key];
    if(query.exec("DELETE FROM point WHERE id_user ='"+QString::number(id_user)+"'"))
    {
        if(query.exec("DELETE FROM users WHERE id_user ='"+QString::number(id_user)+"'"))
        {
            emit deleteDoneOr(true);
        }
        else
        {
            emit deleteDoneOr(false);
        }
    }
    else
    {
        emit deleteDoneOr(false);
    }
}


void DataBase::AuthorSql(const QString city, const QString school, const QString clas, const QString firstn, const QString pass , bool save)
{
    if(query.exec( "SELECT id_user,law,accses FROM users "
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
        QString accses;
        while(query.next())
        {
           // qDebug() << query.value(0).toInt();
           // qDebug() << query.value(1).toString();
           id = query.value(0).toInt();
           law = query.value(1).toString();
           accses = query.value(2).toString();
          //qDebug() << id << law;
        }

        //qDebug() << law;
        emit OpenNewWindow(id,law,accses,save);

        if(law == "user")
        {
            createTableRaiting("user");
        }
        else if(law =="admin")
        {
            createTableListUser();
        }
        else
        {    id = 0;
             emit OpenNewWindow(id,law,accses,save);
        }
    }
    else
    {
       // qDebug() << "no Autor";
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
