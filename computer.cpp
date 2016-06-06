#include <algorithm>
#include "computer.h"





//----------------- CLASS CONTROLEUR ------------------------------------------------------------------------------------------------------------------------------------------------


void Controleur::sentCommande(/*const */QString& s)
{
    //if(vrx.verifOperateurAvance(s)) expAff.setMessage(s); else expAff.setMessage("fuck");

    ObjectPile* op=nullptr;
    if (!(vrx.verifAtomeExistant(s)) && (vrx.verifAtome(s)) ) // si c'est pas un atome existant ! -> on le met dans une expression
    {
        QString s2("\'");
        s2+=s;
        s2+="\'";
        expAff.setMessage(s2);
        op=factoE.ProductE(s2);
        expAff.push(*op);
    }
    /*else if (vrx.verifAtomeExistant(s))
    {
        op*=vrx.getAtm.findAt(s);
        expAff.push(op->);
    }*/
    else if ((op=factoG.Product(s))!=nullptr)
    {
        Expression* a1=dynamic_cast<Expression*>(op);
        Nombre* a2=dynamic_cast<Nombre*>(op);
        Programme* a3=dynamic_cast<Programme*>(op);
        Atome* a4=dynamic_cast<Atome*>(op);
        if(a1!=nullptr) expAff.setMessage("c'est une expression");
        if(a2!=nullptr) expAff.setMessage("c'est un nb");
        if(a3!=nullptr) expAff.setMessage("c'est un progr");
        if(a4!=nullptr) { expAff.setMessage("c'est un atome"); if(expAff.taille()>=1) { } else expAff.setMessage("Erreur : pas assez d'arguments"); }
        expAff.push(*op);
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
                        if (ent==nullptr || ent->getInt()!=0) {expAff.push(a1->operator/(*a2));} //LibMemory::freeMem(a1); LibMemory::freeMem(a2);
                        else 
                        {
                            expAff.push(*a1);
                            expAff.push(*a2);
                            expAff.setMessage("Erreur : division par zéro");
                        }
                    }
                    if (s=="$") {expAff.push(a1->operator$(*a2)); //LibMemory::freeMem(&v1); LibMemory::freeMem(&v2);
                    }
                    if (s=="MOD") {
                        Entier* ent1=dynamic_cast<Entier*>(a1);
                        Entier* ent2=dynamic_cast<Entier*>(a2);
                        if (ent1!=nullptr && ent2!=nullptr){
                            expAff.push(modulo(*ent1,*ent2)); //LibMemory::freeMem(&v1); LibMemory::freeMem(&v2);
                        }
                        else
                        {
                            expAff.push(*a1);
                            expAff.push(*a2);
                            expAff.setMessage("Erreur : Le modulo de la division n'est défini que sur des entiers");
                        }
                    }
                    if (s=="DIV") {
                        Entier* ent1=dynamic_cast<Entier*>(a1);
                        Entier* ent2=dynamic_cast<Entier*>(a2);
                        if (ent1!=nullptr && ent2!=nullptr){
                            expAff.push(diveucli(*ent1,*ent2)); //LibMemory::freeMem(&v1); LibMemory::freeMem(&v2);
                        }
                        else
                        {
                            expAff.push(*a1);
                            expAff.push(*a2);
                            expAff.setMessage("Erreur : La division euclidienne n'est défini que sur des entiers");
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
