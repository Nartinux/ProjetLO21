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
#include <QSignalMapper>
#include "computer.h"



class QLineEditable : public QLineEdit{     //QlineEditable est un QlineEdit avec un slot "addtext" en plus pour permettre au pavé virtuel d'écrire dedans
    Q_OBJECT
public:
    QLineEditable(QWidget *parent = Q_NULLPTR) : QLineEdit(parent){}
public slots:
    void addText(const QString& s);
};

class QComputer : public QWidget
{
    Q_OBJECT
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEditable* commande;
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
    QPushButton* but0;
    QPushButton* butMult;
    QPushButton* butAdd;
    QPushButton* butDiv;
    QPushButton* butSub;
    QPushButton* submit;
    QHBoxLayout* hori1;
    QHBoxLayout* hori2;
    QHBoxLayout* hori3;
    QHBoxLayout* hori4;
    QVBoxLayout* verti1;
    QVBoxLayout* verti2;
    QHBoxLayout* pave;
    QSignalMapper* mapper; //collecte des signaux sans arguments et les redistribue avec argument
    Pile* pile;
    FactoryG* factg;
    FactoryA* facta;
    FactoryP* factp;
    FactoryE* facte;
    FactoryN* factn;
    VerifRegex* vrx;
    Controleur* controleur;

public:
    explicit QComputer(QWidget *parent = 0);
public slots:
    void envoiCmd(QString& s);
    void refresh();
    void getNextCommande();
};


#endif // QCOMPUTER_H
