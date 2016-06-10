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


//----------------------------------------------------------- CLASS FENVAR --------------------------------------------------------------------------------------

class FenVar : public QWidget
{
    Q_OBJECT
    AtomeManager& atm;
    QTableWidget* tabvar;
    QVBoxLayout* corps;
    QPushButton* refresh;
    QVBoxLayout* verti;
    QHBoxLayout* hori1;
    QHBoxLayout* hori2;
    
    FenVar();
    ~FenVar();
    FenVar(const FenVar& fv);
    FenVar& operator=(const FenVar& fv);

    struct Handler {
        FenVar* instance;
        Handler(): instance(nullptr){}
        ~Handler(){delete instance;}
    };
    static Handler handler;

public:

    static FenVar& getInstance();
    static void libereInstance();
    
public slots:
    void afficherAtm();
};


//----------------------------------------------------------- CLASS QLineEditable --------------------------------------------------------------------------------------


class QLineEditable : public QLineEdit      //QlineEditable est un QlineEdit avec un slot "addtext" en plus pour permettre au pavé virtuel d'écrire dedans
{
    Q_OBJECT
public:
    QLineEditable(QWidget *parent = Q_NULLPTR) : QLineEdit(parent){}
public slots:
    void addText(const QString& s);
};


//----------------------------------------------------------- CLASS QComputer --------------------------------------------------------------------------------------

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
    QPushButton* butDivEnt;
    QPushButton* butMod;
    QPushButton* butPow;
    QPushButton* butNeg;
    QPushButton* butSin;
    QPushButton* butCos;
    QPushButton* butTan;
    QPushButton* butNum;
    QPushButton* butDen;
    QPushButton* but$;
    QPushButton* butRe;
    QPushButton* butIm;
    QPushButton* submit;
    QPushButton* vueatm;    // vue atm
    QHBoxLayout* hori1;
    QHBoxLayout* hori2;
    QHBoxLayout* hori3;
    QHBoxLayout* hori4;
    QHBoxLayout* hori5;
    QHBoxLayout* hori6;
    QHBoxLayout* hori7;
    QHBoxLayout* hori8;     // enter + vue atm
    QVBoxLayout* verti1;
    QVBoxLayout* verti2;
    QVBoxLayout* verti3;
    QVBoxLayout* verti4;    // ...
    QHBoxLayout* pave;
    QSignalMapper* mapper; //collecte des signaux sans arguments et les redistribue avec argument
    Pile* pile;
    FactoryG* factg;
    FactoryP* factp;
    FactoryE* facte;
    FactoryN* factn;
    VerifRegex* vrx;
    FactoryOperateur* factoop;
    Controleur* controleur;

public:
    explicit QComputer(QWidget *parent = 0);
public slots:
    void envoiCmd(QString s);
    void refresh();
    void getNextCommande();
    void ouvrirFenVar();
};


#endif // QCOMPUTER_H
