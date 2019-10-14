#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}
void DataBase::connectToDataBase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("194.9.71.94");                            //db.setHostName("95.46.99.156");
    db.setPort(3306);

    db.setDatabaseName("school_jornal");
    db.setUserName("schooluser");                                    //db.setUserName("user");
    db.setPassword("school123");
    if(!db.open()){

        message = new QMessageBox();
        message->setText(db.lastError().text());
        message->show();

    }
    else
    {
         query = db.exec("SET NAMES 'utf8'");

    }
}

void DataBase::createTableRaiting(QString nameUserKey)
{
    QMap<QString,QMultiMap<int,QPair<QString,int>>> myMap;
    QString idText = "";
    if(nameUserKey == "user" || nameUserKey == "moder")
    {
        idText = QString::number(id);
    }
    else
    {
        //QPair<unsigned int,QString> userListPair;

        unsigned int id_user = myMapUserList[nameUserKey].first;
        idText = QString::number(id_user);
    }

    if(query.exec("SELECT name_disc FROM discipline WHERE city ='"+CityAdmin+"'"
                  "AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
       QString key;
       QMultiMap<int,QPair<QString,int>> pairMap;
       while(query.next())
       {

           key = query.value(0).toString();
           myMap.insert(key,pairMap);
       }

    }
    else
    {

    }
   if(query.exec("SELECT disc_name,type_point,point,id FROM point WHERE id_user = "+idText+" ORDER BY id DESC"))
   {
       QString key;

        while(query.next())
        {
            key=query.value(0).toString();
            QPair <QString,int> pair;
            QMultiMap<int,QPair<QString,int>> pairMap;
            const auto found = myMap.find(key);
            if(found==myMap.cend())
            {
                pair.first = query.value(1).toString();
                pair.second = query.value(2).toInt();
                pairMap.insert(query.value(3).toInt(),pair);
                 myMap.insert(key,pairMap);
            }
            else
            {
                QMultiMap<int,QPair<QString,int>> pairMapProm;
                pairMapProm = myMap[key];
                pair.first = query.value(1).toString();
                pair.second = query.value(2).toInt();
                pairMapProm.insert(query.value(3).toInt(),pair);
               // pairMapProm.insert(query.value(1).toString(),query.value(2).toInt());
                myMap[key] = pairMapProm;

            }

       }
        QString Flag = "onUser";

        emit  createTableRaitingSignal(myMap,Flag);

   }
}

void DataBase::createTableRaitingOnDiscp(QString nameDiscp)
{
    QMap<QString,QMultiMap<int,QPair<QString,int>>> myMap;
    QString id = QString::number(discip[nameDiscp]);

    if(query.exec("SELECT name FROM users WHERE city ='"+CityAdmin+"'"
                  "AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'AND (law = 'user' OR law = 'moder') "))
    {
       QString key;
       QPair<QString,int> pair;
       QMultiMap<int,QPair<QString,int>> pairMap;
       while(query.next())
       {

           key = query.value(0).toString();
           myMap.insert(key,pairMap);
       }
    }
    if(query.exec("SELECT id_user,type_point,point,id FROM point  WHERE disc_name ='"+nameDiscp+"' "
                  "AND city ='"+CityAdmin+"'AND school ='"+SchoolAdmin+"' "
                  "AND class = '"+ClassAdmin+"' ORDER BY id DESC" ))
    {
        unsigned int key;
        QPair<unsigned int,QString> userList;
        while(query.next())
        {
            key = query.value(0).toUInt();
            QSqlQuery query2;
            if(query2.exec("SELECT law FROM users WHERE id_user = '"+QString::number(key)+"'"))
            {
                while(query2.next())
                {
                    userList.second = query2.value(0).toString();
                }
            }

            //QMultiMap<QString,int> pairMap;
                      ////////
            userList.first = key;
            //userListt.second = "user";
           // qDebug() << myMapUserList;
            QPair <QString,int> pair;
            QMultiMap<int,QPair<QString,int>> pairMap;
            //const auto found = myMap.find(myMapUserList.key(key));
            const auto found = myMap.find(myMapUserList.key(userList));
//            auto f = myMapUserList.key(userListt);

  //          qDebug() << f;

            if(found==myMap.cend())
            {
                pair.first = query.value(1).toString();
                pair.second = query.value(2).toInt();
                pairMap.insert(query.value(3).toInt(),pair);
               // QPair<unsigned int,QString> userList;
               // userList.first = key;
                 myMap.insert(myMapUserList.key(userList),pairMap);
            }
            else
            {
               // QPair<unsigned int,QString> userList;
                //userList.first = key;
                QMultiMap<int,QPair<QString,int>> pairMapProm;
                pairMapProm = myMap[myMapUserList.key(userList)];
                pair.first = query.value(1).toString();
                pair.second = query.value(2).toInt();
                pairMapProm.insert(query.value(3).toInt(),pair);
                myMap[myMapUserList.key(userList)] = pairMapProm;

            }
        }
        QString Flag = "onDiscp";
        emit  createTableRaitingSignal(myMap,Flag);
    }
}

void DataBase::createTableDiscipline()
{
    discip.clear();
    if(query.exec("SELECT id_disc,name_disc FROM discipline WHERE city ='"+CityAdmin+"'"
                  "AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
        while(query.next())
        {
            discip.insert(query.value(1).toString(),query.value(0).toUInt());
        }
        emit createTableDisciplineSignal(discip);
    }
    else
    {

    }
}

void DataBase::editDiscipline(QString name_disc)
{

    if(query.exec( "INSERT INTO discipline (id_disc,name_disc,city,school,class) "
                   "values(default, '"+name_disc+"','"+CityAdmin+"','"+SchoolAdmin+"','"+ClassAdmin+"')"))
    {
        createTableDiscipline();
    }

}

void DataBase::deleteDiscipline(QString nameDisc)
{
    if(query.exec("DELETE FROM discipline WHERE name_disc ='"+nameDisc+"' "
                  "AND city = '"+CityAdmin+"' AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
        if(query.exec("DELETE FROM point WHERE disc_name ='"+nameDisc+"' "
                      "AND city = '"+CityAdmin+"'AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
        {
           createTableDiscipline();
        }
    }
}

void DataBase::deletePointSlot(QString idName,QString nameDisc, QString Type, QString Point, QString idPoint)
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


    unsigned int id = myMapUserList[idName].first;

    if(query.exec("DELETE FROM point WHERE id ='"+idPoint+"' AND id_user ='"+QString::number(id)+"' "
                  "AND disc_name ='"+nameDisc+"' AND type_point = '"+t+"' "
                  "AND point ='"+Point+"' AND city ='"+CityAdmin+"'AND school = '"+SchoolAdmin+"'"
                  "AND class='"+ClassAdmin+"' "))
    {
        createTableRaiting(idName);
    }
}

void DataBase::deletePointSlotOnDiscp(QString idname, QString userName, QString Type, QString Point, QString idPoint)
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

    unsigned int iduser = myMapUserList[userName].first;
    if(query.exec("DELETE FROM point WHERE id ='"+idPoint+"' AND id_user ='"+QString::number(iduser)+"' "
                  "AND disc_name ='"+idname+"' AND type_point = '"+t+"' "
                  "AND point ='"+Point+"' AND city ='"+CityAdmin+"'AND school = '"+SchoolAdmin+"'"
                  "AND class='"+ClassAdmin+"' "))
    {

        createTableRaitingOnDiscp(idname);

    }
}

void DataBase::editPointSlot(QString idName, QString nameDisc, QString Type, QStringList Point)
{

    unsigned int id = myMapUserList[idName].first;
    int lengthPoint = Point.length();
    for(int i =0; i<lengthPoint; i++)
    {
        if(query.exec("INSERT INTO point (id,id_user,disc_name,type_point,point,city,school,class) "
                      "values(default, '"+QString::number(id)+"',"
                      "'"+nameDisc+"','"+Type+"','"+Point[i]+"',"
                      "'"+CityAdmin+"','"+SchoolAdmin+"','"+ClassAdmin+"')"))
        {
            createTableRaiting(idName);
        }
    }
}

void DataBase::editPointSlotOnDiscp(QString NameDiscp, QString nameStudent, QString Type, QStringList Point)
{
    unsigned int id = myMapUserList[nameStudent].first;
    int lengthPoint = Point.length();
    for(int i =0; i<lengthPoint; i++)
    {
        if(query.exec("INSERT INTO point (id,id_user,disc_name,type_point,point,city,school,class) "
                      "values(default, '"+QString::number(id)+"','"+NameDiscp+"','"+Type+"',"
                      "'"+Point[i]+"','"+CityAdmin+"','"+SchoolAdmin+"','"+ClassAdmin+"')"))
        {
            createTableRaitingOnDiscp(NameDiscp);
        }
    }
}

void DataBase::deleteAllPointSlotOnDiscp(QString NameDiscp, QString NameUser)
{
    unsigned int id = myMapUserList[NameUser].first;
    if(query.exec("DELETE FROM point WHERE id_user ='"+QString::number(id)+"' "
                  "AND disc_name ='"+NameDiscp+"' AND type_point = 'local'"))
    {
        createTableRaitingOnDiscp(NameDiscp);
    }
}


void DataBase::deleteAllPointSlot(QString idName, QString nameDisc)
{

    unsigned int id = myMapUserList[idName].first;
    if(query.exec("DELETE FROM point WHERE id_user ='"+QString::number(id)+"' "
                  "AND disc_name ='"+nameDisc+"' AND type_point = 'local'"))
    {
        createTableRaiting(idName);
    }
}

void DataBase::updatePointSlot(QString idPoint,QString idName,QString point)
{
    if(query.exec("UPDATE `point` SET `point` = '"+point+"' WHERE `id` = '"+idPoint+"'"))
    {
        createTableRaiting(idName);
    }
}

void DataBase::updatePointSlotOnDiscp(QString idPoint, QString NameDiscp, QString point)
{

    if(query.exec("UPDATE `point` SET `point` = '"+point+"' WHERE `id` = '"+idPoint+"'"))
    {
        createTableRaitingOnDiscp(NameDiscp);
    }
}

void DataBase::updateUserLaw(QString nameStudent)
{

    unsigned int id_user = myMapUserList[nameStudent].first;

    if(query.exec("SELECT law FROM users WHERE id_user = "+QString::number(id_user)+""))
    {
        QString law;
        while(query.next())
        {
            law = query.value(0).toString();

        }
        if(law == "user")
        {
            if(query.exec("UPDATE `users` SET `law` = 'moder' WHERE id_user = "+QString::number(id_user)+""))
            {
                createTableListUser();
            }
        }
        else if(law == "moder")
        {
            if(query.exec("UPDATE `users` SET `law` = 'user' WHERE id_user = "+QString::number(id_user)+""))
            {
                createTableListUser();
            }
        }
    }
}

void DataBase::createTableDiscipForHomework()
{
    discip.clear();
    if(query.exec("SELECT id_disc,name_disc FROM discipline WHERE city ='"+CityAdmin+"'"
                  "AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
        while(query.next())
        {
            discip.insert(query.value(1).toString(),query.value(0).toUInt());
        }
        emit createTableDisciplineForHomeworkSignal(discip, CityAdmin, SchoolAdmin, ClassAdmin );
    }
    else
    {

    }
}

void DataBase::saveHomeWork(QMultiMap<QString, QPair<QString, QString> > listTask)
{

    QPair<QString, QString> pair;
    for(auto it = listTask.begin(); it != listTask.end(); it++)
    {
        pair = it.value();

        if(query.exec( "INSERT INTO homework ( id_work, day, discp, homework, city, school, class ) "
                       "values ( default, '"+ dayToInt(it.key()) +"','"+ pair.first +"','"+ pair.second +"','"+ CityAdmin +"','"+ SchoolAdmin +"','" +ClassAdmin+ "')"))
        {
        }
        else
        {

        }
    }



}

void DataBase::updateBoard()
{
    QMap < unsigned int, QPair<QString, QPair<QString, QString>>> list;
    QPair<QString, QPair<QString, QString>> firstLvl;
    QPair<QString, QString> secondLvl;

    if(query.exec("SELECT id_work,day, discp, homework FROM homework WHERE city ='"+CityAdmin+"'"
                  "AND school ='"+SchoolAdmin+"' AND class = '"+ClassAdmin+"'"))
    {
        while(query.next())
        {
            secondLvl.first = query.value(2).toString();
            secondLvl.second = query.value(3).toString();
            firstLvl.first = query.value(1).toString();
            firstLvl.second = secondLvl;
            list.insert(query.value(0).toUInt(), firstLvl);
            //discip.insert(query.value(1).toString(),query.value(0).toUInt());
        }
    }

    emit updateHomeWorkBoard(list);
}

void DataBase::updateTask(QString id, QString task)
{
    if(query.exec("UPDATE `homework` SET `homework` = '"+ task +"' WHERE id_work = "+ id +""))
    {

    }
}

void DataBase::deleteTask(QString id)
{
    if(query.exec("DELETE FROM homework WHERE id_work ='"+ id +"'"))
    {

    }
}

void DataBase::createTableListUser()
{
    myMapUserList.clear();

  if(query.exec("SELECT id_user,name,law FROM users "
                "WHERE city='"+CityAdmin+
                "'AND school='"+SchoolAdmin+
                "'AND class='"+ClassAdmin+
                "'AND (law ='user' OR law = 'moder')"))
  {


       while(query.next())
       {
           QPair<int,QString> userList;
           userList.first = query.value(0).toInt();
           userList.second = query.value(2).toString();
           myMapUserList.insert(query.value(1).toString(),userList);

       }

       emit  createTableListUserSignal(myMapUserList);
  }
}

void DataBase::deleteUserList(QString key)
{
    unsigned int id_user = myMapUserList[key].first;
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

           id = query.value(0).toInt();
           law = query.value(1).toString();
           accses = query.value(2).toString();

        }


        emit OpenNewWindow(id,law,accses,save);

        if(law == "user")
        {
            createTableRaiting("user");
        }
        else if(law =="admin")
        {
            createTableListUser();
            createTableDiscipline();
        }
        else if(law == "moder")
        {
            createTableRaiting("moder");
        }
        else
        {    id = 0;
             emit OpenNewWindow(id,law,accses,save);
        }
    }
    else
    {

    }
}

void DataBase::InsertStudentSlot(QString nameStudent,QString PassStudent)
{

    if(query.exec( "INSERT INTO users (id_user,city,school,class,name,law,pass) "
                   "values(default, '"+CityAdmin+"','"+SchoolAdmin+"',"
                   "'"+ClassAdmin+"','"+nameStudent+"','user','"+PassStudent+"')"))
    {
        emit insertDoneOr(true);
    }
    else
    {
        emit insertDoneOr(false);

    }
}

QString DataBase::dayToInt(QString day)
{
    if(day == "Понеділок")
        return "0";
    else if(day == "Вівторок")
        return "1";
    else if(day == "Середа")
        return "2";
    else if(day == "Четвер")
        return "3";
    else if(day == "П'ятниця")
        return "4";

}
