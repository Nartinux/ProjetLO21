#ifndef QCOMPUTER_H
#define QCOMPUTER_H



#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>
#include "computer.h"


class QComputer : public QWidget
{
    Q_OBJECT
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* couche;
    QPushButton* but1;
    QPushButton* but2;
    QPushButton* but3;
    QPushButton* but4;
    QPushButton* but5;
    QPushButton* but6;
    QPushButton* but7;
    QPushButton* but8;
    QPushButton* but9;
    QHBoxLayout* hori1;
    QHBoxLayout* hori2;
    QHBoxLayout* hori3;
    Pile* pile;
    Controleur* controleur;

public:
    explicit QComputer(QWidget *parent = 0);
public slots:
    void refresh();
    void getNextCommande();
};


#endif // QCOMPUTER_H
