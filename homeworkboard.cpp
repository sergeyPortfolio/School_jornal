#include "homeworkboard.h"

HomeWorkBoard::HomeWorkBoard(QWidget *parent) : QWidget(parent)
{
    table = new QTableWidget(this);
    generalLayout = new QHBoxLayout(this);
    firstLayout = new QVBoxLayout(this);
    secondLayout = new QVBoxLayout(this);
    err = new QMessageBox();



    generalLayout->addLayout(firstLayout);
    generalLayout->addLayout(secondLayout);

    firstLayout->addWidget(table);


    QStringList horizontalHeader;

    table->setColumnCount(5);
    horizontalHeader << "Понеділок" << "Вівторок" << "Середа" << "Четвер" << "П'ятниця";
    table->setHorizontalHeaderLabels(horizontalHeader);
}

void HomeWorkBoard::setRures(const bool flagAcsess)
{
    if(flagAcsess)
    {
        saveTask = new QPushButton("Зберегти",this);
        firstLayout->addWidget(saveTask);

        connect(this->table,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotEdit(QTableWidgetItem*)));
        connect(this->saveTask, SIGNAL(clicked()), this, SLOT(saveTaskSlot()));

    }
    if(!flagAcsess)
    {
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void HomeWorkBoard::createTableDisciplineForHomeworkSlot(QMap<QString, unsigned int> list, QString city, QString school, QString clas)
{
    m_list = list;
    m_city = city;
    m_school = school;
    m_class = clas;
    QStringList discip;
    for(auto it = m_list.begin(); it != m_list.end(); it++)
    {
        discip << it.key();
    }
    table->setRowCount(discip.size());
    table->setVerticalHeaderLabels(discip);

    emit addTaskToBoard();

    emit openBoard();

}

void HomeWorkBoard::slotEdit(QTableWidgetItem *item)
{
    //QString str = "asdf DELETE jlblu";

    if(item->text().contains("delete",Qt::CaseInsensitive) || item->text().contains("insert",Qt::CaseInsensitive) )
    {
       err->setText("Не вірний формат");
       err->show();
       item->setText("");
    }
    else
    {
        if( !item->data(Qt::UserRole).isNull() && !item->text().isEmpty() )
        {

            updateTask(item->data(Qt::UserRole).toString(), item->text());
        }
        else if( !item->data(Qt::UserRole).isNull() && item->text().isEmpty() )
        {

            emit deleteTask(item->data(Qt::UserRole).toString());

        }
        else
        {

            QPair<int,int> cor;
            cor.first = item->column();
            cor.second = item->row();
            coord.append(cor);
        }
    }


}

void HomeWorkBoard::saveTaskSlot()
{

    QPair<QString, QString> task;
    QMultiMap<QString, QPair<QString, QString>> listTask;

    for(int i = 0; i < coord.size(); i++)
    {
         QPair<int,int> cor;
         cor = coord[i];

         switch (cor.first)
         {

            case 0: task.first = table->verticalHeaderItem(cor.second)->text();
                    task.second = table->item(cor.second, cor.first)->text();
                    listTask.insert( "Понеділок", task ); break;

            case 1: task.first = table->verticalHeaderItem(cor.second)->text();
                    task.second = table->item(cor.second, cor.first)->text();
                    listTask.insert( "Вівторок", task ); break;

            case 2: task.first = table->verticalHeaderItem(cor.second)->text();
                    task.second = table->item(cor.second, cor.first)->text();
                    listTask.insert( "Середа", task ); break;

            case 3: task.first = table->verticalHeaderItem(cor.second)->text();
                    task.second = table->item(cor.second, cor.first)->text();
                    listTask.insert( "Четвер", task ); break;

            case 4: task.first = table->verticalHeaderItem(cor.second)->text();
                    task.second = table->item(cor.second, cor.first)->text();
                    listTask.insert( "П'ятниця", task ); break;
         }
    }
    coord.clear();
    emit sendHomeWork(listTask);
}

void HomeWorkBoard::updateHomeWorkBoard(QMap<unsigned int, QPair<QString, QPair<QString, QString> > > list)
{
    listTask.clear();
    listTask = list;
    QPair<QString, QPair<QString, QString>> firstLvl;
    QPair<QString, QString> secondlLvl;

    for(auto it = list.begin(); it != list.end(); it++)
    {
        firstLvl = it.value();
        for(int i =0; i < table->rowCount(); i++)
        {
            secondlLvl = firstLvl.second;
            if(table->verticalHeaderItem(i)->text() == secondlLvl.first )
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::UserRole, it.key());
                item->setText(secondlLvl.second);
                table->setItem(i, firstLvl.first.toInt(), item);
            }
        }
    }



}


