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
            else {
                expAff.push(v1);
                expAff.push(v2);
                expAff.setMessage("Erreur : le modulo n'est définis que pour les entiers");
            }
        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : le modulo n'est définis que pour des nombres");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}



// ------------------------------------------------------ CLASS DIVEUCLI ------------------------------------------------------------------------

Diveucli::~Diveucli(){}

void Diveucli::operation()
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
                Entier* res =new Entier(ent1->getInt()/ent2->getInt());
                expAff.push(*res);
                expAff.setMessage("Modulo effectué");
            }
            else {
                expAff.push(v1);
                expAff.push(v2);
                expAff.setMessage("Erreur : la division euclidienne n'est définis que pour les entiers");
            }
        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : la division euclidienne n'est définis que pour des nombres entiers");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}

// ------------------------------------------------------ CLASS NUM ------------------------------------------------------------------------

Numerateur::~Numerateur(){}

void Numerateur::operation()
{
    if (expAff.taille()>=1)
    {
        ObjectPile& v=expAff.top();
        expAff.pop();
        Nombre* a=dynamic_cast<Nombre*>(&v);
        if(a)
        {
            Rationnel* rat=dynamic_cast<Rationnel*>(a);
            if (rat)
            {
                Entier* res = &rat->getNum();
                expAff.push(*res);
                expAff.setMessage("Num effectué");
            }
            else {
                expAff.push(v);
                expAff.setMessage("Erreur : la fonction num n'est définis que pour les rationnels");
            }
        }
        else {
            expAff.push(v);
            expAff.setMessage("Erreur : la fonction num n'est définis que pour des nombres rationnels");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}

// ------------------------------------------------------ CLASS DEN ------------------------------------------------------------------------

Denominateur::~Denominateur(){}

void Denominateur::operation()
{
    if (expAff.taille()>=1)
    {
        ObjectPile& v=expAff.top();
        expAff.pop();
        Nombre* a=dynamic_cast<Nombre*>(&v);
        if(a)
        {
            Rationnel* rat=dynamic_cast<Rationnel*>(a);
            if (rat)
            {
                Entier* res = &rat->getDen();
                expAff.push(*res);
                expAff.setMessage("Den effectué");
            }
            else {
                expAff.push(v);
                expAff.setMessage("Erreur : la fonction DEN n'est définis que pour les rationnels");
            }
        }
        else {
            expAff.push(v);
            expAff.setMessage("Erreur : la fonction DEN n'est définis que pour des nombres rationnels");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}


// ------------------------------------------------------ CLASS $ ------------------------------------------------------------------------

Operateur$::~Operateur$(){}

void Operateur$::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* b1=dynamic_cast<Nombre*>(&v2);
        if(a1 && b1)
        {
            Nombre* a;
            Nombre* b;
            Entier* a2=dynamic_cast<Entier*>(a1);
            if(a2!=nullptr) a = a2;
            Entier* b2=dynamic_cast<Entier*>(b1);
            if(b2!=nullptr) b = b2;
            Rationnel* a3=dynamic_cast<Rationnel*>(a1);
            if(a3!=nullptr) a = a3;
            Rationnel* b3=dynamic_cast<Rationnel*>(b1);
            if(b3!=nullptr) b = b3;
            Reel* a4=dynamic_cast<Reel*>(a1);
            if(a4!=nullptr) a = a4;
            Reel* b4=dynamic_cast<Reel*>(b1);
            if(b4!=nullptr) b = b4;
            Complexe* a5=dynamic_cast<Complexe*>(a1);
            if(a5!=nullptr) a = a5;
            Complexe* b5=dynamic_cast<Complexe*>(b1);
            if(b5!=nullptr) b = b5;
            Complexe* res =new Complexe(*a,*b);
            expAff.push(res->simplification());
            expAff.setMessage("Complexe construis");
        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : la construction d'un complexe n'est définis que pour des nombres");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}

// ------------------------------------------------------ CLASS RE ------------------------------------------------------------------------

PartieReelle::~PartieReelle(){}

void PartieReelle::operation()
{
    if (expAff.taille()>=1)
    {
        ObjectPile& v=expAff.top();
        expAff.pop();
        Nombre* a=dynamic_cast<Nombre*>(&v);
        if(a)
        {
            Complexe* rat=dynamic_cast<Complexe*>(a);
            if (rat)
            {
                Nombre* res = &rat->getRe();
                expAff.push(*res);
                expAff.setMessage("RE effectué");
            }
            else {
                expAff.push(v);
                expAff.setMessage("Erreur : la fonction RE n'est définis que pour les complexe");
            }
        }
        else {
            expAff.push(v);
            expAff.setMessage("Erreur : la fonction RE n'est définis que pour des nombres");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}

// ------------------------------------------------------ CLASS IM ------------------------------------------------------------------------

PartieIm::~PartieIm(){}

void PartieIm::operation()
{
    if (expAff.taille()>=1)
    {
        ObjectPile& v=expAff.top();
        expAff.pop();
        Nombre* a=dynamic_cast<Nombre*>(&v);
        if(a)
        {
            Complexe* rat=dynamic_cast<Complexe*>(a);
            if (rat)
            {
                Nombre* res = &rat->getIm();
                expAff.push(*res);
                expAff.setMessage("Im effectué");
            }
            else {
                expAff.push(v);
                expAff.setMessage("Erreur : la fonction IM n'est définis que pour les complexe");
            }
        }
        else {
            expAff.push(v);
            expAff.setMessage("Erreur : la fonction IM n'est définis que pour des nombres");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}

// ------------------------------------------------------ CLASS = ------------------------------------------------------------------------

Egal::~Egal(){}

void Egal::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* b1=dynamic_cast<Nombre*>(&v2);
        if(a1 && b1)
        {
            Nombre* a;
            Nombre* b;
            Entier* a2=dynamic_cast<Entier*>(a1);
            if(a2!=nullptr) {
                Entier* b2=dynamic_cast<Entier*>(b1);
                if(b2!=nullptr) {
                    if (a2->getInt()==b2->getInt()){                                                //entier == entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Rationnel* a3=dynamic_cast<Rationnel*>(a1);
            if(a3!=nullptr) {
                Rationnel* b3=dynamic_cast<Rationnel*>(b1);
                if(b3!=nullptr) {                                                                   // rationnel == rationnel
                    if (a3->getDen().getInt()==b3->getDen().getInt() && a3->getNum().getInt()==b3->getNum().getInt()){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* c3=dynamic_cast<Reel*>(b1);
                if(c3!=nullptr) {
                    Reel* d3 = new Reel(a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1.0));
                    if (d3->getRel()==c3->getRel()){                                                //rationnel == reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                 }
            }
            Reel* a4=dynamic_cast<Reel*>(a1);
            if(a4!=nullptr) {
                Reel* b4=dynamic_cast<Reel*>(b1);
                if(b4!=nullptr) {
                    if (a4->getRel()==b4->getRel()){                                                // reel == reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c4=dynamic_cast<Rationnel*>(b1);
                if(c4!=nullptr) {
                    Reel* d4 = new Reel(c4->getNum().getInt()/(c4->getDen().getInt()+1.0-1.0));
                    if (a4->getRel()==d4->getRel()){                                                //reel == rationnel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                 }
            }
            Complexe* a5=dynamic_cast<Complexe*>(a1);                                               //complexe == complexe
            if(a5!=nullptr) {
                Complexe* b5=dynamic_cast<Complexe*>(b1);
                if(b5!=nullptr) {
                        expAff.push(a5->getIm());   //on réinjecte les 2 parties imaginaires dans la pile
                        expAff.push(b5->getIm());
                        Egal* recursifIm = new Egal(expAff);
                        recursifIm->operation();    //on test l'operation== sur les imaginaires
                        expAff.push(a5->getRe());   //on réinjecte les 2 parties reelles dans la pile
                        expAff.push(b5->getRe());
                        Egal* recursifRe = new Egal(expAff);
                        recursifRe->operation();    //on test l'operation== sur les imaginaires
                        ObjectPile& testIm=expAff.top();
                        expAff.pop();
                        ObjectPile& testRe=expAff.top();
                        expAff.pop();
                        Entier* testIm2=dynamic_cast<Entier*>(&testIm);
                        Entier* testRe2=dynamic_cast<Entier*>(&testRe);
                        if (testIm2->getInt() && testRe2->getInt()){    //on regarde si les 2 tests ont retournés VRAI
                            expAff.push(*(new Entier(1)));
                            expAff.setMessage("VRAI");return;
                        }
                }
            }
            expAff.push(*(new Entier(0)));
            expAff.setMessage("FAUX");

        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : les opérateurs logiques ne sont définis que pour des nombres");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}

// ------------------------------------------------------ CLASS != ------------------------------------------------------------------------

Different::~Different(){}

void Different::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* b1=dynamic_cast<Nombre*>(&v2);
        if(a1 && b1)
        {
            Nombre* a;
            Nombre* b;
            Entier* a2=dynamic_cast<Entier*>(a1);
            if(a2!=nullptr) {
                Entier* b2=dynamic_cast<Entier*>(b1);
                if(b2!=nullptr) {
                    if (a2->getInt()==b2->getInt()){                                                //entier == entier
                        expAff.push(*(new Entier(0)));
                        expAff.setMessage("Faux");return;
                    }
                }
            }
            Rationnel* a3=dynamic_cast<Rationnel*>(a1);
            if(a3!=nullptr) {
                Rationnel* b3=dynamic_cast<Rationnel*>(b1);
                if(b3!=nullptr) {                                                                   // rationnel == rationnel
                    if (a3->getDen().getInt()==b3->getDen().getInt() && a3->getNum().getInt()==b3->getNum().getInt()){
                        expAff.push(*(new Entier(0)));
                        expAff.setMessage("Faux");return;
                    }
                }
                Reel* c3=dynamic_cast<Reel*>(b1);
                if(c3!=nullptr) {
                    Reel* d3 = new Reel(a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1.0));
                    if (d3->getRel()==c3->getRel()){                                                //rationnel == reel
                        expAff.push(*(new Entier(0)));
                        expAff.setMessage("Faux");return;
                    }
                 }
            }
            Reel* a4=dynamic_cast<Reel*>(a1);
            if(a4!=nullptr) {
                Reel* b4=dynamic_cast<Reel*>(b1);
                if(b4!=nullptr) {
                    if (a4->getRel()==b4->getRel()){                                                // reel == reel
                        expAff.push(*(new Entier(0)));
                        expAff.setMessage("Faux");return;
                    }
                }
                Rationnel* c4=dynamic_cast<Rationnel*>(b1);
                if(c4!=nullptr) {
                    Reel* d4 = new Reel(c4->getNum().getInt()/(c4->getDen().getInt()+1.0-1.0));
                    if (a4->getRel()==d4->getRel()){                                                //reel == rationnel
                        expAff.push(*(new Entier(0)));
                        expAff.setMessage("Faux");return;
                    }
                 }
            }
            Complexe* a5=dynamic_cast<Complexe*>(a1);                                               //complexe == complexe
            if(a5!=nullptr) {
                Complexe* b5=dynamic_cast<Complexe*>(b1);
                if(b5!=nullptr) {
                        expAff.push(a5->getIm());   //on réinjecte les 2 parties imaginaires dans la pile
                        expAff.push(b5->getIm());
                        Egal* recursifIm = new Egal(expAff);
                        recursifIm->operation();    //on test l'operation!= sur les imaginaires
                        expAff.push(a5->getRe());   //on réinjecte les 2 parties reelles dans la pile
                        expAff.push(b5->getRe());
                        Egal* recursifRe = new Egal(expAff);
                        recursifRe->operation();    //on test l'operation!= sur les imaginaires
                        ObjectPile& testIm=expAff.top();
                        expAff.pop();
                        ObjectPile& testRe=expAff.top();
                        expAff.pop();
                        Entier* testIm2=dynamic_cast<Entier*>(&testIm);
                        Entier* testRe2=dynamic_cast<Entier*>(&testRe);
                        if (testIm2->getInt() && testRe2->getInt()){    //on regarde si les 2 tests ont retournés VRAI
                            expAff.push(*(new Entier(0)));
                            expAff.setMessage("FAUX");return;
                        }
                }
            }
            expAff.push(*(new Entier(0)));
            expAff.setMessage("VRAI");

        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : les opérateurs logiques ne sont définis que pour des nombres");
        }
    }
    else expAff.setMessage("Erreur : Pas assez d'arguments");
}

// ------------------------------------------------------ CLASS >= ------------------------------------------------------------------------

SupOuEgal::~SupOuEgal(){}

void SupOuEgal::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* b1=dynamic_cast<Nombre*>(&v2);
        if(a1 && b1)
        {
            Nombre* a;
            Nombre* b;
            Entier* a2=dynamic_cast<Entier*>(a1);
            if(a2!=nullptr) {
                Entier* b2=dynamic_cast<Entier*>(b1);
                if(b2!=nullptr) {
                    if (a2->getInt()>=b2->getInt()){                                                //entier >= entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c2=dynamic_cast<Rationnel*>(b1);
                if(c2!=nullptr) {                                                                   // entier >= rationnel
                    if (a2->getInt() >= c2->getNum().getInt()/(c2->getNum().getInt())+1.0-1){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* d2=dynamic_cast<Reel*>(b1);
                if(d2!=nullptr) {
                    if (a2->getInt() >= d2->getRel()){                                                //entier >= reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                 }
            }
            Rationnel* a3=dynamic_cast<Rationnel*>(a1);
            if(a3!=nullptr) {
                Rationnel* b3=dynamic_cast<Rationnel*>(b1);
                if(b3!=nullptr) {                                                                   // rationnel >= rationnel
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) >= b3->getNum().getInt()/(b3->getDen().getInt())+1.0-1){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* c3=dynamic_cast<Reel*>(b1);
                if(c3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) >= c3->getRel()){       //rationnel >= reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d3=dynamic_cast<Entier*>(b1);
                if(d3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) >= d3->getInt()){        //rationnel >= entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Reel* a4=dynamic_cast<Reel*>(a1);
            if(a4!=nullptr) {
                Reel* b4=dynamic_cast<Reel*>(b1);
                if(b4!=nullptr) {
                    if (a4->getRel()>=b4->getRel()){                                                // reel >= reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c4=dynamic_cast<Rationnel*>(b1);
                if(c4!=nullptr) {
                    if (a4->getRel() >= c4->getNum().getInt()/(c4->getDen().getInt()+1.0-1.0)){     //reel >= rationnel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d4=dynamic_cast<Entier*>(b1);
                if(d4!=nullptr) {
                    if (a4->getRel() >= d4->getInt()){                                              //reel >= entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Complexe* a5=dynamic_cast<Complexe*>(a1);                                               //complexe >= complexe
            if(a5!=nullptr) {
                Complexe* b5=dynamic_cast<Complexe*>(b1);
                if(b5!=nullptr) {
                    expAff.push(a5->getIm());   //on réinjecte les 2 parties imaginaires dans la pile
                    expAff.push(b5->getIm());
                    SupOuEgal* recursifIm = new SupOuEgal(expAff);
                    recursifIm->operation();    //on test l'operation== sur les imaginaires
                    expAff.push(a5->getRe());   //on réinjecte les 2 parties reelles dans la pile
                    expAff.push(b5->getRe());
                    SupOuEgal* recursifRe = new SupOuEgal(expAff);
                    recursifRe->operation();    //on test l'operation== sur les imaginaires
                    ObjectPile& testIm=expAff.top();
                    expAff.pop();
                    ObjectPile& testRe=expAff.top();
                    expAff.pop();
                    Entier* testIm2=dynamic_cast<Entier*>(&testIm);
                    Entier* testRe2=dynamic_cast<Entier*>(&testRe);
                    if (testIm2->getInt() && testRe2->getInt()){    //on regarde si les 2 tests ont retournés VRAI
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("VRAI");return;
                    }
                }
            }
            expAff.push(*(new Entier(0)));
            expAff.setMessage("FAUX");

        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : les opérateurs logiques ne sont définis que pour des nombres");
        }
    }
}

// ------------------------------------------------------ CLASS =< ------------------------------------------------------------------------

InfOuEgal::~InfOuEgal(){}

void InfOuEgal::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* b1=dynamic_cast<Nombre*>(&v2);
        if(a1 && b1)
        {
            Nombre* a;
            Nombre* b;
            Entier* a2=dynamic_cast<Entier*>(a1);
            if(a2!=nullptr) {
                Entier* b2=dynamic_cast<Entier*>(b1);
                if(b2!=nullptr) {
                    if (a2->getInt() <= b2->getInt()){                                                //entier <= entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c2=dynamic_cast<Rationnel*>(b1);
                if(c2!=nullptr) {                                                                   // entier <= rationnel
                    if (a2->getInt() <= c2->getNum().getInt()/(c2->getNum().getInt())+1.0-1){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* d2=dynamic_cast<Reel*>(b1);
                if(d2!=nullptr) {
                    if (a2->getInt() <= d2->getRel()){                                                //entier <= reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                 }
            }
            Rationnel* a3=dynamic_cast<Rationnel*>(a1);
            if(a3!=nullptr) {
                Rationnel* b3=dynamic_cast<Rationnel*>(b1);
                if(b3!=nullptr) {                                                                   // rationnel <= rationnel
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) <= b3->getNum().getInt()/(b3->getDen().getInt())+1.0-1){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* c3=dynamic_cast<Reel*>(b1);
                if(c3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) <= c3->getRel()){       //rationnel <= reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d3=dynamic_cast<Entier*>(b1);
                if(d3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) <= d3->getInt()){        //rationnel <= entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Reel* a4=dynamic_cast<Reel*>(a1);
            if(a4!=nullptr) {
                Reel* b4=dynamic_cast<Reel*>(b1);
                if(b4!=nullptr) {
                    if (a4->getRel()<=b4->getRel()){                                                // reel <= reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c4=dynamic_cast<Rationnel*>(b1);
                if(c4!=nullptr) {
                    if (a4->getRel() <= c4->getNum().getInt()/(c4->getDen().getInt()+1.0-1.0)){     //reel <= rationnel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d4=dynamic_cast<Entier*>(b1);
                if(d4!=nullptr) {
                    if (a4->getRel() <= d4->getInt()){                                              //reel <= entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Complexe* a5=dynamic_cast<Complexe*>(a1);                                               //complexe <= complexe
            if(a5!=nullptr) {
                Complexe* b5=dynamic_cast<Complexe*>(b1);
                if(b5!=nullptr) {
                        expAff.push(a5->getIm());   //on réinjecte les 2 parties imaginaires dans la pile
                        expAff.push(b5->getIm());
                        InfOuEgal* recursifIm = new InfOuEgal(expAff);
                        recursifIm->operation();    //on test l'operation== sur les imaginaires
                        expAff.push(a5->getRe());   //on réinjecte les 2 parties reelles dans la pile
                        expAff.push(b5->getRe());
                        InfOuEgal* recursifRe = new InfOuEgal(expAff);
                        recursifRe->operation();    //on test l'operation== sur les imaginaires
                        ObjectPile& testIm=expAff.top();
                        expAff.pop();
                        ObjectPile& testRe=expAff.top();
                        expAff.pop();
                        Entier* testIm2=dynamic_cast<Entier*>(&testIm);
                        Entier* testRe2=dynamic_cast<Entier*>(&testRe);
                        if (testIm2->getInt() && testRe2->getInt()){    //on regarde si les 2 tests ont retournés VRAI
                            expAff.push(*(new Entier(1)));
                            expAff.setMessage("VRAI");return;
                        }
                }
            }
            expAff.push(*(new Entier(0)));
            expAff.setMessage("FAUX");

        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : les opérateurs logiques ne sont définis que pour des nombres");
        }
    }
}

// ------------------------------------------------------ CLASS > ------------------------------------------------------------------------

Sup::~Sup(){}

void Sup::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* b1=dynamic_cast<Nombre*>(&v2);
        if(a1 && b1)
        {
            Nombre* a;
            Nombre* b;
            Entier* a2=dynamic_cast<Entier*>(a1);
            if(a2!=nullptr) {
                Entier* b2=dynamic_cast<Entier*>(b1);
                if(b2!=nullptr) {
                    if (a2->getInt()>b2->getInt()){                                                //entier > entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c2=dynamic_cast<Rationnel*>(b1);
                if(c2!=nullptr) {                                                                   // entier > rationnel
                    if (a2->getInt() > c2->getNum().getInt()/(c2->getNum().getInt())+1.0-1){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* d2=dynamic_cast<Reel*>(b1);
                if(d2!=nullptr) {
                    if (a2->getInt() > d2->getRel()){                                                //entier > reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                 }
            }
            Rationnel* a3=dynamic_cast<Rationnel*>(a1);
            if(a3!=nullptr) {
                Rationnel* b3=dynamic_cast<Rationnel*>(b1);
                if(b3!=nullptr) {                                                                   // rationnel > rationnel
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) > b3->getNum().getInt()/(b3->getDen().getInt())+1.0-1
                        && a3->getDen().getInt()!=b3->getDen().getInt() && a3->getNum().getInt()!=b3->getNum().getInt()){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* c3=dynamic_cast<Reel*>(b1);
                if(c3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) > c3->getRel()){       //rationnel > reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d3=dynamic_cast<Entier*>(b1);
                if(d3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) > d3->getInt()){        //rationnel > entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Reel* a4=dynamic_cast<Reel*>(a1);
            if(a4!=nullptr) {
                Reel* b4=dynamic_cast<Reel*>(b1);
                if(b4!=nullptr) {
                    if (a4->getRel()>b4->getRel()){                                                // reel > reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c4=dynamic_cast<Rationnel*>(b1);
                if(c4!=nullptr) {
                    if (a4->getRel() > c4->getNum().getInt()/(c4->getDen().getInt()+1.0-1.0)){     //reel > rationnel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d4=dynamic_cast<Entier*>(b1);
                if(d4!=nullptr) {
                    if (a4->getRel() > d4->getInt()){                                              //reel > entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Complexe* a5=dynamic_cast<Complexe*>(a1);                                               //complexe > complexe
            if(a5!=nullptr) {
                Complexe* b5=dynamic_cast<Complexe*>(b1);
                if(b5!=nullptr) {
                    expAff.push(a5->getIm());   //on réinjecte les 2 parties imaginaires dans la pile
                    expAff.push(b5->getIm());
                    Sup* recursifIm = new Sup(expAff);
                    recursifIm->operation();    //on test l'operation== sur les imaginaires
                    expAff.push(a5->getRe());   //on réinjecte les 2 parties reelles dans la pile
                    expAff.push(b5->getRe());
                    Sup* recursifRe = new Sup(expAff);
                    recursifRe->operation();    //on test l'operation== sur les imaginaires
                    ObjectPile& testIm=expAff.top();
                    expAff.pop();
                    ObjectPile& testRe=expAff.top();
                    expAff.pop();
                    Entier* testIm2=dynamic_cast<Entier*>(&testIm);
                    Entier* testRe2=dynamic_cast<Entier*>(&testRe);
                    if (testIm2->getInt() && testRe2->getInt()){    //on regarde si les 2 tests ont retournés VRAI
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("VRAI");return;
                    }
                }
            }
            expAff.push(*(new Entier(0)));
            expAff.setMessage("FAUX");

        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : les opérateurs logiques ne sont définis que pour des nombres");
        }
    }
}

// ------------------------------------------------------ CLASS < ------------------------------------------------------------------------

Inf::~Inf(){}

void Inf::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& v2=expAff.top();
        expAff.pop();
        ObjectPile& v1=expAff.top();
        expAff.pop();
        Nombre* a1=dynamic_cast<Nombre*>(&v1);
        Nombre* b1=dynamic_cast<Nombre*>(&v2);
        if(a1 && b1)
        {
            Nombre* a;
            Nombre* b;
            Entier* a2=dynamic_cast<Entier*>(a1);
            if(a2!=nullptr) {
                Entier* b2=dynamic_cast<Entier*>(b1);
                if(b2!=nullptr) {
                    if (a2->getInt() < b2->getInt()){                                                //entier < entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c2=dynamic_cast<Rationnel*>(b1);
                if(c2!=nullptr) {                                                                   // entier < rationnel
                    if (a2->getInt() < c2->getNum().getInt()/(c2->getNum().getInt())+1.0-1){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* d2=dynamic_cast<Reel*>(b1);
                if(d2!=nullptr) {
                    if (a2->getInt() < d2->getRel()){                                                //entier < reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                 }
            }
            Rationnel* a3=dynamic_cast<Rationnel*>(a1);
            if(a3!=nullptr) {
                Rationnel* b3=dynamic_cast<Rationnel*>(b1);
                if(b3!=nullptr) {                                                                   // rationnel < rationnel
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) > b3->getNum().getInt()/(b3->getDen().getInt())+1.0-1
                        && a3->getDen().getInt()!=b3->getDen().getInt() && a3->getNum().getInt()!=b3->getNum().getInt()){
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Reel* c3=dynamic_cast<Reel*>(b1);
                if(c3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) < c3->getRel()){       //rationnel < reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d3=dynamic_cast<Entier*>(b1);
                if(d3!=nullptr) {
                    if (a3->getNum().getInt()/(a3->getDen().getInt()+1.0-1) < d3->getInt()){        //rationnel < entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Reel* a4=dynamic_cast<Reel*>(a1);
            if(a4!=nullptr) {
                Reel* b4=dynamic_cast<Reel*>(b1);
                if(b4!=nullptr) {
                    if (a4->getRel()<b4->getRel()){                                                // reel < reel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Rationnel* c4=dynamic_cast<Rationnel*>(b1);
                if(c4!=nullptr) {
                    if (a4->getRel() < c4->getNum().getInt()/(c4->getDen().getInt()+1.0-1.0)){     //reel < rationnel
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
                Entier* d4=dynamic_cast<Entier*>(b1);
                if(d4!=nullptr) {
                    if (a4->getRel() < d4->getInt()){                                              //reel < entier
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("Vrai");return;
                    }
                }
            }
            Complexe* a5=dynamic_cast<Complexe*>(a1);                                              //complexe < complexe
            if(a5!=nullptr) {
                Complexe* b5=dynamic_cast<Complexe*>(b1);
                if(b5!=nullptr) {
                    expAff.push(a5->getIm());   //on réinjecte les 2 parties imaginaires dans la pile
                    expAff.push(b5->getIm());
                    Inf* recursifIm = new Inf(expAff);
                    recursifIm->operation();    //on test l'operation== sur les imaginaires
                    expAff.push(a5->getRe());   //on réinjecte les 2 parties reelles dans la pile
                    expAff.push(b5->getRe());
                    Inf* recursifRe = new Inf(expAff);
                    recursifRe->operation();    //on test l'operation== sur les imaginaires
                    ObjectPile& testIm=expAff.top();
                    expAff.pop();
                    ObjectPile& testRe=expAff.top();
                    expAff.pop();
                    Entier* testIm2=dynamic_cast<Entier*>(&testIm);
                    Entier* testRe2=dynamic_cast<Entier*>(&testRe);
                    if (testIm2->getInt() && testRe2->getInt()){    //on regarde si les 2 tests ont retournés VRAI
                        expAff.push(*(new Entier(1)));
                        expAff.setMessage("VRAI");return;
                    }
                }
            }
            expAff.push(*(new Entier(0)));
            expAff.setMessage("FAUX");
        }
        else {
            expAff.push(v1);
            expAff.push(v2);
            expAff.setMessage("Erreur : les opérateurs logiques ne sont définis que pour des nombres");
        }
    }
}

// ------------------------------------------------------ CLASS DROP ------------------------------------------------------------------------

Drop::~Drop(){}

void Drop::operation()
{
    if (expAff.taille()>=1)
    {
        ObjectPile& obp=expAff.top();
        expAff.pop();
        delete &obp;
    }
    else expAff.setMessage("necessite un argument dans la pile"); 
}


// ------------------------------------------------------ CLASS DUP ------------------------------------------------------------------------

Dup::~Dup(){}

void Dup::operation()
{
    if (expAff.taille()>=1)
    {
        ObjectPile& obp=expAff.top();
        expAff.pop();
        expAff.push(obp);
        expAff.push(obp);
    }
    else expAff.setMessage("necessite un argument dans la pile"); 
}


// ------------------------------------------------------ CLASS SWAP ------------------------------------------------------------------------

Swap::~Swap(){}

void Swap::operation()
{
    if (expAff.taille()>=2)
    {
        ObjectPile& obp1=expAff.top();
        expAff.pop();
        ObjectPile& obp2=expAff.top();
        expAff.pop();
        expAff.push(obp1);
        expAff.push(obp2);
    }
    else expAff.setMessage("necessite 2 arguments dans la pile"); 
}


// ------------------------------------------------------ CLASS CLEAR ------------------------------------------------------------------------

Clear::~Clear(){}

void Clear::operation()
{
    if (expAff.taille()==0) expAff.setMessage("no need for it"); 
    else
    {
        while(!expAff.estVide())
        {
            ObjectPile& obp=expAff.top();
            expAff.pop();
            delete &obp;
        }
    }
}


// ------------------------------------------------------ CLASS UNDO ------------------------------------------------------------------------

Undo::~Undo(){}

void Undo::operation()
{
    //pm.restore(&expAff);
    expAff.setMessage("l'operation ne fonctionne pas");
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
        else if (s=="DIV")
        {
            return new Diveucli(pil);
        }
        else if (s=="NUM")
        {
            return new Numerateur(pil);
        }
        else if (s=="DEN")
        {
            return new Denominateur(pil);
        }
        else if (s=="$")
        {
            return new Operateur$(pil);
        }
        else if (s=="RE")
        {
            return new PartieReelle(pil);
        }
        else if (s=="IM")
        {
            return new PartieIm(pil);
        }
        else if (s=="=")
        {
            return new Egal(pil);
        }
        else if (s=="!=")
        {
            return new Different(pil);
        }
        else if (s==">=")
        {
            return new SupOuEgal(pil);
        }
        else if (s=="<=")
        {
            return new InfOuEgal(pil);
        }
        else if (s==">")
        {
            return new Sup(pil);
        }
        else if (s=="<")
        {
            return new Inf(pil);
        }
        else if (s=="DUP")
        {
            return new Dup(pil);
        }
        else if (s=="DROP")
        {
            return new Drop(pil);
        }
        else if (s=="SWAP")
        {
            return new Swap(pil);
        }
        else if (s=="CLEAR")
        {
            return new Clear(pil);
        }
        else if (s=="UNDO")
        {
            return new Undo(pil);
        }
        else return nullptr;
    }












