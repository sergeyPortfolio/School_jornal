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
#include <insertdisciplinewidget.h>

class AdminInterface : public QWidget
{
    Q_OBJECT
public:
    explicit AdminInterface(QWidget *parent = nullptr);
    QPushButton *EditPoint;
    QPushButton *DeleteStudentButton;
    QPushButton *InsertStudentButton;
    QPushButton *InsertDiscipline;
    MyMessageBox *message;
    AdminPanelForEdit *panelForEdit;
    InsertDisciplineWidget *panelForEditDisc;

signals:
    void deleteUserSignal(QString);
    void repeatUserList();
    void createTablePoint(QString);
    void createTableDiscipline();
    void idUser(QString);
public slots:
    void createUserList(QMap<QString,unsigned int> UserListMap);
    void openEditWindowForInsert();
    void closeEditWindowForInsert();
    void deleteUser();
    void deleteUserDone(bool);
    void editPointUser();
    void closeAdminPanelForEdit();
    void insertDiscipline();
private:
    QHBoxLayout *CentralLayout;
    QVBoxLayout *RightLayout;
    QTableWidget *tabl;
    QMessageBox *DeleteOk;
    QMessageBox *CheckUncheck;
    QMap<QString,unsigned int> List;

};

#endif // ADMININTERFACE_H
