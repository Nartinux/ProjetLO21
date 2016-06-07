#ifndef OPERATION_H
#define OPERATION_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "nombre.h"
#include "pile.h"
#include "verifregex.h"


// BUT FAIRE EVAL POUR LES EXPRESSIONS



//------------------------------------------- CLASS OPERATEURAVANCE ---------------------------------------------------------------------------------------------------


class OperateurAvance // abstraite elle permet de donner acces a une pile pour toutes ses classes dérivées
{
protected: 
    Pile& expAff;	// FAUT QUE CA SOIT LA MEME PILE -> singleton ou bien faire attention lors de la construction !
	VerifRegex& vrx;
    AtomeManager& atm;
public:
    OperateurAvance(Pile& p): expAff(p), vrx(VerifRegex::getInstance()), atm(AtomeManager::getInstance()) {}
	virtual ~OperateurAvance();
    virtual void operation()=0;	// cette methode prends 0 args elle les prends direct dans la pile
    Pile& getPile(){return expAff;}
    VerifRegex& getVrx(){return vrx;}
    AtomeManager& getAtm(){return atm;}
};



//------------------------------------------- CLASS EVAL ---------------------------------------------------------------------------------------------------

class Eval : public OperateurAvance
{
public:
    Eval(Pile& p): OperateurAvance(p) {}
	~Eval();
	void operation();

};


//------------------------------------------- CLASS STO ---------------------------------------------------------------------------------------------------

class Sto : public OperateurAvance
{
public:
    Sto(Pile& p): OperateurAvance(p) {}
	~Sto();
	void operation();
};


class Forget : public OperateurAvance
{
public:
    Forget(Pile& p): OperateurAvance(p) {}
	~Forget();
	void operation();
};



// ------------------------------------------------------ CLASS MODULO ------------------------------------------------------------------------


class Modulo : public OperateurAvance
{
public:
    Modulo(Pile& p): OperateurAvance(p) {}
    ~Modulo();
    void operation();
};


Entier& modulo(Entier& a,Entier& b);
Entier& diveucli(Entier& a,Entier& b);




// ------------------------------------------------------ CLASS FACTORYOPERATEUR ------------------------------------------------------------------------

class FactoryOperateur // classe a instancier dans le controleur
{
    VerifRegex& vrx;
    Pile& pil;

    FactoryOperateur(Pile& p): pil(p), vrx(VerifRegex::getInstance()){}

    ~FactoryOperateur();
    FactoryOperateur(const FactoryOperateur& fop);
    FactoryOperateur& operator=(const FactoryOperateur& fop);

    // singleton voir TD6 ou 5...
    struct Handler {
        FactoryOperateur* instance;
        Handler(): instance(nullptr) {}
        ~Handler(){delete instance;}
    };
    static Handler handler;

public:

    static FactoryOperateur* getInstance(Pile& p);
    static void libereInstance();
    OperateurAvance* ProductOP(QString s);
};



#endif // OPERATION_H
