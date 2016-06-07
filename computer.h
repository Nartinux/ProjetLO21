#ifndef COMPUTER_H
#define COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "factory.h"
#include "operation.h"


using namespace std;






// ------------------------------------------------------ CLASS CONTROLEUR -----------------------------------------------------------

class Controleur
{
    FactoryOperateur& factoOP;
    FactoryG& factoG;
    FactoryE& factoE;
    FactoryN& factoN;
    FactoryP& factoP;
    Pile& expAff;
    VerifRegex& vrx;
public:
    Controleur(Pile& p, VerifRegex& v,FactoryOperateur& fop, FactoryG& fg, FactoryP& fp, FactoryE& fe, FactoryN& fn):
    expAff(p), vrx(v), factoOP(fop), factoG(fg), factoP(fp), factoE(fe), factoN(fn) {}

    void sentCommande( QString& c);
};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);



#endif // COMPUTER_H
