#include <algorithm>
#include "computer.h"
#include "exception.h"


/*
ExpressionManager::Handler ExpressionManager::handler=ExpressionManager::Handler();


ExpressionManager& ExpressionManager::getInstance(){
    if (handler.instance==nullptr) handler.instance=new ExpressionManager;
    return *handler.instance;
}

void ExpressionManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}
*/




/*QString  Expression::toString() const {
    return QString::number(value);
}*/


/*
void ExpressionManager::agrandissementCapacite() {
    Expression** newtab=new Expression*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Expression**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
}

Expression& ExpressionManager::addExpression(int v){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Expression(v);
    return *exps[nb-1];
}

void ExpressionManager::removeExpression(Expression& e){
    unsigned int i=0;
    while(i<nb && exps[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Expression inexistante");
    delete exps[i];
    i++;
    while(i<nb) { exps[i-1]=exps[i]; i++; }
    nb--;
}

ExpressionManager::~ExpressionManager(){
    for(unsigned int i=0; i<nb; i++) delete exps[i];
    delete[] exps;
}

Expression& Item::getExpression() const {
        if (exp==nullptr) throw ComputerException("Item : tentative d'acces a une expression inexistante");
        return *exp;
}

*/

//----------------- CLASS COMPUTER ---------------------------------


void Pile::push(Nombre &e){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb]=&e;
    nb++;
    modificationEtat();
}


void Pile::pop(){
    nb--;
    exps[nb]=nullptr;
    modificationEtat();
}

void Pile::agrandissementCapacite()
{
    Nombre** newtab=new Nombre*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Nombre**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete[] old;
}



/*
void Pile::affiche(QTextStream& f) const{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    for(int i=nbAffiche; i>0; i--) {
        if (i<=nb) f<<i<<": "<<exps[nb-i]->toString()<<"\n";
        else f<<i<<": \n";
    }
    f<<"---------------------------------------------\n";
}
*/


Pile::~Pile(){
    delete[] exps;
}



Nombre& Pile::top() const {

    if (nb==0) throw ComputerException("aucune expression sur la pile");
    return *(exps[nb-1]);
}





//----------------- CLASS FACTORY ---------------------------------


Nombre* Factory::Product(const QString s)
{
    int i;
    bool ok=false;
    int a=s.toInt(&ok,10);
    if(ok){Entier* e=new Entier(a); return e;};

    double b=s.toDouble(&ok);
    if(ok){Reel* re=new Reel(b); return re;};


    if (s.length()==1) return nullptr; // verif que si y'a un "$" ou un "/", il ne s'agit pas de l'operateur, si c'est l'operateur, il est seul, on sort
    if(((i=s.indexOf('$'))!=-1))
    {
        Nombre* a=Product(s.left(i));
        Nombre* b=Product(s.right(s.length()-(i+1)));
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
    }

    if(((i=s.indexOf('/'))!=-1))
    {
        Nombre* a=Product(s.left(i));
        Nombre* b=Product(s.right(s.length()-(i+1)));
        Entier* a1=dynamic_cast<Entier*>(a);
        Entier* b1=dynamic_cast<Entier*>(b);
        if(a1!= nullptr && b1!=nullptr) // safe
        {
            Rationnel* ra= new Rationnel(*a1,*b1);
            return &(ra->simplification());
        }
    }
    else return nullptr;
    // on ne comprend pas les atomes pour l'instant
    
}

//------------------------------------------------------------------------
// a modif !!

bool estUnOperateur(const QString s){
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*") return true;
    if (s=="/") return true;
    return false;
}

//----------------- CLASS CONTROLEUR ---------------------------------

// estUnNombre n'existe plus !!!

void Controleur::commande(const QString& c){
    Nombre* n;
    if ((n=facto.Product(c))!=nullptr)
    {
        expAff.push(*n);
    }
    else
    {
        if (estUnOperateur(c))
        {
            if (expAff.taille()>=2) // a modifier
            {
                Nombre& v1=expAff.top();
                expAff.pop();
                // pk ne pas faire les 2 en meme temps ? 
                Nombre& v2=expAff.top();
                expAff.pop();
                if (c=="+") {expAff.push(v1+v2); LibMemory::freeMem(&v1); LibMemory::freeMem(&v2);}
                if (c=="-") {expAff.push(v1-v2); LibMemory::freeMem(&v1); LibMemory::freeMem(&v2);}
                if (c=="*") {expAff.push(v1*v2); LibMemory::freeMem(&v1); LibMemory::freeMem(&v2);}
                if (c=="/") 
                {
                    Entier* ent=dynamic_cast<Entier*>(&v2);
                    if (ent==nullptr || ent->getInt()!=0) {expAff.push(v1/v2); LibMemory::freeMem(&v1); LibMemory::freeMem(&v2);}
                    else 
                    {
                        expAff.push(v2);
                        expAff.push(v1);
                        expAff.setMessage("Erreur : division par zéro");
                    }
                }
            }
            else
            {
                expAff.setMessage("Erreur : pas assez d'arguments");
            }
        }
        else expAff.setMessage("Erreur : commande inconnue");
    }
}
