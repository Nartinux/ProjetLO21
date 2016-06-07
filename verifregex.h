#ifndef VERIFREGEX_H
#define VERIFREGEX_H
#include "objectpile.h"



// ------------------------------------------------------ CLASS VERIFREGEX ------------------------------------------------------------------------

class VerifRegex    // classe singleton, et finale ? DOIT AVOIR UNE VUE SUR ATOMEMANAGER
{
    AtomeManager& Atm;

    VerifRegex(): Atm(AtomeManager::getInstance()) {}
    ~VerifRegex();
    VerifRegex(const VerifRegex& vrx);
    VerifRegex& operator=(const VerifRegex& vrx);

    struct Handler {
        VerifRegex* instance;
        Handler(): instance(nullptr) {}
        ~Handler(){delete instance;}
    };
    static Handler handler;

public:
    
    static VerifRegex& getInstance();
    static void libereInstance();

    AtomeManager& getAtm(){return Atm;}

    bool verifEntier(QString s);
    bool verifReel(QString s);
    bool verifRationnel(QString s);
    bool verifComplexe(QString s);
    bool verifNombre(QString s);

    bool verifOperateurSimple(QString s);
    bool verifOperateurAvance(QString s);       // fait le listing des strings des operateurs que l'on peut inserer dans la ligne de commande
    bool verifOperateurAvanceExp(QString s);    // verifie les operateurs definis pas une chaine de char (et des parenthèses avec des args dedans... separés par des virgules !)

    bool verifAtome(QString s);    // verifie que le string est un candidat pour devenir un atome
    bool verifAtomeExistant(QString s);    // verifie que c'est un atome déjà defini

    bool verifExpression(QString s);
    bool verifProgramme(QString s);

};





#endif // VERIFREGEX_H
