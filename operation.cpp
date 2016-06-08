#include "operation.h"

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
    else
    {
        QString s=exp->getExp();
        if( (s.indexOf("+")==-1) && (s.indexOf("-")==-1) && (s.indexOf("*")==-1) && (s.indexOf("/")==-1))    // on check si y'a pas d'operateurs -> juste un atome ou un operateur Avance.
        {
            if ( (s[1]=='(') && (s[s.length()-2]==')') )   // cas ou on a 1 layer de parethèses et pas d'operations simples dedans, type: '(TOTO)'
            {
                s.remove(1,1);
                s.remove(s.length()-2,1);
                Expression* express=new Expression(s);
                expAff.push(*express);
                operation();            // rappel recursif d'eval dans la fonction
            }
            else
            {
                if(vrx.verifNombre(s.mid(1,(s.length()-2))))
                {
                    Nombre* n=fN.ProductN(s.mid(1, (s.length()-2)));
                    expAff.push(*n);
                } 
                else if (vrx.verifAtomeExistant(s.mid(1, (s.length()-2))))
                {
                    Atome* atexist=atm.findAt(s.mid(1, (s.length()-2)));
                    expAff.push(*(atexist->getVal()));
                }
                else if (vrx.verifOperateurAvanceExp(s.mid(1,(s.length()-2))))
                {
                    int i=1;
                    while (i<s.length() && (s[i]>='A') && (s[i]<='Z')) i++;

                    FactoryOperateur* fOP=FactoryOperateur::getInstance(expAff);
                    QString opav=s.mid(1, (i-1));     
                    OperateurAvance* op=fOP->ProductOP(opav);

                    int j=i+1;
                    while(i<s.length() && s[i]!=',') i++;
                    if(i!=s.length())
                    {
                        if (vrx.verifNombre(s.mid(j, i-j)))
                        {
                            Nombre* n=fN.ProductN(s.mid(j, i-j));
                            expAff.push(*n);
                        }
                        if (vrx.verifAtomeExistant(s.mid(j, i-j)))
                        {
                            Atome* atexist=atm.findAt(s.mid(j, i-j));
                            expAff.push(*(atexist->getVal()));
                        }
                        j=i+1;
                        while(i<s.length() && s[i]!=')') i++;
                        if (vrx.verifNombre(s.mid(j, i-j)))
                        {
                            Nombre* n=fN.ProductN(s.mid(j, i-j));
                            expAff.push(*n); 
                        }
                        if (vrx.verifAtomeExistant(s.mid(j, i-j)))
                        {
                            Atome* atexist=atm.findAt(s.mid(j, i-j));
                            expAff.push(*(atexist->getVal()));
                        }
                    }
                    else 
                    {
                        if (vrx.verifNombre(s.mid(j, ((i-2)-j) )))
                        {
                            Nombre* n=fN.ProductN(s.mid(j,((i-2)-j)));
                            expAff.push(*n); 
                        }
                        if (vrx.verifAtomeExistant(s.mid(j, ((i-2)-j) )))
                        {
                            Atome* atexist=atm.findAt(s.mid(j,((i-2)-j)));
                            expAff.push(*(atexist->getVal()));
                        }
                    }
                    op->operation();
                }
            }
        }
/*
        int i=1, j=1;
        bool ok=true; 
        
        while (i<(s.length()-1) && !verifOperateurSimple(s.at(i))) i++;
        if(i==(s.length()-1) || (i==s.length()-2)) return false;
        if(s[j]!='(')
        {
            if( verifNombre(s.mid(j, i-j)) || verifAtomeExistant(s.mid(j, i-j)) || verifOperateurAvanceExp(s.mid(j, i-j)))
            {
                QString s2="'";
                s2+=s.right(s.length()-(i+1));
                return verifExpression(s2);
            }
            return false;
        }
        else if( (s[j]=='(') && (s[i]=='-') && (j==i-1)) // cas type: (-987)
        {
            j++;
            while(s[i]!=')' && i<s.length()) i++;
            if (i==s.length()) return false; // pas de fin de parenthèse !! -> illegal
            QString s2=s.mid(j,i-j);
            ok=verifNombre(s2);
            i++;
            if (i==s.length()-1 && ok) return true;
            s2="'";
            s2+=s.right(s.length()-(i+1));
            if(ok) return verifExpression(s2); else return false;
        }
        else if (s[j]=='(' && s[i-1]==')')   // cas ou on a 1 layer de parethèses et pas d'operations simples dedans, type: '44*(X)/7'
        {
            QString s2="'";
            s2+=s.mid(j+1,i-2-(j+1));
            s2+="'";
            ok=verifExpression(s2); // on rappelle la fonction qui s'arretera au premier if
            if (i==s.length()-1 && ok) return true;
            s2="'";
            s2+=s.right(s.length()-(i+1));
            if(ok) return verifExpression(s2); else return false;
        }
        else if (s[j]=='(' && s[i-1]!=')') // cas d'operations dans les paretheses
        {
            int countpo=1; // nb de parentheses ouvrantes decouvertes jusqu'alors
            int countpf=0; // nb de parentheses fermantes decouvertes jusqu'alors
            i=j+1;
            while(countpf!=countpo && i<s.length())
            {
                if (s[i]==')') countpf++;
                if (s[i]=='(') countpo++;
                i++;
            }
            if (i==s.length() || (i==s.length()-3)) return false; // pas de fin de parenthèse ou un unique caractere apresla fin des parentheses qui est juste avant le ' final
            else
            {
                QString s2="'";
                s2+=s.mid(j+1, (i-1)-(j+1));
                s2+="'";
                ok=verifExpression(s2);
                if (i==s.length()-1 && ok) return true;
                s2="'";
                s2+=s.right(s.length()-(i+1));
                if(ok) return verifExpression(s2); else return false;
            }
        }
        return false;*/
    }   
}


//------------------------------------------- CLASS STO ---------------------------------------------------------------------------------------------------


Sto::~Sto(){}


void Sto::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& val=getPile().top();
        getPile().pop();

        ObjectPile& exp=getPile().top();
        getPile().pop();
        Expression* expat=dynamic_cast<Expression*>(&exp);
        if (expat==nullptr)
        {
            getPile().push(exp);
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
                Atome* at=getAtm().findAt(s2);  // on cherche l'atome dans l'atome manager
                //delete at.getVal();             // on detruit l'ancienne valeur
                ObjectPile* obp=at->getVal();
                obp=&val;                       // on met la valeur du premier objectPile recup, quoi que se soit.
                //delete expat;                   // on detruit l'expression represantant l'atome
                getPile().setMessage("atome réevalué");
            }
            else if (getVrx().verifAtome(s2))
            {
                Atome* a=new Atome(s2,&val);         // on cree un nouvel atome
                getAtm().addAtome(*a);          // on le met dans AtomeManager
                //delete expat;                   // on detruit l'expression represantant l'atome
                getPile().setMessage("atome crée");
            }
            else    // l'expression ne represente pas un atome
            {
                getPile().push(*expat);
                getPile().setMessage("l'expression n'est pas un atome");
                getPile().push(val);            // on remet aussi l'objet qui etait a mettre dans l'atome
            }
        }
    }else expAff.setMessage("necessite deux arguments");
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
        getPile().push(exp);
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
            //Atome* at=getAtm().findAt(s2);  // on cherche l'atome dans l'atome manager
            getAtm().removeAtome(s2);       // on detruit l'atome via l'atomeManager, le destructeur de l'atome s'occupe de détruire son objPile
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
