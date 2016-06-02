#ifndef COMPUTER_H
#define COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "factory.h"
#include "pile.h"
#include "operation.h"


using namespace std;






// ------------------------------------------------------ CLASS CONTROLEUR -----------------------------------------------------------

class Controleur
{
    FactoryG& factoG;
    FactoryA& factoA;
    FactoryE& factoE;
    FactoryN& factoN;
    FactoryP& factoP;
    Pile& expAff;
    VerifRegex& vrx;
public:
    Controleur(Pile& p, VerifRegex& v, FactoryG& fg,FactoryA& fa, FactoryP& fp, FactoryE& fe, FactoryN& fn):
    expAff(p), vrx(v), factoG(fg), factoA(fa), factoP(fp), factoE(fe), factoN(fn) {}

    void sentCommande(/*const*/ QString& c);
};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);



#endif // COMPUTER_H
