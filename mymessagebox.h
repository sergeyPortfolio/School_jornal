#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QMessageBox>

class MyMessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit MyMessageBox(QWidget *parent = nullptr);
    QPushButton *Cancel;

signals:
        void NameAndPassSignal(QString name, QString Pass);
        void ResetTableUser();
public slots:
        void NameAndPassSlot();
        void DoneOrNot(bool b);
private:
    QPushButton *Ok;

    QLineEdit *name;
    QLineEdit *pass;
    QVBoxLayout *CentralLayout;
    QHBoxLayout *TopLayout;
    QHBoxLayout *BottomLayout;
    QLabel *nameLabel;
    QLabel *passLabel;
    QMessageBox *messegeDone;
    QMessageBox *messegeNotDone;
    QMessageBox *messegeNotFill;
};

#endif // MYMESSAGEBOX_H
