#ifndef PILE_H
#define PILE_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "objectpile.h"



// ------------------------------------------------------ CLASS PILE -----------------------------------------------------------


class Pile : public QObject {
    Q_OBJECT

    //Item* items;
    ObjectPile** ob; // ammené a changer car on va avoir des atomes ? ptet pas en fait...
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    void agrandissementCapacite();
    unsigned int nbAffiche;
public:
    //construct et destruct
    Pile():ob(nullptr),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();

    void push(ObjectPile& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    //void affiche(QTextStream& f) const;
    ObjectPile& top() const;
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; } // utile ??
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }

    class iterator {
        //Item* current;
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

    class const_iterator {
        //Item* current;
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


#endif // PILE_H
