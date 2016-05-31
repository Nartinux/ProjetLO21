#include <algorithm>
#include "computer.h"
#include "exception.h"




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




//----------------- CLASS CONTROLEUR ------------------------------------------------------------------------------------------------------------------------------------------------

// A REFAIRE COMPLETEMENT !!!!!!!!!!!!!

void Controleur::sentCommande(/*const */QString& s)
{
//expAff.setMessage(s);/*
    ObjectPile* op=nullptr;
    if ((op=factoG.Product(s))!=nullptr)
    {


        expAff.push(*op);
        Expression* a1=dynamic_cast<Expression*>(op);
        Nombre* a2=dynamic_cast<Nombre*>(op);
        Programme* a3=dynamic_cast<Programme*>(op);
        Atome* a4=dynamic_cast<Atome*>(op);
        expAff.setMessage(s);
        if(a1!=nullptr) expAff.setMessage("c'est une expression");
        if(a2!=nullptr) expAff.setMessage("c'est un nb");
        if(a3!=nullptr) expAff.setMessage("c'est un un progr");
        if(a4!=nullptr) expAff.setMessage("c'est un atome");
        
    }
    else
    {
        if (vrx.verifOperateurSimple(s))
        {
            if (expAff.taille()>=2) // a modifier
            {
                ObjectPile& v2=expAff.top();
                expAff.pop();
                ObjectPile& v1=expAff.top();
                expAff.pop();
                Nombre* a1=dynamic_cast<Nombre*>(&v1);
                Nombre* a2=dynamic_cast<Nombre*>(&v2);
                if(a1!=nullptr && a2!=nullptr)
                {
                    if (s=="+") {Nombre* b1=&(a1->operator+(*a2)); expAff.push(*b1); LibMemory::freeMem(a1); LibMemory::freeMem(a2);}
                    if (s=="-") {expAff.push(a1->operator-(*a2)); LibMemory::freeMem(a1); LibMemory::freeMem(a2);}
                    if (s=="*") {expAff.push(a1->operator*(*a2)); LibMemory::freeMem(a1); LibMemory::freeMem(a2);}
                    if (s=="/") 
                    {   
                        Entier* ent=dynamic_cast<Entier*>(a2);
                        if (ent==nullptr || ent->getInt()!=0) {expAff.push(a1->operator/(*a2)); LibMemory::freeMem(a1); LibMemory::freeMem(a2);}
                        else 
                        {
                            expAff.push(*a1);
                            expAff.push(*a2);
                            expAff.setMessage("Erreur : division par zéro");
                        }
                    }
                }
                else
                {
                    expAff.setMessage("Les operandes ne sont pas des nuneriques");
                    expAff.push(*a1);
                    expAff.push(*a2);
                }
            }
            else expAff.setMessage("Erreur : pas assez d'arguments");
        }
        else expAff.setMessage("Erreur : commande inconnue");
    }
}
