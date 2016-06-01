#include "objectpile.h"

ObjectPile::~ObjectPile(){}
Expression::~Expression(){}
Programme::~Programme(){}
Atome::~Atome(){}


//---------------------------------------- CLASS EXPRESSION ----------------------------------------



QString Expression::toString()const
{
	return exp;
}


//---------------------------------------- CLASS PROGRAMME ----------------------------------------



QString Programme::toString()const
{
	return prg;
}

//---------------------------------------- CLASS ATOME ----------------------------------------------

Atome::Atome(){}


QString Atome::toString()const
{
    return ID;
}
// cas ou on voudrais afficher l'ID ! attention pas l'usage général !


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

void AtomeManager::addAtome(Atome& a){
	if (nb==nbMax) agrandissementCapacite();
    tab[nb++]=a;
}


void AtomeManager::removeAtome(Atome& a){
	unsigned int i=0;
    while(i<nb && tab[i].operator !=(a)) i++;
	if (i==nb) throw ComputerException("elimination d'un Atome inexistant");
    delete &tab[i];
	i++;
	while(i<nb) { tab[i-1]=tab[i]; i++; }
	nb--;
}

Atome& AtomeManager::findAt(QString& s)
{
	unsigned int i=0;
	while(i<nb && tab[i].getID()!=s) i++;
	if (i==nb) throw ComputerException("recherche d'un atome inexistant");
	return tab[i];
}

bool AtomeManager::existAt(QString& s)
{
	unsigned int i=0;
	while(i<nb) if(tab[i].getID()!=s) i++; else break;
	if (i==nb) return false;
	return true;
}



/*
ExpressionManager& ExpressionManager::operator=(const ExpressionManager& m){
	if (this==&m) return *this;
	Expression** newtab=new Expression*[m.nbMax];
	for(unsigned int i=0; i<nb; i++) 
		newtab[i]=new Expression(*m.exps[i]);
	Expression** old=exps;
	unsigned int oldnb=nb;
	exps=newtab;
	nb=m.nb;
	nbMax=m.nbMax;
	for(unsigned int i=0; i<oldnb; i++) delete old[i];
	delete[] old;
	return *this;
}
*/

