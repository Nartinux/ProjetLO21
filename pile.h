#ifndef PILE_H
#define PILE_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "objectpile.h"



// ------------------------------------------------------ CLASS PILE -----------------------------------------------------------


class Pile : public QObject
{
    Q_OBJECT

    ObjectPile** ob;
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    unsigned int nbAffiche;
    void agrandissementCapacite();
    friend class PileMemento;
public:
    //construct et destruct
    Pile():ob(nullptr),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();

    void push(ObjectPile& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    ObjectPile& top() const;
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }

    class iterator 
    {
        ObjectPile **current;
        iterator(ObjectPile** u):current(u){}
        friend class Pile;
    public:
        iterator():current(nullptr){}
        ObjectPile& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ --current; return *this; }
    };
    iterator begin() { return iterator(ob+nb-1); }
    iterator end() { return iterator(ob-1); }

    class const_iterator 
    {
        ObjectPile **current;
        const_iterator(ObjectPile** u):current(u){}
        friend class Pile;
    public:
        const_iterator():current(nullptr){}
        const ObjectPile& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ --current; return *this; }
    };
    const_iterator begin() const { return const_iterator(ob+nb-1); }
    const_iterator end() const { return const_iterator(ob-1); }



signals:
    void modificationEtat();
};




class Memento
{
    ObjectPile** obM;
    unsigned int nbM;
    unsigned int nbMaxM;
    QString messageM;
    unsigned int nbAfficheM;

    //Pile pil;
    friend class PileMemento;
public:
    Memento(ObjectPile** ob, unsigned int nb, unsigned int nbMax, QString message, unsigned int nbAffiche): nbM(nb), nbMaxM(nbMax), messageM(message), nbAfficheM(nbAffiche)
    {
        /*ObjectPile** obM=new ObjectPile*[nbMax];
        for(unsigned int i=0; i<nb; i++) obM[i]=ob[i];*/
    }
    ~Memento()
    {
        //delete[] obM;
    }
    //Pile& getPile(){return &pil;}
    //QString getMessage() {return messageM;}
};




class PileMemento
{

    Memento** memp;
    unsigned int nb;
    unsigned int nbMax;

    void agrandissementCapacite();
    PileMemento(): memp(0), nb(0), nbMax(0){}
    ~PileMemento(){delete[] memp;}
    PileMemento(const PileMemento& am);
    PileMemento& operator=(const PileMemento& am);

    struct Handler {
        PileMemento* instance;
        Handler(): instance(nullptr){}
        ~Handler(){delete instance;}
    };
    static Handler handler;
public:
    static PileMemento& getInstance();
    static void libereInstance();

    void push(Memento& mem);
    Memento& pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void restore(Pile& p);

};









#endif // PILE_H
