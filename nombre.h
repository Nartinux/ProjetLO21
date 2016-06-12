#ifndef NOMBRE_H
#define NOMBRE_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "objectpile.h"


//---------------------------------------- CLASS NOMBRE ----------------------------------------


class Nombre : public ObjectPile
{
public :
    virtual Nombre& operator+(Nombre& a)=0;
    virtual Nombre& operator-(Nombre& a)=0;
    virtual Nombre& operator*(Nombre& a)=0;
    virtual Nombre& operator/(Nombre& a)=0;
    Nombre& operator$(Nombre& a);
    virtual Nombre& neg()=0;
    virtual QString toString()const=0;
    virtual ~Nombre();
};

// ------------ CLASS ENTIER -----------------------------------

class Entier : public Nombre
{
    int val;
    friend class Rationnel;
    friend class Reel;
    friend class Complexe;
public :

    //constructeur
    Entier(int a): val(a){}

    //destructeur
    ~Entier();

    //getters
    int getInt()const {return val;}

    //operateurs
    Nombre& operator+(Nombre& a);
    Nombre& operator-(Nombre& a);
    Nombre& operator*(Nombre& a);
    Nombre& operator/(Nombre& a);
    Nombre& neg();
    QString toString()const;
};


// ------------ CLASS RATIONNEL -----------------------------------


class Rationnel : public Nombre
{
    Entier* num;
    Entier* den;
    void simplificationConstruct();
    friend class Factory;
    friend class Entier;
    friend class Reel;
    friend class Complexe;
public :
    Nombre& simplificationExt();
    //constructeur
    Rationnel(Entier& n, Entier& d)
    {
        if (d.val==0) {throw ComputerException("le denominateur ne peut etre nul !");}
        num=&n;
        den=&d;
        simplificationConstruct();
    }
    //destructeur
    ~Rationnel(){}

    //getters
    Entier& getNum()const {return *num;}
    Entier& getDen()const {return *den;}

    //operateurs
    Nombre& operator+(Nombre& a);
    Nombre& operator-(Nombre& a);
    Nombre& operator*(Nombre& a);
    Nombre& operator/(Nombre& a);
    Nombre& neg();
    QString toString()const;
};


// ------------ CLASS REEL -----------------------------------

class Reel : public Nombre
{
    double val;
    friend class Rationnel;
    friend class Entier;
    friend class Complexe;
    Nombre& simplification();
public :
    //constructeur
    Reel(double a): val(a){}

    //destructeur
    ~Reel();

    //getters
    double getRel()const {return val;}

    Nombre& operator+(Nombre& a);
    Nombre& operator-(Nombre& a);
    Nombre& operator*(Nombre& a);
    Nombre& operator/(Nombre& a);
    Nombre& neg();
    QString toString()const;

};


// ----------------------- CLASS COMPLEXE -------------------

class Complexe : public Nombre
{
    Nombre* re;
    Nombre* im;
    friend class Factory;
    friend class Rationnel;
    friend class Reel;
    friend class Entier;

public :
    //constructeur
    Complexe(Nombre& r,Nombre& i)
    {
        re=&r;
        im=&i;
    }

    //destructeur
    ~Complexe();

    //simplificateur
    Nombre& simplification();

    //getters 
    Nombre& getRe()const {return *re;}
    Nombre& getIm()const {return *im;}

    //operaeurs
    Nombre& operator+(Nombre& a);
    Nombre& operator-(Nombre& a);
    Nombre& operator*(Nombre& a);
    Nombre& operator/(Nombre& a);
    Nombre& operator$(Nombre& a);
    Nombre& neg();
    QString toString()const;
};




// ------------------------------------------------------ CLASS LIBMEMORY ------------------------------------------------------------------------


class LibMemory
{
public:
    static void freeMem(Nombre* n) {delete n;}

};






#endif // NOMBRE_H
