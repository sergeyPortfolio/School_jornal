#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <mymessagebox.h>
#include <adminpanelforedit.h>
#include <QMessageBox>

class AdminInterface : public QWidget
{
    Q_OBJECT
public:
    explicit AdminInterface(QWidget *parent = nullptr);
    QPushButton *EditPoint;
    QPushButton *DeleteStudentButton;
    QPushButton *InsertStudentButton;
    MyMessageBox *message;
    AdminPanelForEdit *panelForEdit;

signals:
    void deleteUserSignal(QString);
    void repeatUserList();
    void createTablePoint(QString);
public slots:
    void createUserList(QMap<QString,unsigned int> UserListMap);
    void openEditWindowForInsert();
    void closeEditWindowForInsert();
    void deleteUser();
    void deleteUserDone(bool);
    void editPointUser();
    void closeAdminPanelForEdit();
private:
    QHBoxLayout *CentralLayout;
    QVBoxLayout *RightLayout;
    QTableWidget *tabl;
    QMessageBox *DeleteOk;
    QMessageBox *CheckUncheck;

};

#endif // ADMININTERFACE_H
