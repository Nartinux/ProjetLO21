#include "objectpile.h"

ObjectPile::~ObjectPile(){}



//---------------------------------------- CLASS EXPRESSION ----------------------------------------

Expression::~Expression(){}

QString Expression::toString()const
{
	return exp;
}


//---------------------------------------- CLASS PROGRAMME ----------------------------------------

Programme::~Programme(){}

QString Programme::toString()const
{
	return prg;
}

//---------------------------------------- CLASS ATOME ----------------------------------------------

Atome::Atome(){}
Atome::~Atome()
{
	if(val) delete val;		// si c'est pas nullptr, on le delete
}

QString Atome::toString()const
{
    return ID;
}
// cas ou on voudrais afficher l'ID ...


//---------------------------------------- CLASS ATOMEMANAGER ----------------------------------------


void AtomeManager::agrandissementCapacite() {
	Atome* newtab=new Atome[nbMax+10];
	for(unsigned int i=0; i<nb; i++) newtab[i]=tab[i];
	Atome*  old=tab;
	tab=newtab;
	nbMax=+10;
	delete[] old;
}

AtomeManager::Handler AtomeManager::handler=AtomeManager::Handler();

AtomeManager& AtomeManager::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new AtomeManager;}
    return *handler.instance;
}

void AtomeManager::libereInstance()
{
	if (handler.instance == nullptr) throw ComputerException("on peut pas liberer une instance si elle est pas cree");
	delete handler.instance;
	handler.instance=nullptr;
}

void AtomeManager::addAtome(Atome& a)
	{
	if (nb==nbMax) agrandissementCapacite();
    tab[nb++]=a;
}


void AtomeManager::removeAtome(QString& s)
{
	unsigned int i=0;
    while(i<nb) {if(tab[i].getID()!=s) i++; else break;}
    //delete &tab[i];
	i++;
    while(i<nb) {tab[i-1]=tab[i]; i++;}
	nb--;
}

Atome* AtomeManager::findAt(QString& s)
{
	unsigned int i=0;
	//while(i<nb && tab[i].getID()!=s) i++;
	while(i<nb) {if(tab[i].getID()!=s) i++; else break;}
	if (i==nb) return nullptr;
    return &tab[i];
}

bool AtomeManager::existAt(QString& s)
{
	unsigned int i=0;
	while(i<nb) {if(tab[i].getID()!=s) i++; else break;}
	if (i==nb) return false;
	return true;
}

