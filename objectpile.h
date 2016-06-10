#ifndef OBJECTPILE_H
#define OBJECTPILE_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "exception.h"


//---------------------------------------- CLASS OBJECTPILE ----------------------------------------

class ObjectPile
{
public:
	virtual QString toString()const=0;
	virtual ~ObjectPile();
};


//---------------------------------------- CLASS EXPRESSION ----------------------------------------

class Expression : public ObjectPile
{
    QString exp;
public:
	Expression(QString& s): exp(s){}
	~Expression();
	QString toString()const;
	const QString getExp()const {return exp;}
};

//---------------------------------------- CLASS PROGRAMME ----------------------------------------

class Programme : public ObjectPile
{
    QString prg;
public:
	Programme(QString& s): prg(s) {}
	~Programme();
	QString toString()const;
	const QString getPrg()const {return prg;}

};


//---------------------------------------- CLASS ATOME ----------------------------------------


class Atome : public ObjectPile
{
    QString ID;
    ObjectPile* val;

public:
	Atome();
	Atome(QString& s, ObjectPile* obp): ID(s), val(obp){}
	~Atome();
    const QString& getID()const {return ID;}
	bool operator!=(Atome& a)const {return ID!=a.getID();}
	ObjectPile* getVal() {return val;}
	void setVal(ObjectPile* v) {val=v;}
	QString toString()const;

};


//---------------------------------------- CLASS ATOMEMANAGER ----------------------------------------



class AtomeManager		//singleton
{
	Atome* tab;			// tableau d'obj Atomes
	unsigned int nb;
	unsigned int nbMax;
	void agrandissementCapacite();
    AtomeManager(): tab(0), nb(0), nbMax(0){}
	~AtomeManager(){delete[] tab;}
    AtomeManager(const AtomeManager& am);
	AtomeManager& operator=(const AtomeManager& am);

	struct Handler {
        AtomeManager* instance;
        Handler(): instance(nullptr){}
        ~Handler(){delete instance;}
	};
	static Handler handler;

public:

	const unsigned int getNb()const {return nb;}
	static AtomeManager& getInstance();
	static void libereInstance();

    Atome* findAt(QString s);
	bool existAt(QString& s);

	void addAtome(Atome& a);
	void removeAtome (QString& s);


	// ----------- ITERATOR ----------------------------

	class iterator
	{
		Atome* curs;
		iterator(Atome* a): curs(a){}
        friend class AtomeManager;
	public:
		iterator& operator+(int k)
		{
			curs+=k;
			return *this;
		}
		iterator& operator++()
		{
			curs++;
			return *this;
		}
        Atome& operator*()const{return *curs;}
        bool operator!=(iterator it)const {return it.getCurs()!=curs;}
		Atome* getCurs()const {return curs;}
	};
    iterator begin(){return iterator(tab); }
    iterator end(){return iterator(tab+nb); }

};












#endif // OBJECTPILE_H
