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

class AdminPanelForEdit : public QWidget
{
    Q_OBJECT
public:
    explicit AdminPanelForEdit(QWidget *parent = nullptr);
    QPushButton *cancel;
signals:

public slots:
    void createTable(QMap<QString,QMultiMap<QString,int>> map);

private:
    QTableWidget *tabl;
    QComboBox *globalLocal;
    QLabel *label;
    QPushButton *insertPoint;

    QLineEdit *windowForPoint;
    QVBoxLayout *CentralLayout;
    QHBoxLayout *BottomLayout;
    QPushButton *deletePoint;

};

#endif // ADMINPANELFOREDIT_H
