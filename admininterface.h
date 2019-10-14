#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include "mymessagebox.h"
#include "adminpanelforedit.h"
#include "insertdisciplinewidget.h"
#include "homeworkboard.h"
#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QMessageBox>


class AdminInterface : public QWidget
{
    Q_OBJECT
public:
    explicit AdminInterface(QWidget *parent = nullptr);
    QPushButton *EditPoint;
    QPushButton *DeleteStudentButton;
    QPushButton *InsertStudentButton;
    QPushButton *InsertDiscipline;
    QPushButton *DeleteDiscipline;
    QPushButton *UseUser;
    QPushButton *EditHomework;
    MyMessageBox *message;
    AdminPanelForEdit *panelForEdit;
    InsertDisciplineWidget *panelForEditDisc;
    HomeWorkBoard *homeWorkBoard;

signals:
    void deleteUserSignal(QString);
    void repeatUserList();
    void createTablePoint(QString);
    void createTablePointOnDiscp(QString);
    void idDiscp(QString);
    void createTableDiscipline();
    void idUser(QString);
    void deleteDisciplineSignal(QString);
    void updateUserLawSignal(QString);

    void createHomeWorkBoard();


public slots:
    void updateUserLaw();
    void createUserList(QMap<QString,QPair<unsigned int,QString>> UserListMap);
    void openEditWindowForInsert();
    void closeEditWindowForInsert();
    void deleteUser();
    void deleteUserDone(bool);
    void editPointUser();
    void closeAdminPanelForEdit();
    void insertDiscipline();
    void createTableDisciplineSlot(QMap<QString,unsigned int> list);
    void deleteDiscplineSlot();
    void resetItemTabl(QTableWidgetItem *Item);
    void openHomeWorkWindow();
    void closeHomeWorkWindow();


private:
    QHBoxLayout *CentralLayout;
    QVBoxLayout *RightLayout;
    QTableWidget *tabl;
    QTableWidget *tablDiscipline;
    QMessageBox *DeleteOk;
    QMessageBox *CheckUncheck;
    QMessageBox *messageDeliteDescipline;
    QMap<QString,QPair<unsigned int,QString>> List;

};

#endif // ADMININTERFACE_H
