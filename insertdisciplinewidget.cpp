#include "insertdisciplinewidget.h"

InsertDisciplineWidget::InsertDisciplineWidget(QWidget *parent) : QWidget(parent)
{
    label = new QLabel("Введіть назву дисципліни",this);
    lineEdit = new QLineEdit(this);
    vLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout(this);
    edit = new QPushButton("Додати",this);

    vLayout->addLayout(hLayout);
    hLayout->addWidget(label);
    hLayout->addWidget(lineEdit);
    hLayout->addWidget(edit);
    connect(this->edit,SIGNAL(clicked()),this,SLOT(editDiscipline()));
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


