#include "pile.h"






//----------------- CLASS PILE -----------------------------------------------------------------------------------------------------------------


void Pile::push(ObjectPile &e){
    if (nb==nbMax) agrandissementCapacite();
    ob[nb]=&e;
    nb++;
    modificationEtat();
    Memento* mem= new Memento(ob, nb, nbMax,message, nbAffiche);
    PileMemento& pm=PileMemento::getInstance();
    pm.push(*mem);
}


void Pile::pop(){
    nb--;
    ob[nb]=nullptr;
    modificationEtat();
}

void Pile::agrandissementCapacite()
{
    ObjectPile** newtab=new ObjectPile*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=ob[i];
    ObjectPile**  old=ob;
    ob=newtab;
    nbMax=(nbMax+1)*2;
    delete[] old;
}

Pile::~Pile(){
    delete[] ob;
}



ObjectPile& Pile::top() const {

    if (nb==0) throw ComputerException("aucune expression sur la pile");
    return *(ob[nb-1]);
}


//--------------------------------------------------- CLASS PILE::PILEMEMENTO -------------------------------------------------------------------------------

void PileMemento::agrandissementCapacite()
{
    Memento** newtab=new Memento*[nbMax+10];
    for(unsigned int i=0; i<nb; i++) newtab[i]=memp[i];
    Memento** old=memp;
    memp=newtab;
    nbMax=+10;
    delete[] old;
}

PileMemento::Handler PileMemento::handler=PileMemento::Handler();

PileMemento& PileMemento::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new PileMemento;}
    return *handler.instance;
}

void PileMemento::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("on peut pas liberer une instance si elle est pas cree");
    delete handler.instance;
    handler.instance=nullptr;
}




void PileMemento::push(Memento &mem){
    if (nb==nbMax) agrandissementCapacite();
    memp[nb]=&mem;
    nb++;
}


Memento& PileMemento::pop()
{
    if (nb==0) throw ComputerException("aucune expression sur la PileMemento");
    Memento& memret=*(memp[nb-1]);
    nb--;
    memp[nb]=nullptr;
    return memret;
}

void PileMemento::restore(Pile& p)
{
    Memento& mem=pop();
    // on efface la pile
    for (unsigned int i = 0; i < p.nb; ++i)
    {
        p.ob[i]=nullptr;
    }
    // on re remplie la pile avec memento
    for (unsigned int i = 0; i < mem.nbM; ++i)
    {
        p.ob[i]=mem.obM[i];
    }
    p.nb=mem.nbM;
    p.nbMax=mem.nbMaxM;
    p.message=mem.messageM;
    p.nbAffiche=mem.nbAfficheM;
}

