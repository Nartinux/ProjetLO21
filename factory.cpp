#include "factory.h"


//----------------- CLASS FACTORYG ------------------------------------------------------------------------------------------------------------------------------------------------

FactoryG::FactoryG(): fN(FactoryN::getInstance()), fE(FactoryE::getInstance()), fP(FactoryP::getInstance()), vrx(VerifRegex::getInstance()) {}

FactoryG::~FactoryG(){}


FactoryG::Handler FactoryG::handler=FactoryG::Handler();

FactoryG& FactoryG::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new FactoryG;}
    return *handler.instance;
}

void FactoryG::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("impossible to destruct an instance which haven't been created");
    delete handler.instance;
    handler.instance=nullptr;
}


ObjectPile* FactoryG::Product (QString s) // besoin de check ici si c'est un opérateur ? a voir avec le controleur
{
    int i,j;
    if (s[0]=='\'' && s[1]=='\'') return nullptr;   // cas ou on entre l'expression '' que l'on ne veut pas traiter !
    if (s[0]=='\'' && s[s.length()-1]=='\'') // DANS UNE EXPRESSION ON NE GERE PAS LES MULTIPLICATIONS IMPLICITES tq: 4(32+4) ou 7SIN(8)
    {
        while ((i=s.indexOf(" "))!=-1) s.remove(i,1); i++; // on retire tous les espaces
        i=1;
        while (i<(s.length()-2))
        {
            if ((s[i]=='-') && (vrx.verifOperateurSimple(s.at(i-1))  || (s[i-1]==',') || (s[i-1]==')') || (s[i-1]=='(') || (s[i-1]=='\'')) )
            {
                j=i+1;
                while ( (s[j]!=',') && !vrx.verifOperateurSimple(s.at(j)) && (s[j]!=')') &&  j<s.length()-1 ) j++;
                {
                    s.insert(i, "(");
                    s.insert(j+1, ")");
                    i++;
                }

            }
            i++;
        }
        if(vrx.verifExpression(s)) return fE.ProductE(s); else return nullptr;
    }
    if (s[0]=='[' && s[s.length()-1]==']')
    {
        while ((i=s.indexOf(" "))!=-1) s.remove(i,1); // on retire tous les espaces
        /*if(vrx.verifProgramme(s)) return fE.ProductP(s); else*/ return nullptr;
    }
    if(vrx.verifNombre(s)) return fN.ProductN(s);
    return nullptr;
}



//----------------- CLASS FACTORYN ------------------------------------------------------------------------------------------------------------------------------------------------

FactoryN::~FactoryN(){}
FactoryN::FactoryN(){}

FactoryN::Handler FactoryN::handler=FactoryN::Handler();

FactoryN& FactoryN::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new FactoryN;}
    return *handler.instance;
}

void FactoryN::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("impossible to destruct an instance which haven't been created");
    delete handler.instance;
    handler.instance=nullptr;
}




Nombre* FactoryN::ProductN(QString s)
{
    int i;
    bool ok=false;
    int a=s.toInt(&ok,10);
    if(ok){Entier* e=new Entier(a); return e;};

    double b=s.toDouble(&ok);
    if(ok){Reel* re=new Reel(b); return re;};


    if (s.length()==1) return nullptr; // verif que si y'a un "$" ou un "/", il ne s'agit pas de l'operateur, si c'est l'operateur, il est seul, on sort
    if((i=s.indexOf('$'))!=-1)
    {
        Nombre* a=ProductN(s.left(i));
        Nombre* b=ProductN(s.right(s.length()-(i+1)));
        Entier* a1=dynamic_cast<Entier*>(a);
        Reel* a2=dynamic_cast<Reel*>(a);
        Rationnel* a3=dynamic_cast<Rationnel*>(a);

        Entier* b1=dynamic_cast<Entier*>(b);
        Reel* b2=dynamic_cast<Reel*>(b);
        Rationnel* b3=dynamic_cast<Rationnel*>(b);
        if ((a1!=nullptr || a2!=nullptr || a3!=nullptr) && (b1!=nullptr || b2!=nullptr || b3!=nullptr)) // safe
        {
            Complexe* c= new Complexe(*a,*b);
            return &(c->simplification());
        }
        else throw ComputerException("");
    }

    if(((i=s.indexOf('/'))!=-1))
    {
        Nombre* a=ProductN(s.left(i));
        Nombre* b=ProductN(s.right(s.length()-(i+1)));
        Entier* a1=dynamic_cast<Entier*>(a);
        Entier* b1=dynamic_cast<Entier*>(b);
        if(a1!= nullptr && b1!=nullptr) // safe
        {
            Rationnel* ra= new Rationnel(*a1,*b1);
            return &(ra->simplificationExt());
        }
    }
    return nullptr;
}


//----------------- CLASS FACTORYE ------------------------------------------------------------------------------------------------------------------------------------------------

FactoryE::~FactoryE() {}
FactoryE::FactoryE(){}

FactoryE::Handler FactoryE::handler=FactoryE::Handler();

FactoryE& FactoryE::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new FactoryE;}
    return *handler.instance;
}

void FactoryE::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("impossible to destruct an instance which haven't been created");
    delete handler.instance;
    handler.instance=nullptr;
}


Expression* FactoryE::ProductE (QString s)
{
    return new Expression(s);
}



//----------------- CLASS FACTORYP ------------------------------------------------------------------------------------------------------------------------------------------------

FactoryP::~FactoryP(){}
FactoryP::FactoryP(){}


FactoryP::Handler FactoryP::handler=FactoryP::Handler();

FactoryP& FactoryP::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new FactoryP;}
    return *handler.instance;
}

void FactoryP::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("impossible to destruct an instance which haven't been created");
    delete handler.instance;
    handler.instance=nullptr;
}

Programme* FactoryP::ProductP(QString s)
{
    return new Programme(s);
}



