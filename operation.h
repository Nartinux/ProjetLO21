#ifndef OPERATION_H
#define OPERATION_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "nombre.h"
#include "objectpile.h"
#include "computer.h"
#include "pile.h"


// BUT FAIRE EVAL POUR LES EXPRESSIONS



//------------------------------------------- CLASS OPERATEURAVANCE ---------------------------------------------------------------------------------------------------


class OperateurAvance // abstraite elle permet de donner acces a une pile pour toutes ses classes dérivées
{
	Pile& expAff;	// FAUT QUE CA SOIT LA MEME PILE -> singleton ou bien faire attention lors de la construction !
public:
	OperateurAvance(Pile& p): expAff(p) {}
	virtual ~OperateurAvance();
    virtual ObjectPile& operation()=0;	// cette methode prends 0 args elle les prends direct dans la pile
    Pile& getPile(){return expAff;}
		
};



//------------------------------------------- CLASS EVAL ---------------------------------------------------------------------------------------------------

class Eval : public OperateurAvance
{
public:
	Eval(Pile& p): OperateurAvance(p) {}
	~Eval();
	ObjectPile& operation();

};













Entier& modulo(Entier& a,Entier& b);
Entier& diveucli(Entier& a,Entier& b);





#endif // OPERATION_H
