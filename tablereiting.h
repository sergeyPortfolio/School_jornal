#ifndef TABLEREITING_H
#define TABLEREITING_H

#include <QWidget>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPushButton>
class tablereiting : public QWidget
{
    Q_OBJECT
public:
    explicit tablereiting(QWidget *parent = nullptr);

signals:

public slots:
    void createTable(QSqlQuery);
private:
    QTableView reiting;
    QPushButton *but;
};

#endif // TABLEREITING_H
