#ifndef AUTHORFORM_H
#define AUTHORFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>


class authorForm : public QWidget
{
    Q_OBJECT
private:

    QString ForReadcity;
    QString ForReadschool;
    QString ForReadclass;
    QString ForReadname;
    QString ForReadpass;

   QColor m_backGroundColor;
   QLineEdit *CityLineEdit;
   QLineEdit *SchoolLineEdit;
   QLineEdit *ClassLineEdit;
   QLineEdit *FirstNameLineEdit;
   QLineEdit *PassLineEdit;


   QCheckBox *SaveDataCheckBox;

   QVBoxLayout *CentralVLayout;
   QVBoxLayout *LabelVLayout;
   QVBoxLayout *LineEditVLayout;
   QHBoxLayout *DataAutorHLayout;
   QHBoxLayout *EnterHLayout;


   QLabel *CityLabel;
   QLabel *SchoolLabel;
   QLabel *ClassLabel;
   QLabel *FirstNameLabel;
   QLabel *PassLabel;
public:
    explicit authorForm(QWidget *parent = nullptr);
   QPushButton *EnterButton;

signals:
   void MyAuthorization(QString city,QString school, QString clas,QString firstn,QString pass);
   void TextForTopInterf(QString city,QString school, QString clas,QString firstn);
   void TestDataSave(QString city,QString school, QString clas,QString firstn,QString pass);
   void clicked();
public slots:
   void MyClikc();
};

#endif // AUTHORFORM_H
