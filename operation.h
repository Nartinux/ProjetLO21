#ifndef OPERATION_H
#define OPERATION_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "nombre.h"
#include "pile.h"
#include "verifregex.h"
#include "factory.h"





//------------------------------------------- CLASS OPERATEURAVANCE ---------------------------------------------------------------------------------------------------


class OperateurAvance // abstraite elle permet de donner acces a une pile pour toutes ses classes dérivées
{
protected: 
    Pile& expAff;	// FAUT QUE CA SOIT LA MEME PILE -> singleton ou bien faire attention lors de la construction !
	VerifRegex& vrx;
    AtomeManager& atm;
    FactoryN& fN;
public:
    OperateurAvance(Pile& p): expAff(p), vrx(VerifRegex::getInstance()), atm(AtomeManager::getInstance()), fN(FactoryN::getInstance()) {}
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



// ------------------------------------------------------ CLASS FORGET ------------------------------------------------------------------------


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

// ------------------------------------------------------ CLASS DIV ------------------------------------------------------------------------


class Diveucli : public OperateurAvance
{
public:
    Diveucli(Pile& p): OperateurAvance(p) {}
    ~Diveucli();
    void operation();
};

// ------------------------------------------------------ CLASS NUM ------------------------------------------------------------------------


class Numerateur : public OperateurAvance
{
public:
    Numerateur(Pile& p): OperateurAvance(p) {}
    ~Numerateur();
    void operation();
};

// ------------------------------------------------------ CLASS DEN ------------------------------------------------------------------------


class Denominateur : public OperateurAvance
{
public:
    Denominateur(Pile& p): OperateurAvance(p) {}
    ~Denominateur();
    void operation();
};

// ------------------------------------------------------ CLASS $ ------------------------------------------------------------------------


class Operateur$ : public OperateurAvance
{
public:
    Operateur$(Pile& p): OperateurAvance(p) {}
    ~Operateur$();
    void operation();
};

// ------------------------------------------------------ CLASS RE ------------------------------------------------------------------------


class PartieReelle : public OperateurAvance
{
public:
    PartieReelle(Pile& p): OperateurAvance(p) {}
    ~PartieReelle();
    void operation();
};

// ------------------------------------------------------ CLASS IM ------------------------------------------------------------------------


class PartieIm : public OperateurAvance
{
public:
    PartieIm(Pile& p): OperateurAvance(p) {}
    ~PartieIm();
    void operation();
};

// ------------------------------------------------------ CLASS = ------------------------------------------------------------------------


class Egal : public OperateurAvance
{
public:
    Egal(Pile& p): OperateurAvance(p) {}
    ~Egal();
    void operation();
};

// ------------------------------------------------------ CLASS != ------------------------------------------------------------------------


class Different : public OperateurAvance
{
public:
    Different(Pile& p): OperateurAvance(p) {}
    ~Different();
    void operation();
};

// ------------------------------------------------------ CLASS >= ------------------------------------------------------------------------


class SupOuEgal : public OperateurAvance
{
public:
    SupOuEgal(Pile& p): OperateurAvance(p) {}
    ~SupOuEgal();
    void operation();
};

// ------------------------------------------------------ CLASS =< ------------------------------------------------------------------------


class InfOuEgal : public OperateurAvance
{
public:
    InfOuEgal(Pile& p): OperateurAvance(p) {}
    ~InfOuEgal();
    void operation();
};

// ------------------------------------------------------ CLASS > ------------------------------------------------------------------------


class Sup : public OperateurAvance
{
public:
    Sup(Pile& p): OperateurAvance(p) {}
    ~Sup();
    void operation();
};

// ------------------------------------------------------ CLASS < ------------------------------------------------------------------------


class Inf : public OperateurAvance
{
public:
    Inf(Pile& p): OperateurAvance(p) {}
    ~Inf();
    void operation();
};

// ------------------------------------------------------ CLASS AND ------------------------------------------------------------------------


class And : public OperateurAvance
{
public:
    And(Pile& p): OperateurAvance(p) {}
    ~And();
    void operation();
};


// ------------------------------------------------------ CLASS Or ------------------------------------------------------------------------


class Or : public OperateurAvance
{
public:
    Or(Pile& p): OperateurAvance(p) {}
    ~Or();
    void operation();
};

// ------------------------------------------------------ CLASS NOT ------------------------------------------------------------------------


class Not : public OperateurAvance
{
public:
    Not(Pile& p): OperateurAvance(p) {}
    ~Not();
    void operation();
};

// ------------------------------------------------------ CLASS POW ------------------------------------------------------------------------


class Pow : public OperateurAvance
{
public:
    Pow(Pile& p): OperateurAvance(p) {}
    ~Pow();
    void operation();
};

// ------------------------------------------------------ CLASS DUP ------------------------------------------------------------------------


class Dup : public OperateurAvance
{
public:
    Dup(Pile& p): OperateurAvance(p) {}
    ~Dup();
    void operation();
};


// ------------------------------------------------------ CLASS DROP ------------------------------------------------------------------------


class Drop : public OperateurAvance
{
public:
    Drop(Pile& p): OperateurAvance(p) {}
    ~Drop();
    void operation();
};

// ------------------------------------------------------ CLASS SWAP ------------------------------------------------------------------------


class Swap : public OperateurAvance
{
public:
    Swap(Pile& p): OperateurAvance(p) {}
    ~Swap();
    void operation();
};

// ------------------------------------------------------ CLASS CLEAR ------------------------------------------------------------------------


class Clear : public OperateurAvance
{
public:
    Clear(Pile& p): OperateurAvance(p) {}
    ~Clear();
    void operation();
};


// ------------------------------------------------------ CLASS UNDO ------------------------------------------------------------------------


class Undo : public OperateurAvance
{
    PileMemento& pm;
public:
    Undo(Pile& p): OperateurAvance(p), pm(PileMemento::getInstance()) {}
    ~Undo();
    void operation();
};

// ------------------------------------------------------ CLASS NEG ------------------------------------------------------------------------


class Neg : public OperateurAvance
{
    PileMemento& pm;
public:
    Neg(Pile& p): OperateurAvance(p), pm(PileMemento::getInstance()) {}
    ~Neg();
    void operation();
};




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
