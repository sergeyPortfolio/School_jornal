#ifndef INSERTDISCIPLINEWIDGET_H
#define INSERTDISCIPLINEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QMessageBox>

class InsertDisciplineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InsertDisciplineWidget(QWidget *parent = nullptr);

signals:
    void editDisciplineSignal(QString);
    void deleteDisciplineSignal(QString);
public slots:
    void createTableDiscipline(QMap<QString,unsigned int>);
    void editDiscipline();
    void deleteDiscpline();
private:
    QTableWidget *tabl;
    QLabel *label;
    QLineEdit *lineEdit;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QPushButton *edit;
    QMessageBox *message;
    QPushButton *deleteDics;

};


#endif // INSERTDISCIPLINEWIDGET_H
