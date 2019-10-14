#ifndef HOMEWORKBOARD_H
#define HOMEWORKBOARD_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

class HomeWorkBoard : public QWidget
{
    Q_OBJECT
public:
    explicit HomeWorkBoard(QWidget *parent = nullptr);

    void setRures(const bool flag);
signals:
    void openBoard();
    void sendHomeWork(QMultiMap<QString, QPair<QString, QString>>);
    void addTaskToBoard();
    void deleteTask(QString);
    void updateTask(QString, QString);

public slots:
    void createTableDisciplineForHomeworkSlot(QMap<QString,unsigned int>, QString, QString, QString);
    void slotEdit(QTableWidgetItem *item);
    void saveTaskSlot();
    void updateHomeWorkBoard(QMap < unsigned int, QPair<QString, QPair<QString, QString>>>);

private:
    QTableWidget *table; //понедельник
    QHBoxLayout *generalLayout;
    QVBoxLayout *firstLayout;
    QVBoxLayout *secondLayout;
    QMessageBox *err;
    QMap<unsigned int, QPair<QString, QPair<QString, QString> > > listTask;
    QPushButton *saveTask;

    QVector<QPair<int,int>> coord;
    QString m_school;
    QString m_class;
    QString m_city;
    QMap <QString, unsigned int> m_list;
};

#endif // HOMEWORKBOARD_H
