#ifndef FACTORY_H
#define FACTORY_H

#include "verifregex.h"
#include "nombre.h"
#include "pile.h"


// ------------------------------------------------------ CLASS FACTORYN ------------------------------------------------------------------------

class FactoryN
{
    FactoryN();
    ~FactoryN();
    FactoryN(const FactoryN& fn);
    FactoryN& operator=(const FactoryN& fn);

    struct Handler {
        FactoryN* instance;
        Handler(): instance(nullptr){}
        ~Handler(){delete instance;}
    };
    static Handler handler;

public:
    static FactoryN& getInstance();
    static void libereInstance();

    Nombre* ProductN(QString s);
};


// ------------------------------------------------------ CLASS FACTORYE ------------------------------------------------------------------------

class FactoryE
{

    FactoryE();
    ~FactoryE();
    FactoryE(const FactoryE& fe);
    FactoryE& operator=(const FactoryE& fe);

    struct Handler {
        FactoryE* instance;
        Handler(): instance(nullptr){}
        ~Handler(){delete instance;}
    };
    static Handler handler;

public:
    static FactoryE& getInstance();
    static void libereInstance();

    Expression* ProductE(QString s);
};

// ------------------------------------------------------ CLASS FACTORYP ------------------------------------------------------------------------


class FactoryP
{
    FactoryP();
    ~FactoryP();
    FactoryP(const FactoryN& fp);
    FactoryP& operator=(const FactoryP& fp);

    struct Handler {
        FactoryP* instance;
        Handler(): instance(nullptr){}
        ~Handler(){delete instance;}
    };
    static Handler handler;
public:
    static FactoryP& getInstance();
    static void libereInstance();

    Programme* ProductP(QString s);
};



// ------------------------------------------------------ CLASS FACTORYG ------------------------------------------------------------------------

// implementation du design pattern adapter

class FactoryG // classe a instancier dans le controleur
{
    FactoryN& fN;
    FactoryE& fE;
    FactoryP& fP;
    VerifRegex& vrx;


    FactoryG();

    ~FactoryG();
    FactoryG(const FactoryG& am);
    FactoryG& operator=(const FactoryG& am);

    // singleton voir TD6 ou 5...
    struct Handler {
        FactoryG* instance;
        Handler(): instance(nullptr) {}
        ~Handler(){delete instance;}
    };
    static Handler handler;

public:

    static FactoryG& getInstance();
    static void libereInstance();


    ObjectPile* Product(QString s);
};






#endif // FACTORY_H
