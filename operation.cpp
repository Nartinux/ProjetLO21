#include"operation.h"

//------------------------------------------- CLASS OPERATEURAVANCE  ---------------------------------------------------------------------------------------------------

OperateurAvance::~OperateurAvance() {}




//------------------------------------------- CLASS EVAL ---------------------------------------------------------------------------------------------------


Eval::~Eval(){}

void Eval::operation()
{

    ObjectPile& obp=getPile().top();
    getPile().pop();
    Expression* exp=dynamic_cast<Expression*>(&obp);
    if (!exp)
    {
        getPile().push(*exp);
        getPile().setMessage("Erreur ce n'est pas une expression");
    }
   
}


//------------------------------------------- CLASS STO ---------------------------------------------------------------------------------------------------


Sto::~Sto() {}




void Sto::operation()
{
    ObjectPile& val=getPile().top();
    getPile().pop();

    ObjectPile& exp=getPile().top();
    getPile().pop();
    Expression* expat=dynamic_cast<Expression*>(&exp);
    if (!expat)
    {
        getPile().push(*expat);
        getPile().setMessage("Erreur ce n'est pas une expression");
        getPile().push(val);                // on remet aussi l'objet qui etait a mettre dans l'atome
    }
    else
    {
        QString s= expat->getExp();
        QString s2=s.mid(1,(s.length()-2));

        if (getVrx().verifOperateurAvance(s2))
        {
            getPile().push(*expat);
            getPile().setMessage("Non, il s'agit d'un operateur");
            getPile().push(val);            // on remet aussi l'objet qui etait a mettre dans l'atome
        }
        else if(getVrx().verifAtomeExistant(s2))
        {
            Atome& at=getAtm().findAt(s2);  // on cherche l'atome dans l'atome manager
            //delete at.getVal();             // on detruit l'ancienne valeur
            ObjectPile* obp=at.getVal();
            obp=&val;                       // on met la valeur du premier objectPile recup, quoi que se soit.
            //delete expat;                   // on detruit l'expression represantant l'atome
        }
        else if (getVrx().verifAtome(s2))
        {
            Atome* a=new Atome(s2);         // on cree un nouvel atome
            ObjectPile* obp=a->getVal();
            obp=&val;                       // on lui affecte la valeur adéquate
            getAtm().addAtome(*a);          // on le met dans AtomeManager
            //delete expat;                   // on detruit l'expression represantant l'atome
        }
        else    // l'expression ne represente pas un atome
        {
            getPile().push(*expat);
            getPile().setMessage("l'expression n'est pas un atome");
            getPile().push(val);            // on remet aussi l'objet qui etait a mettre dans l'atome
        }
    }
}




//------------------------------------------- CLASS FORGET ---------------------------------------------------------------------------------------------------

Forget::~Forget(){}

void Forget::operation()
{
    ObjectPile& exp=getPile().top();
    getPile().pop();
    Expression* expat=dynamic_cast<Expression*>(&exp);
    if (!expat)
    {
        getPile().push(*expat);
        getPile().setMessage("Erreur ce n'est pas une expression");
    }
    else
    {
        QString s=expat->getExp();
        QString s2=s.mid(1,(s.length()-2));

        if (getVrx().verifOperateurAvance(s2))
        {
            getPile().push(*expat);
            getPile().setMessage("Non, il s'agit d'un operateur");
        }
        else if(getVrx().verifAtomeExistant(s2))
        {
            Atome& at=getAtm().findAt(s2);  // on cherche l'atome dans l'atome manager
            getAtm().removeAtome(at);       // on detruit l'atome via l'atomeManager, le destructeur de l'atome s'occupe de détruire son objPile
            delete expat;                   // on detruit l'expression represantant l'atome
        }
        else    // l'expression ne represente pas un atome
        {
            getPile().push(*expat);
            getPile().setMessage("cet atome n'existe pas");
        }
    }
}


// ------------------------------------------------------ CLASS MODULO ------------------------------------------------------------------------

Modulo::~Modulo(){}

void Modulo::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* a2=dynamic_cast<Nombre*>(&v2);
        if(a1 && a2)
        {
            Entier* ent1=dynamic_cast<Entier*>(a1);
            Entier* ent2=dynamic_cast<Entier*>(a2);
            if (ent1 && ent2)  
            {
                Entier* res =new Entier(ent1->getInt()%ent2->getInt());
                expAff.push(*res);
                expAff.setMessage("Modulo effectué");
            }
        }
    }
}




Entier& modulo(Entier& a,Entier& b){
    Entier* ent=new Entier(a.getInt()%b.getInt());
    return *ent;
}

Entier& diveucli(Entier& a,Entier& b){
    Entier* ent=new Entier(a.getInt()/b.getInt());
    return *ent;
}






// ------------------------------------------------------ CLASS FACTORYOPERATEUR ------------------------------------------------------------------------




FactoryOperateur::~FactoryOperateur() {}

FactoryOperateur::Handler FactoryOperateur::handler=FactoryOperateur::Handler();

FactoryOperateur* FactoryOperateur::getInstance(Pile& p)
{
    if(handler.instance==nullptr){handler.instance= new FactoryOperateur(p);}
    return handler.instance;
}

void FactoryOperateur::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("impossible to destruct an instance which haven't been created");
    delete handler.instance;
    handler.instance=nullptr;
}


OperateurAvance* FactoryOperateur::ProductOP(QString s)
{
    if (s=="EVAL")
    {
        return new Eval(pil);
    }
    else if (s=="STO")
    {
        return new Sto(pil);
    }
    else if (s=="FORGET")
    {
        return new Forget(pil);
    }
    else if (s=="MOD")
    {
        return new Modulo(pil);
    }
    else return nullptr;
}
