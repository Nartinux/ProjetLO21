#include "operation.h"

//------------------------------------------- CLASS OPERATEURAVANCE  ---------------------------------------------------------------------------------------------------

OperateurAvance::~OperateurAvance() {}




//------------------------------------------- CLASS EVAL ---------------------------------------------------------------------------------------------------


Eval::~Eval(){}

void Eval::operation()
{
    ObjectPile& obp=expAff.top();
    getPile().pop();
    Expression* exp=dynamic_cast<Expression*>(&obp);
    if (!exp)
    {
        Programme* prg=dynamic_cast<Programme*>(&obp);
        if (prg)
        {
            int i=2;
            QString s=prg->getPrg();
            if(s.length()-2==1);    // si le programme nul : [ ] qui est accepté a la verif est entré, on ressort rien (la pile a été épurée de ce progr)
            else
            {
                if(s[2]=='[')
                {
                    while(s[i]!=']' && i<s.length()-1) i++;
                    i++;
                    QString s2=s.mid(2,i-2);
                    Programme* prg1=new Programme(s2);
                    expAff.push(*prg1);
                    operation();

                    QString s3=("["+s.right(s.length()-i));
                    Programme* prg2=new Programme(s3);
                    expAff.push(*prg2);
                    operation();
                }
                else
                {
                    while(s[i]!=' ') i++;
                    QString s2=s.mid(2,i-2);

                    if (vrx.verifNombre(s2))
                    {
                        Nombre* n=fN.ProductN(s2);
                        expAff.push(*n);
                    }
                    else if(vrx.verifOperateurSimple(s2))   
                    {
                        ObjectPile& v2=expAff.top();
                        expAff.pop();
                        ObjectPile& v1=expAff.top();
                        expAff.pop();
                        Nombre* a1=dynamic_cast<Nombre*>(&v1);
                        Nombre* a2=dynamic_cast<Nombre*>(&v2);
                        if(!a1 || !a2)                  // si c'est pas des nombres
                        {
                            expAff.push(v1);
                            expAff.push(v2);
                            expAff.setMessage("Erreur programme mal construit");
                        }
                        else
                        {
                            if (s2=="+") expAff.push(a1->operator+(*a2));
                            if (s2=="-") expAff.push(a1->operator-(*a2));
                            if (s2=="*") expAff.push(a1->operator*(*a2));
                            if (s2=="/") expAff.push(a1->operator/(*a2));
                        }
                    }
                    else if(vrx.verifOperateurAvance(s2))
                    {
                        int i=0;
                        while (i<s.length() && (s2[i]>='A') && (s2[i]<='Z')) i++;
                        FactoryOperateur* fOP=FactoryOperateur::getInstance(expAff);
                        QString opav=s2.left(i);     
                        OperateurAvance* op=fOP->ProductOP(opav);

                        int j=i+1;
                        while(i<s.length() && s2[i]!=',') i++;
                        if(i!=s.length())
                        {
                            if (vrx.verifNombre(s2.mid(j, i-j)))
                            {
                                Nombre* n=fN.ProductN(s2.mid(j, i-j));
                                expAff.push(*n);
                            }
                            if (vrx.verifAtomeExistant(s2.mid(j, i-j)))
                            {
                                Atome* atexist=atm.findAt(s2.mid(j, i-j));
                                expAff.push(*(atexist->getVal()));
                            }
                            j=i+1;
                            while(i<s2.length() && s2[i]!=')') i++;
                            if (vrx.verifNombre(s2.mid(j, i-j)))
                            {
                                Nombre* n=fN.ProductN(s2.mid(j, i-j));
                                expAff.push(*n); 
                            }
                            if (vrx.verifAtomeExistant(s2.mid(j, i-j)))
                            {
                                Atome* atexist=atm.findAt(s2.mid(j, i-j));
                                expAff.push(*(atexist->getVal()));
                            }
                        }
                        else 
                        {
                            if (vrx.verifNombre(s2.mid(j,((i-1)-j) )))
                            {
                                Nombre* n=fN.ProductN(s2.mid(j,((i-1)-j) ));
                                expAff.push(*n); 
                            }
                            if (vrx.verifAtomeExistant(s2.mid(j,((i-1)-j) )))
                            {
                                Atome* atexist=atm.findAt(s2.mid(j,((i-1)-j) ));
                                expAff.push(*(atexist->getVal()));
                            }
                        }
                        op->operation();
                    }
                    else if (vrx.verifAtomeExistant(s2))
                    {
                        Atome* atexist=atm.findAt(s2);
                        expAff.push(*(atexist->getVal()));
                    }
                    QString s3=("["+s.right(s.length()-i));
                    Programme* prg2=new Programme(s3);
                    expAff.push(*prg2);
                    operation();
                }
            }
        }
        else
        {
            expAff.push(obp);
            expAff.setMessage("Erreur ce n'est pas une expression ni un programme");
        }
    }
    else
    {
        QString s=exp->getExp();
        if(s[1]=='(' && (s[s.length()-2]==')') && s[2]=='-')
        {
            if (vrx.verifNombre(s.mid(2, s.length()-2-2)))
            {
                Nombre* n=fN.ProductN(s.mid(2, s.length()-2-2));
                expAff.push(*n);
            }
        }
        else if ( (s[1]=='(') && (s[s.length()-2]==')') )   // si y' des parentheses on les enleve
        {
            s.remove(1,1);
            s.remove(s.length()-2,1);
            Expression* express=new Expression(s);
            expAff.push(*express);
            operation();            // rappel recursif d'eval dans la fonction
        }
        else if( (s.indexOf("+")==-1) && (s.indexOf("-")==-1) && (s.indexOf("*")==-1) && (s.indexOf("/")==-1)) 
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
        else
        {
            int j=1;
            while(s[j]!='(' && j<s.length()-1)
            { 
                if (s[j]=='(' && ((s[j-1]>='A' && s[j-1]<='Z') || s[j+1]=='-'))
                {
                    while(s[j]!=')' && j<s.length()-1) j++;
                }
                j++;
            }
            if (j==s.length()-1)         // pas de parentheses
            {
                int i=1,j=0,k=1;
                while (s[i]!='*' && s[i]!='/' && i<s.length()-1 ) i++;
                if(i==s.length()-1)                     // s'il n'y a pas d'operateur prioritaire * ou /
                {
                    i=1;
                    while ((s[i]!='+' && s[i]!='-') && i<s.length()-1 ) i++;
                    QString s1=s.left(i);
                    s1+="\'";
                    Expression* express1=new Expression(s1);
                    expAff.push(*express1);
                    operation();                    // on met la partie gauche dans la pile sous forme d'exp et on l'evalue
                    QString s2="\'";
                    s2+=s.right(s.length()-(i+1));
                    Expression* express2=new Expression(s2);
                    expAff.push(*express2);
                    operation();                    // on met la partie droite dans la pile sous forme d'exp et on l'evalue

                    ObjectPile& v2=expAff.top();
                    expAff.pop();
                    ObjectPile& v1=expAff.top();
                    expAff.pop();
                    Nombre* a1=dynamic_cast<Nombre*>(&v1);
                    Nombre* a2=dynamic_cast<Nombre*>(&v2);
                    if (s[i]=='+') expAff.push(a1->operator+(*a2));
                    if (s[i]=='-') expAff.push(a1->operator-(*a2));
                }
                else
                {
                    k=i;
                    while(s[k]!='+' && s[k]!='-' && k>0) k--;
                    if(k!=0)
                    {
                        QString s0=s.left(k);
                        s0+="\'";
                        Expression* express0=new Expression(s0);
                        expAff.push(*express0);
                        operation();
                    }

                    QString s1=("\'"+s.mid(k+1,i-(k+1))+"\'");
                    Expression* express1=new Expression(s1);
                    expAff.push(*express1);
                    operation();

                    j=i;
                    while(s[j]!='+' && s[j]!='-' && j<s.length()-1) j++;

                    QString s3=("\'"+s.mid(i+1,j-(i+1))+"\'");
                    Expression* express3=new Expression(s3);
                    expAff.push(*express3);
                    operation();

                    ObjectPile& v2=expAff.top();
                    expAff.pop();
                    ObjectPile& v1=expAff.top();
                    expAff.pop();
                    Nombre* a1=dynamic_cast<Nombre*>(&v1);
                    Nombre* a2=dynamic_cast<Nombre*>(&v2);
                    if (s[i]=='*') expAff.push(a1->operator*(*a2));
                    if (s[i]=='/') expAff.push(a1->operator/(*a2));

                    if(k!=0)
                    {
                        ObjectPile& v4=expAff.top();
                        expAff.pop();
                        ObjectPile& v3=expAff.top();
                        expAff.pop();
                        Nombre* a3=dynamic_cast<Nombre*>(&v3);
                        Nombre* a4=dynamic_cast<Nombre*>(&v4);
                        if (s[k]=='+') expAff.push(a3->operator+(*a4));
                        if (s[k]=='-') expAff.push(a3->operator-(*a4));
                    }
                    if (j!=s.length()-1)
                    {
                        QString s4="\'";
                        s4+=s.right(s.length()-(j+1));
                        Expression* express4=new Expression(s4);
                        expAff.push(*express4);
                        operation();

                        ObjectPile& v6=expAff.top();
                        expAff.pop();
                        ObjectPile& v5=expAff.top();
                        expAff.pop();
                        Nombre* a5=dynamic_cast<Nombre*>(&v5);
                        Nombre* a6=dynamic_cast<Nombre*>(&v6);
                        if (s[j]=='+') expAff.push(a5->operator+(*a6));
                        if (s[j]=='-') expAff.push(a5->operator-(*a6));
                    }
                }
            }
            else    // ya des parentheses
            {
                int j=0,k=1,countpo=1, countpf=0;
                while(s[j]!='(' && j<s.length()-1)
                {
                    j++;
                    if (s[j]=='(' && ((s[j-1]>='A' && s[j-1]<='Z') || s[j+1]=='-'))
                    {
                        while(s[j]!=')' && j<s.length()-1) j++;
                    }
                }
                k=j;
                j++;
                while (countpo!=countpf) 
                {
                    if(s[j]=='(') countpo++;
                    if(s[j]==')') countpf++;
                    j++;
                }
                if (s[k-1]!='\'')
                {
                    if (s[j]=='-' || s[j]=='+' || s[k-1]=='*' || s[k-1]=='/' || j==s.length()-1)
                    {

                        QString s1=(s.left(k-1)+"\'");
                        Expression* express1=new Expression(s1);
                        expAff.push(*express1);
                        operation();

                        QString s0=("\'"+s.mid(k,j-k)+"\'");
                        Expression* express0=new Expression(s0);
                        expAff.push(*express0);
                        operation();

                        ObjectPile& v2=expAff.top();
                        expAff.pop();
                        ObjectPile& v1=expAff.top();
                        expAff.pop();
                        Nombre* a1=dynamic_cast<Nombre*>(&v1);
                        Nombre* a2=dynamic_cast<Nombre*>(&v2);
                        if (s[k-1]=='+') expAff.push(a1->operator+(*a2));
                        if (s[k-1]=='-') expAff.push(a1->operator-(*a2));
                        if (s[k-1]=='*') expAff.push(a1->operator*(*a2));
                        if (s[k-1]=='/') expAff.push(a1->operator/(*a2));

                        if(j!=s.length()-1)
                        {
                            QString s2=("\'"+s.right(s.length()-(j+1)));
                            Expression* express2=new Expression(s2);
                            expAff.push(*express2);
                            operation();

                            ObjectPile& v4=expAff.top();
                            expAff.pop();
                            ObjectPile& v3=expAff.top();
                            expAff.pop();
                            Nombre* a3=dynamic_cast<Nombre*>(&v3);
                            Nombre* a4=dynamic_cast<Nombre*>(&v4);
                            if (s[j]=='+') expAff.push(a3->operator+(*a4));
                            if (s[j]=='-') expAff.push(a3->operator-(*a4));
                            if (s[j]=='*') expAff.push(a1->operator*(*a2));
                            if (s[j]=='/') expAff.push(a1->operator/(*a2));
                        }
                    }
                }
                else if (s[j]!='\'')
                {
                    if (s[j]=='*' || s[j]=='/' || s[k-1]=='+' || s[k-1]=='-' || (k-1)==0)
                    {
                        QString s0=("\'"+s.mid(k,j-k)+"\'");
                        Expression* express0=new Expression(s0);
                        expAff.push(*express0);
                        operation();

                        QString s2=("\'"+s.right(s.length()-(j+1)));
                        Expression* express2=new Expression(s2);
                        expAff.push(*express2);
                        operation();

                        ObjectPile& v2=expAff.top();
                        expAff.pop();
                        ObjectPile& v1=expAff.top();
                        expAff.pop();
                        Nombre* a1=dynamic_cast<Nombre*>(&v1);
                        Nombre* a2=dynamic_cast<Nombre*>(&v2);
                        if (s[j]=='+') expAff.push(a1->operator+(*a2));
                        if (s[j]=='-') expAff.push(a1->operator-(*a2));
                        if (s[j]=='*') expAff.push(a1->operator*(*a2));
                        if (s[j]=='/') expAff.push(a1->operator/(*a2));

                        if((k-1)!=0)
                        {
                            QString s1=(s.left(k-1)+"\'");
                            Expression* express1=new Expression(s1);
                            expAff.push(*express1);
                            operation();

                            ObjectPile& v4=expAff.top();
                            expAff.pop();
                            ObjectPile& v3=expAff.top();
                            expAff.pop();
                            Nombre* a3=dynamic_cast<Nombre*>(&v3);
                            Nombre* a4=dynamic_cast<Nombre*>(&v4);
                            if (s[k-1]=='+') expAff.push(a3->operator+(*a4));
                            if (s[k-1]=='-') expAff.push(a3->operator-(*a4));
                        }
                    }
                }
            }
        }
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
                at->setVal(&val);                       // on met la valeur du premier objectPile recup, quoi que se soit.
                getPile().setMessage("atome réevalué");
            }
            else if (getVrx().verifAtome(s2))
            {
                Atome* a=new Atome(s2,&val);         // on cree un nouvel atome
                getAtm().addAtome(*a);          // on le met dans AtomeManager
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












