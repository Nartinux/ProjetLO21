#include "factory.h"


//----------------- CLASS FACTORYG ------------------------------------------------------------------------------------------------------------------------------------------------

FactoryG::FactoryG(): fA(FactoryA::getInstance()), fN(FactoryN::getInstance()), fE(FactoryE::getInstance()), fP(FactoryP::getInstance()), vrx(*(new VerifRegex())) {}

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
    int i;
    if (s[0]=='\'' && s[s.length()-1]=='\'') // DANS UNE EXPRESSION ON NE GERE PAS LES MULTIPLICATIONS IMPLICITES tq: 4(32+4) ou 7SIN(8)
    {
        while ((i=s.indexOf(" "))!=-1) {s.remove(i,1); i++;} // on retire tous les espaces
        i=1;
        while (i<(s.length()-2)) // length -2 pour ne pas a vaoir a gerer des cas comme '44+7-' qui est illégale sinon on lance un traitement pour le - à la fin qui va echouer.
        {
            if ( (s[i]=='-') && (s[i-1]=='(' /*&& s[]*/)) // cas type: OPE(-3,5) on veut -> OPE((-3),5)
            {
                int v=i+1, f=i+1;
                while ( ( (s[v]!=',') || (!vrx.verifOperateurSimple(s[v]))) && v<s.length()) v++;
                while (s[f]!=')' && f<s.length() ) f++; // on verifie qui ne s'agit pas deja de OPE((-3),5)
                if (v<f)    // dans ce cas insertion des parentheses
                {
                    s.insert(i,"(");
                    s.insert(v, ")");
                }
            }
            if ( (s[i]=='-') && (vrx.verifOperateurSimple(s.at(i-1))  || (s[i-1]==',')) ) // si y'a un - et avant, on trouve un operateur simple, une virgule
            {
                s.insert(i,"(");
                i=+2;    // on incrémente de 2 pour sauter le - qui s'est décalé à i+1 du coup.
                while((i<s.length()) && !vrx.verifOperateurSimple(s[i])) i++;
                s.insert(i+1, ")");
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
    if (vrx.verifAtomeExistant(s)) return &(vrx.getAtm().findAt(s));   // pour les atomes, verifier qu'il y a bien quelque chose dans la pile !!!
    if(vrx.verifAtome(s)) return fA.ProductA(s);
    if(vrx.verifNombre(s)) return fN.ProductN(s); // que ca soit un nombre ou non c'est la methode ProductN qui fera la discrimiation
    return nullptr;
}



//----------------- CLASS FACTORYA ------------------------------------------------------------------------------------------------------------------------------------------------

FactoryA::FactoryA(): Atm(AtomeManager::getInstance()) {}

FactoryA::~FactoryA() {}




FactoryA::Handler FactoryA::handler=FactoryA::Handler();

FactoryA& FactoryA::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new FactoryA;}
    return *handler.instance;
}

void FactoryA::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("impossible to destruct an instance which haven't been created");
    delete handler.instance;
    handler.instance=nullptr;
}


Atome* FactoryA::ProductA(QString s)
{
    VerifRegex *vrx = new VerifRegex();
    if (vrx->verifOperateurSimple(s)) return nullptr; //Pour pas qu'un operateur comme "DIV", "MOD".. soient considérés comme des atomes
    Atome* at=new Atome(s);
    // comment faire pour lui affecter la valeur ? ici ou dans le controleur ? ou ailleurs ?
    Atm.addAtome(*at);
    return at;
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
