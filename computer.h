#ifndef COMPUTER_H
#define COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include "exception.h"
#include "nombre.h"


using namespace std;


/*
class Expression {
    int value;
    Expression(const Expression& e);
    Expression& operator=(const Expression& e);
    //friend class ExpressionManager;
public:
    Expression(int v):value(v){}
    QString toString() const;
    int getValue() const { return value; }
};*/

// ------------------------------------------------------ CLASS LIBMEMORY ------------------------------------------------------------------------


class LibMemory 
{
public:
    static void freeMem(Nombre* n){delete n;}
};




// ------------------------------------------------------ CLASS FACTORY ------------------------------------------------------------------------



class Factory
{
public:
    Nombre* Product(const QString s);
};




// ------------------------------------------------------ Le reste : pile, controleur -----------------------------------------------------------





/*
class ExpressionManager {
    Expression** exps;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();
    ExpressionManager():exps(nullptr),nb(0),nbMax(0){}
    ~ExpressionManager();
    ExpressionManager(const ExpressionManager& m);
    ExpressionManager& operator=(const ExpressionManager& m);

    struct Handler{
        ExpressionManager* instance;
        Handler():instance(nullptr){}
        // destructeur appelé à la fin du programme
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    Expression& addExpression(int v);
    void removeExpression(Expression& e);
    static ExpressionManager& getInstance();
    static void libererInstance();
    class Iterator {
        friend class ExpressionManager;
        Expression** currentExp;
        unsigned int nbRemain;
        Iterator(Expression** u, unsigned nb):currentExp(u),nbRemain(nb){}
    public:
        Iterator():currentExp(nullptr),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw ComputerException("error, next on an iterator which is done");
            nbRemain--;
            currentExp++;
        }
        Expression& current() const {
            if (isDone())
                throw ComputerException("error, indirection on an iterator which is done");
            return **currentExp;
        }
    };
    Iterator getIterator() {
        return Iterator(exps,nb);
    }
    class iterator {
        Expression** current;
        iterator(Expression** u):current(u){}
        friend class ExpressionManager;
    public:
        iterator():current(0){}
        Expression& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(exps); }
    iterator end() { return iterator(exps+nb); }

    class const_iterator {
        Expression** current;
        const_iterator(Expression** u):current(u){}
        friend class ExpressionManager;
    public:
        const_iterator():current(0){}
        Expression& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ ++current; return *this; }
    };
    const_iterator begin() const { return const_iterator(exps); }
    const_iterator end() const { return const_iterator(exps+nb); }
};


class Item {
    Expression* exp;
public:
    Item():exp(nullptr){}
    void setExpression(Expression& e) { exp=&e; }
    void raz() { exp=0; }
    Expression& getExpression() const;
};


*/

class Pile : public QObject {
    Q_OBJECT

    //Item* items;
    Nombre** exps; // ammené a changer car on va avoir des atomes ? ptet pas en fait...
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    void agrandissementCapacite();
    unsigned int nbAffiche;
public:
    //construct et destruct
    Pile():exps(nullptr),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();

    void push(Nombre& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    //void affiche(QTextStream& f) const;
    Nombre& top() const;
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; } // utile ?? 
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }

    class iterator {
        //Item* current;
        Nombre **current;
        iterator(Nombre** u):current(u){}
        friend class Pile;
    public:
        iterator():current(nullptr){}
        Nombre& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ --current; return *this; }
    };
    iterator begin() { return iterator(exps+nb-1); }
    iterator end() { return iterator(exps-1); }

    class const_iterator {
        //Item* current;
        Nombre **current;
        const_iterator(Nombre** u):current(u){}
        friend class Pile;
    public:
        const_iterator():current(nullptr){}
        const Nombre& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ --current; return *this; }
    };
    const_iterator begin() const { return const_iterator(exps+nb-1); }
    const_iterator end() const { return const_iterator(exps-1); }

signals:
    void modificationEtat();
};



class Controleur {
    //ExpressionManager& expMng;
    Factory& facto;
    Pile& expAff;
public:
    Controleur(Pile& v, Factory& f):expAff(v), facto(f){}
    void commande(const QString& c);

};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);



#endif // COMPUTER_H
