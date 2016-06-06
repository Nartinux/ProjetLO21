#include "pile.h"






//----------------- CLASS PILE -----------------------------------------------------------------------------------------------------------------


void Pile::push(ObjectPile &e){
    if (nb==nbMax) agrandissementCapacite();
    ob[nb]=&e;
    nb++;
    modificationEtat();
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


