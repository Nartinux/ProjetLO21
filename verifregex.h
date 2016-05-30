#ifndef VERIFREGEX_H
#define VERIFREGEX_H
#include "objectpile.h"



// ------------------------------------------------------ CLASS VERIFREGEX ------------------------------------------------------------------------

class VerifRegex    // classe non singleton, et finale ? DOIT AVOIR UNE VUE SUR ATOMEMANAGER
{
    AtomeManager& Atm;
public:
    VerifRegex(): Atm(AtomeManager::getInstance()) {}

    AtomeManager& getAtm(){return Atm;}

    bool verifEntier(QString& s);
    bool verifReel(QString& s);
    bool verifRationnel(QString& s);
    bool verifComplexe(QString& s);
    bool verifNombre(QString& s);

    bool verifOperateurSimple(const QChar &s);  // verifie qu'on a des operateurs de type: + - * /
    bool verifOperateurSimple(QString&s);
    bool verifOperateurAvance(QString& s);  // verifie les operateurs definis pas une chaine de char (et des parenthèses avec des args dedans... separés par des virgules !)

    bool verifAtome(QString& s);    // verifie que le string est un candidat pour devenir un atome
    bool verifAtomeExistant(QString& s);    // verifie que c'est un atome déjà defini

    bool verifExpression(QString& s);
    bool verifProgramme(QString& s);

};





#endif // VERIFREGEX_H
