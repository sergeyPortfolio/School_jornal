#ifndef ADMINPANELFOREDIT_H
#define ADMINPANELFOREDIT_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>


class AdminPanelForEdit : public QWidget
{
    Q_OBJECT
public:
    explicit AdminPanelForEdit(QWidget *parent = nullptr);
    QPushButton *update;
signals:
    void deletePointSignal(QString,QString,QString,QString,QString);
    void editPointSignal(QString,QString,QString,QStringList);
    void editPointSignalOnDiscp(QString,QString,QString,QStringList);
    void deleteAllPointSignal(QString,QString);
    void deleteAllPointSignalOnDiscp(QString,QString);
    void deletePointOnDiscpSignal(QString,QString,QString,QString,QString);
    void updatePointSignal(QString,QString,QString);
    void updatePointSignalonDiscp(QString,QString,QString);
public slots:
    void createTable(QMap<QString,QMultiMap<int,QPair<QString,int>>>,QString Flag);
    void deletePointSlot();
    void updatePoint();
    void idUserSlot(QString);
    void idDiscpSlot(QString);
    void editPointSlot();
    void deleteAllPointSlot();

private:
    QTableWidget *tabl;
    QComboBox *globalLocal;
    QLabel *label;
    QPushButton *insertPoint;
    QLineEdit *windowForPoint;
    QVBoxLayout *CentralLayout;
    QHBoxLayout *BottomLayout;
    QPushButton *deletePoint;
    QPushButton *deleteALlPoint;
    QMessageBox *message;
    QString idName;
    QString Flag;

};

#endif // ADMINPANELFOREDIT_H
