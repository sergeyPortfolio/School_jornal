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
    QPushButton *cancel;
signals:
    void deletePointSignal(QString,QString,QString,QString);
    void editPointSignal(QString,QString,QString,QString);
    void deleteAllPointSignal(QString,QString);
public slots:
    void createTable(QMap<QString,QMultiMap<QString,int>> map);
    void deletePointSlot();
    void idUserSlot(QString);
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

};

#endif // ADMINPANELFOREDIT_H
