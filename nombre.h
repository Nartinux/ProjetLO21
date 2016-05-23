#ifndef NOMBRE_H
#define NOMBRE_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "exception.h"



//---------------------------------------- CLASS NOMBRE ----------------------------------------


class Nombre
{
public :
    virtual Nombre& operator+(Nombre& a)=0;
    virtual Nombre& operator-(Nombre& a)=0;
    virtual Nombre& operator*(Nombre& a)=0;
    virtual Nombre& operator/(Nombre& a)=0;
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
    Nombre& simplification();
    friend class Factory;
    friend class Entier;
    friend class Reel;
    friend class Complexe;
public :

    //constructeur
    Rationnel(Entier& n, Entier& d)
    {
        if (d.val==0) {throw ComputerException("le denominateur ne peut etre nul !");}
        num=&n;
        den=&d;
        simplification();
    }
    //destructeur
    ~Rationnel()
    {
        delete num;
        delete den;
    }

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
    Reel(double a): val(a)
    {
        
    }

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
    Nombre& simplification();
    friend class Factory;
    friend class Rationnel;
    friend class Reel;
    friend class Entier;

public :
    //constructeur
    // ici l'upcast implicite fonctionne si on met direct un entier et un reel par exemple ? a try
    Complexe(Nombre& r,Nombre& i)
    {
        re=&r;
        im=&i;
        simplification();
    }

    //destructeur
    ~Complexe();

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

    // creer un complexe avec l'operator $
};











#endif // NOMBRE_H
