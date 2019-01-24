#ifndef TOPINTERFACE_H
#define TOPINTERFACE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class TopInterface : public QWidget
{
    Q_OBJECT
public:
    explicit TopInterface(QWidget *parent = nullptr);
    QPushButton *LogOutButtonTop;

private:
    QHBoxLayout *Layout;
    QLabel *CityLabelTop;
    QLabel *SchoolLabelTop;
    QLabel *ClassLabelTop;
    QLabel *FirstNameLabelTop;

signals:


public slots:
    void author(QString Ucity,QString Uscholl,QString Uclass,QString Uname);

};

#endif // TOPINTERFACE_H
