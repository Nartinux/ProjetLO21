#include <algorithm>
#include "computer.h"




//----------------- CLASS CONTROLEUR ------------------------------------------------------------------------------------------------------------------------------------------------


void Controleur::sentCommande(QString& s)
{
    OperateurAvance* op=nullptr;
    ObjectPile* obp=nullptr;

    // --- partie operations avancees

    if ((op=factoOP.ProductOP(s))!=nullptr) // dans le cas d'un operateur avance
    {
        expAff.setMessage("operation avancee");
        op->operation();
    }
    else if (vrx.verifAtomeExistant(s))
    {
        expAff.setMessage("atome existant");
        Atome* atexist=vrx.getAtm().findAt(s);
        Expression* a1=dynamic_cast<Expression*>(atexist->getVal());
        Programme* a3=dynamic_cast<Programme*>(atexist->getVal());
        if (a1)
        {
            expAff.push(*a1);
            op=factoOP.ProductOP("EVAL");
            op->operation();
        }
        else if (a3)
        {
            expAff.push(*a3);
            op=factoOP.ProductOP("EVAL");
            op->operation();
        }
        else
        {
            expAff.push(*(atexist->getVal()));
        }
    }
    else if (vrx.verifAtome(s) && !vrx.verifOperateurAvance(s)) // si c'est pas un atome existant, on le met dans une expression
    {
        QString s2("\'");
        s2+=s;
        s2+="\'";
        expAff.setMessage("atome transforme en exp");
        obp=factoE.ProductE(s2);
        expAff.push(*obp);
    }
    else if ((obp=factoG.Product(s))!=nullptr)  // si c'est un objectPile autre que atome
    {
        Expression* a1=dynamic_cast<Expression*>(obp);
        Nombre* a2=dynamic_cast<Nombre*>(obp);
        Programme* a3=dynamic_cast<Programme*>(obp);
        if(a1!=nullptr) expAff.setMessage("c'est une expression");
        if(a2!=nullptr) expAff.setMessage("c'est un nb");
        if(a3!=nullptr) expAff.setMessage("c'est un progr");
        expAff.push(*obp);
    }
    else
    {
        if (vrx.verifOperateurSimple(s))
        {
            if (expAff.taille()>=2)
            {
                ObjectPile& v2=expAff.top();
                expAff.pop();
                ObjectPile& v1=expAff.top();
                expAff.pop();
                Nombre* a1=dynamic_cast<Nombre*>(&v1);
                Nombre* a2=dynamic_cast<Nombre*>(&v2);
                if(a1!=nullptr && a2!=nullptr)
                {
                    if (s=="+") expAff.push(a1->operator+(*a2));
                    if (s=="-") expAff.push(a1->operator-(*a2));
                    if (s=="*") expAff.push(a1->operator*(*a2));
                    if (s=="/")
                    {
                        Entier* ent=dynamic_cast<Entier*>(a2);
                        if (ent==nullptr || ent->getInt()!=0) {expAff.push(a1->operator/(*a2));}
                        else
                        {
                            expAff.push(*a1);
                            expAff.push(*a2);
                            expAff.setMessage("Erreur : division par zéro");
                        }
                    }
                    if (s=="$") {expAff.push(a1->operator$(*a2));}
                }
                else
                {
                    expAff.setMessage("Les operandes ne sont pas des nombres");
                    expAff.push(*a1);
                    expAff.push(*a2);
                }
            }
            else expAff.setMessage("Erreur : pas assez d'arguments");
        }
        else expAff.setMessage("Erreur : commande inconnue");
    }
}

