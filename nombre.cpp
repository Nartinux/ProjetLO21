#include "nombre.h"
#include "computer.h"

Nombre::~Nombre(){};
Entier::~Entier(){};
Reel::~Reel(){};

// ------------ CLASS ENTIER -----------------------------------

// pas besoin de liberer "manuellement"  la memoire pour ces methdes car ce sera fait a l'xterieur dans la methode commande de controleur.

Nombre& Entier::operator+(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a+(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a+(*this));}

    Reel* a3=dynamic_cast<Reel*>(&a);
    if(a3!=nullptr){return (a+(*this));}

    Entier* a4=dynamic_cast<Entier*>(&a);
    Entier* ent=new Entier(val+a4->val);
    return *ent;
}

Nombre& Entier::operator-(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a-(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a-(*this));}

    Reel* a3=dynamic_cast<Reel*>(&a);
    if(a3!=nullptr){return (a-(*this));}

    Entier* a4=dynamic_cast<Entier*>(&a);
    Entier* ent=new Entier(val-a4->val);
    return *ent;
}

Nombre& Entier::operator*(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a*(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a*(*this));}

    Reel* a3=dynamic_cast<Reel*>(&a);
    if(a3!=nullptr){return (a*(*this));}

    Entier* a4=dynamic_cast<Entier*>(&a);
    Entier* ent=new Entier(val*a4->val);
    return *ent;
}

Nombre& Entier::operator/(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a/(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a/(*this));}

    Reel* a3=dynamic_cast<Reel*>(&a);
    if(a3!=nullptr){return (a/(*this));}

    Entier* a4=dynamic_cast<Entier*>(&a);
    double r1 = val;
    double r2 = a4->val;
    Reel* re=new Reel(r1/r2);
    return *re;
}

Nombre& Entier::neg()
{
    Entier* ent = new Entier(-val);
    return *ent;
}

QString Entier::toString()const
{
    return QString::number(val);
}


// ----------------------- CLASS RATIONNEL ------------------------------------------------------------------------------------------------------

Nombre& Rationnel::simplification()
{

    //algo d'euclide
    int a=num->val;
    int b=den->val;
    if(a<0) a=-a;
    if(b<0) b=-b;
    while (a!=b){if (a>b) a=a-b; else b=b-a;}
    //fin algo

    num->val/=a;
    den->val/=a;
    if(den->val<0){den->val=-(den->val); num->val=-(num->val);}


    if (den->val==1){Entier* ent=new Entier(num->val); return *ent;}
    if (num->val==0){Entier* ent=new Entier(0); return *ent;}
    return *this;
}


Nombre& Rationnel::operator+(Nombre& a) // ent1,ent2, r // on ne détruit pas les opérandes initiales a et this car il seront détruit après l'appel
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr)
    {
        Entier& ent1=dynamic_cast<Entier&>(num->operator*(*(a1->den)));     // l'operateur appelé crée un nb non libere dans le controleur. a suppr apres
        Entier& ent2=dynamic_cast<Entier&>((a1->num)->operator*(*den));     // allocation ent2
        Entier& ent3=dynamic_cast<Entier&>(ent1.operator+(ent2));           // allocation ent3 ne pas les detruire ils font parti du Rationnel final
        Entier& ent4=dynamic_cast<Entier&>((den->operator*(*(a1->den))));   // allocation ent4 ne pas les detruire ils font parti du Rationnel final
        Rationnel* r=new Rationnel(ent3,ent4);                             // allocation r
        LibMemory::freeMem(&ent1);           // liberation memoire des obj cree en interne
        LibMemory::freeMem(&ent2);
        return *r;
    }

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr) return (a2->operator +(*this));


    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent5=dynamic_cast<Entier&>(a3->operator*(*den));
        Entier& ent6=dynamic_cast<Entier&>(num->operator+(ent5));
        Rationnel* r= new Rationnel(ent6,(*den));
        LibMemory::freeMem(&ent5);
        return *r;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* re= new Reel(re1/re2+a4->val);
        return *re;
    }
    throw ComputerException("");
}

Nombre& Rationnel::operator-(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr)
    {
        Entier& ent1=dynamic_cast<Entier&>(num->operator*(*(a1->den)));
        Entier& ent2=dynamic_cast<Entier&>((a1->num)->operator*(*den));
        Entier& ent3=dynamic_cast<Entier&>(ent1.operator-(ent2));
        Entier& ent4=dynamic_cast<Entier&>((den->operator*(*(a1->den))));
        Rationnel* r=new Rationnel(ent3,ent4);
        LibMemory::freeMem(&ent1);           // liberation memoire des obj cree en interne
        LibMemory::freeMem(&ent2);
        return *r;
    }

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr)return (a2->operator -(*this));

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent5=dynamic_cast<Entier&>(a3->operator*(*den));
        Entier& ent6=dynamic_cast<Entier&>(num->operator-(ent5));
        Rationnel* r= new Rationnel(ent6,(*den));
        LibMemory::freeMem(&ent5);
        return *r;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* re= new Reel(re1/re2-a4->val);
        return *re;
    }
    throw ComputerException("");
}


Nombre& Rationnel::operator*(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr)
    {
        Entier& ent1=dynamic_cast<Entier&>(num->operator *(*(a1->num)));
        Entier& ent2=dynamic_cast<Entier&>(den->operator *(*(a1->den)));
        Rationnel* r=new Rationnel(ent1,ent2);
        return *r;
    }

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr)return (a2->operator *(*this));

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent3=dynamic_cast<Entier&>(num->operator*(*a3));
        Rationnel* r= new Rationnel(ent3,(*den));
        return *r;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* re= new Reel(re1/re2*a4->val);
        return *re;
    }
    throw ComputerException("");
}

Nombre& Rationnel::operator/(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr)
    {
        Entier& ent1=dynamic_cast<Entier&>(num->operator *(*(a1->den)));
        Entier& ent2=dynamic_cast<Entier&>(den->operator*(*(a1->num)));
        Rationnel* r= new Rationnel(ent1,ent2);
        return *r;
    }
    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr)return (a2->operator /(*this));

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent3=dynamic_cast<Entier&>(den->operator*(*a3));
        Rationnel* r= new Rationnel(*num,ent3);
        return *r;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* re= new Reel(re1/re2/a4->val);
        return *re;
    }
    throw ComputerException("");
}

Nombre& Rationnel::neg()
{
    Entier& ent=dynamic_cast<Entier&>(num->neg());
    Rationnel* r = new Rationnel(ent,*den);
    return *r;
}

QString Rationnel::toString()const
{
    return num->toString()+"/"+den->toString();
}



// ----------------------- CLASS REEL ------------------------------------------------------------------------------------------------------

Nombre& Reel::simplification()
{
    int a = val;
    if((val-a)==0)
    {
        Entier* ent =new Entier(val);
        return *ent;
    }
    else return *this;
}

// pas besoin de liberer "manuellement"  la memoire pour ces methdes car ce sera fait a l'xterieur dans la methode commande de controleur.

Nombre& Reel::operator+(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a+(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a+(*this));}

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Reel* re=new Reel(val+a3->val);
        return *re;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    Reel* re=new Reel(val+a4->val);
    return *re;
}

Nombre& Reel::operator-(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a-(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a-(*this));}

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Reel* re=new Reel(val-a3->val);
        return *re;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    Reel* re=new Reel(val-a4->val);
    return *re;
}
Nombre& Reel::operator*(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a*(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a*(*this));}

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Reel* re=new Reel(val*a3->val);
        return *re;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    Reel* re=new Reel(val*a4->val);
    return *re;
}
Nombre& Reel::operator/(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr){return (a/(*this));}

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr){return (a/(*this));}

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Reel* re=new Reel(val/a3->val);
        return *re;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    Reel* re=new Reel(val/a4->val);
    return *re;
    // gerer la div par 0 !!!
}
Nombre& Reel::neg()
{
    Reel* re = new Reel(-val);
    return *re;
}

QString Reel::toString()const
{
    return QString::number(val);
}




// ----------------------- CLASS COMPLEXE ------------------------------------------------------------------------------------------------------------------


Nombre& Complexe::simplification()
{
    Entier* im1=dynamic_cast<Entier*>(im);
    if (im1!=nullptr)
    {
        if(im1->val==0)
        {
                Entier* a1=dynamic_cast<Entier*>(re);
                if(a1!=nullptr){Entier* a=new Entier (a1->val); return *a;};

                Rationnel* a2=dynamic_cast<Rationnel*>(re);
                if(a2!=nullptr){Rationnel *a= new Rationnel(*(a2->num), *(a2->den)); return *a;};

                Reel* a3=dynamic_cast<Reel*>(re);
                if(a3!=nullptr){Reel* a = new Reel(a3->val); return *a;};
        }
    }
    return *this;
}


Nombre& Complexe::operator+(Nombre& a)
{
    Complexe* a1=dynamic_cast<Complexe*>(&a);
    if(a1!=nullptr)
    {
        Complexe* c= new Complexe(((a1->re)->operator+(*re)), (a1->im)->operator+(*im));
        return *c;
    }

    Entier* a2=dynamic_cast<Entier*>(&a);
    Reel *a3=dynamic_cast<Reel*>(&a);
    Rationnel* a4=dynamic_cast<Rationnel*>(&a);
    if (a2!=nullptr || a3!=nullptr || a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator +(*re)),(*im));
        return c->simplification();
    }
    throw ComputerException("type inconnu");
}

Nombre& Complexe::operator-(Nombre& a)
{
    Complexe* a1=dynamic_cast<Complexe*>(&a);
    if(a1!=nullptr)
    {
        Complexe* c= new Complexe(((a1->re)->operator-(*re)), (a1->im)->operator-(*im));
        return *c;
    }

    Entier* a2=dynamic_cast<Entier*>(&a);
    Reel* a3=dynamic_cast<Reel*>(&a);
    Rationnel* a4=dynamic_cast<Rationnel*>(&a);
    if (a2!=nullptr || a3!=nullptr || a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator -(*re)),(*im));
        return c->simplification();
    }
    throw ComputerException("type inconnu");
}

Nombre& Complexe::operator*(Nombre& a)
{
    Complexe* a1=dynamic_cast<Complexe*>(&a);
    if(a1!=nullptr)
    {
        //numerateur de la partie reelle
        Nombre& nb1=re->operator*(*(a1->re));
        Nombre& nb2=(a1->im)->operator*(*im);
        Nombre& nb3=nb1.operator -(nb2);
        LibMemory::freeMem(&nb1);
        LibMemory::freeMem(&nb2);

        //numerateur de la partie immaginaire
        nb1=(a1->re)->operator*(*im);
        nb2=re->operator*(*(a1->im));
        Nombre& nb4=nb2.operator +(nb1);
        LibMemory::freeMem(&nb1);
        LibMemory::freeMem(&nb2);


        Complexe* c= new Complexe(nb3, nb4);
        return *c;
    }

    Entier& a2=dynamic_cast<Entier&>(a);
    Reel& a3=dynamic_cast<Reel&>(a);
    Rationnel& a4=dynamic_cast<Rationnel&>(a);
    if (&a2!=nullptr || &a3!=nullptr || &a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator*(*re)),(a.operator*(*im)));
        return *c;
    }
    throw ComputerException("type inconnu");

}

Nombre& Complexe::operator/(Nombre& a)
{
    Complexe* a1=dynamic_cast<Complexe*>(&a);
    if(a1!=nullptr)
    {
        //numerateur de la partie reelle
        Nombre& nb1= re->operator*(*(a1->re));
        Nombre& nb2= (a1->im)->operator*(*im);
        Nombre& nb3= nb1.operator +(nb2);
        LibMemory::freeMem(&nb1);
        LibMemory::freeMem(&nb2);

        // denominateur de la partie reelle et imaginaire
        nb1=(a1->re)->operator*(*(a1->re));
        nb2=(a1->im)->operator*(*(a1->im));
        Nombre& nb4=nb1.operator +(nb2);
        Nombre& nb5=nb3.operator/(nb4);
        LibMemory::freeMem(&nb1);
        LibMemory::freeMem(&nb2);
        LibMemory::freeMem(&nb3);

        //numerateur de la partie immaginaire
        nb1=(a1->re)->operator*(*im);
        nb2=re->operator*(*(a1->im));
        nb3=nb1.operator -(nb2);
        Nombre& nb6=nb3.operator/(nb4);
        LibMemory::freeMem(&nb1);
        LibMemory::freeMem(&nb2);
        LibMemory::freeMem(&nb3);
        LibMemory::freeMem(&nb4);

        Complexe* c= new Complexe(nb5, nb6);
        return *c;
    }

    Entier& a2=dynamic_cast<Entier&>(a);
    Reel& a3=dynamic_cast<Reel&>(a);
    Rationnel& a4=dynamic_cast<Rationnel&>(a);
    if (&a2!=nullptr || &a3!=nullptr || &a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator /(*re)),(a.operator /(*im)));
        return *c;
    }
    throw ComputerException("type inconnu");
}

Nombre& Complexe::operator$(Nombre& a)
{
    // on choisit d'en faire l'addition (on a pas a gérer l'erreur comme ca)
    return (this->operator +(a));
}

Nombre& Complexe::neg()
{
    Complexe* c = new Complexe(re->neg(), im->neg());
    return *c;
}


QString Complexe::toString()const
{

    Rationnel* re3=dynamic_cast<Rationnel*>(re);
    Rationnel* im3=dynamic_cast<Rationnel*>(im);
    return re->toString()+"$"+im->toString();
    /*
    QString s("");
    if (re3!=nullptr) s+"("+re->toString()+")"; else s+re->toString();
    s+"$";
    if (im3!=nullptr) s+"("+im->toString()+")"; else s+im->toString();
    return s;
    */
}

Complexe::~Complexe()
{
    delete re;
    delete im;
}
