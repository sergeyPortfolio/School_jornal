#include "insertdisciplinewidget.h"
InsertDisciplineWidget::InsertDisciplineWidget(QWidget *parent) : QWidget(parent)
{
    tabl = new QTableWidget();
    label = new QLabel("Введіть назву дисципліни",this);
    lineEdit = new QLineEdit(this);
    vLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout(this);
    edit = new QPushButton("Додати",this);
    deleteDics = new QPushButton("Видалити",this);

    vLayout->addWidget(tabl);
    vLayout->addLayout(hLayout);
    hLayout->addWidget(label);
    hLayout->addWidget(lineEdit);
    hLayout->addWidget(edit);
    hLayout->addWidget(deleteDics);
    connect(this->edit,SIGNAL(clicked()),this,SLOT(editDiscipline()));
    connect(this->deleteDics,SIGNAL(clicked()),this,SLOT(deleteDiscpline()));
}

void InsertDisciplineWidget::createTableDiscipline(QMap<QString,unsigned int> list)
{
    tabl->clear();
    tabl->setRowCount(0);
    tabl->setColumnCount(1);
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText("Назва Дисциплін");
    tabl->setHorizontalHeaderItem(0,item);
    int row =0;
    int number = 1;
    for (QMap<QString,unsigned int>::iterator it=list.begin(); it!=list.end(); ++it)
    {
        QTableWidgetItem *itemNumber = new QTableWidgetItem;
        itemNumber->setText(QString::number(number));
        QTableWidgetItem *itemDiscipline = new QTableWidgetItem;
        itemDiscipline->setText(it.key());

        row = tabl->rowCount()+1;
        tabl->setRowCount(row);
        tabl->setVerticalHeaderItem(row-1,itemNumber);
        tabl->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabl->setItem(row-1,0,itemDiscipline);
        number++;
    }
    tabl->show();
}

void InsertDisciplineWidget::editDiscipline()
{
    if(!lineEdit->text().isEmpty())
    {
        emit editDisciplineSignal(lineEdit->text());
        lineEdit->setText(NULL);
    }
    else
    {
        message = new QMessageBox();
        message->setText("Заповніть поле");
        message->show();
    }
}

void InsertDisciplineWidget::deleteDiscpline()
{
    message = new QMessageBox();
    auto index = tabl->selectedItems();
    if(index.empty())
    {
        message->setText("Натисніть на назву дисципліни");
        message->show();
    }
    else
    {
       QString nameStudent = index[0]->text();
       emit deleteDisciplineSignal(nameStudent);

    }
}
