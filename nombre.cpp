#include "nombre.h"
#include "computer.h"

Nombre::~Nombre(){};
Entier::~Entier(){};
Reel::~Reel(){};

// ------------ CLASS ENTIER -----------------------------------


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
    else return *this;
}


Nombre& Rationnel::operator+(Nombre& a) // ent1,ent2, r // on ne détruit pas les opérandes initiales a et this car il seront détruit après l'appel
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr)
    {
        Entier& ent1=dynamic_cast<Entier&>(num->operator*(*(a1->den)));
        Entier& ent2=dynamic_cast<Entier&>((a1->num)->operator*(*den));
        Entier& ent3=dynamic_cast<Entier&>(ent1.operator+(ent2));
        Entier& ent4=dynamic_cast<Entier&>((den->operator*(*(a1->den))));
        Rationnel* r=new Rationnel(ent3,ent4);
        Nombre& r2=r->simplification();
        LibMemory::freeMem(&ent1);           // liberation memoire des obj cree en interne
        LibMemory::freeMem(&ent2);
        LibMemory::freeMem(&ent3);
        LibMemory::freeMem(&ent4);
        LibMemory::freeMem(r);
        return r2;
    }

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr) return (a2->operator +(*this));


    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent5=dynamic_cast<Entier&>(a3->operator*(*den));
        Entier& ent6=dynamic_cast<Entier&>(num->operator+(ent5));
        Rationnel* r= new Rationnel(ent6,(*den));
        
        Nombre& r2=r->simplification();
        LibMemory::freeMem(&ent5);
        LibMemory::freeMem(&ent6);
        LibMemory::freeMem(r);
        return r2;
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* r= new Reel(re1/re2+a4->val);
        return r->simplification();
    }
    throw ComputerException("");
}

Nombre& Rationnel::operator-(Nombre& a)
{
    Rationnel* a1=dynamic_cast<Rationnel*>(&a);
    if(a1!=nullptr)
    {
        Entier& ent1=dynamic_cast<Entier&>((num->operator*(*(a1->den))).operator -((a1->num)->operator*(*den)));
        Entier& ent2=dynamic_cast<Entier&>(den->operator*(*(a1->den)));
        Rationnel* r= new Rationnel(ent1,ent2);
        return r->simplification();
    }

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr)return (a2->operator -(*this));

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent3=dynamic_cast<Entier&>(num->operator-(a3->operator*(*den)));
        Rationnel* r= new Rationnel(ent3,(*den));
        return r->simplification();
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* r= new Reel(re1/re2-a4->val);
        return r->simplification();
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
        return r->simplification();
    }

    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr)return (a2->operator *(*this));

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent3=dynamic_cast<Entier&>(num->operator*(*a3));
        Rationnel* r= new Rationnel(ent3,(*den));
        return r->simplification();
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* re= new Reel(re1/re2*a4->val);
        return re->simplification();
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
        return r->simplification();
    }
    Complexe* a2=dynamic_cast<Complexe*>(&a);
    if(a2!=nullptr)return (a2->operator /(*this));

    Entier* a3=dynamic_cast<Entier*>(&a);
    if(a3!=nullptr)
    {
        Entier& ent3=dynamic_cast<Entier&>(den->operator*(*a3));
        Rationnel* r= new Rationnel(*num,ent3);
        return r->simplification();
    }

    Reel* a4=dynamic_cast<Reel*>(&a);
    if(a4!=nullptr)
    {
        double re1=num->val;
        double re2=den->val;
        Reel* re= new Reel(re1/re2/a4->val);
        return re->simplification();
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
    Entier& im1=dynamic_cast<Entier&>(*im);
    Reel& im2=dynamic_cast<Reel&>(*im);
    Rationnel& im3=dynamic_cast<Rationnel&>(*im);
    if (&im1!=nullptr || &im2!=nullptr || &im3!=nullptr)
    {
        Entier& a1=dynamic_cast<Entier&>(*re);
        if(&a1!=nullptr){Entier* a=new Entier (a1); delete this; return *a;};

        Rationnel& a2=dynamic_cast<Rationnel&>(*re);
        if(&a2!=nullptr){Rationnel *a= new Rationnel(a2); delete this; return *a;};

        Reel& a3=dynamic_cast<Reel&>(*re);
        if(&a3!=nullptr){Reel* a = new Reel(a3); delete this; return *a;};
    }
    return *this;
}


Nombre& Complexe::operator+(Nombre& a)
{
    Complexe& a1=dynamic_cast<Complexe&>(a);
    if(&a1!=nullptr)
    {
        Complexe* c= new Complexe(((a1.re)->operator+(*re)), (a1.im)->operator+(*im));
        return c->simplification();
    }

    Entier& a2=dynamic_cast<Entier&>(a);
    Reel& a3=dynamic_cast<Reel&>(a);
    Rationnel& a4=dynamic_cast<Rationnel&>(a);
    if (&a2!=nullptr || &a3!=nullptr || &a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator +(*re)),(*im));
        return c->simplification();
    }
    throw ComputerException("type inconnu");
}

Nombre& Complexe::operator-(Nombre& a)
{
    Complexe& a1=dynamic_cast<Complexe&>(a);
    if(&a1!=nullptr)
    {
        Complexe* c= new Complexe(((a1.re)->operator-(*re)), (a1.im)->operator-(*im));
        return c->simplification();
    }

    Entier& a2=dynamic_cast<Entier&>(a);
    Reel& a3=dynamic_cast<Reel&>(a);
    Rationnel& a4=dynamic_cast<Rationnel&>(a);
    if (&a2!=nullptr || &a3!=nullptr || &a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator -(*re)),(*im));
        return c->simplification();
    }
    throw ComputerException("type inconnu");
}

Nombre& Complexe::operator*(Nombre& a)
{
    Complexe& a1=dynamic_cast<Complexe&>(a);
    if(&a1!=nullptr)
    {
        Complexe* c= new Complexe(((a1.re)->operator*(*re)), (a1.im)->operator*(*im));
        return c->simplification();
    }

    Entier& a2=dynamic_cast<Entier&>(a);
    Reel& a3=dynamic_cast<Reel&>(a);
    Rationnel& a4=dynamic_cast<Rationnel&>(a);
    if (&a2!=nullptr || &a3!=nullptr || &a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator*(*re)),(*im));
        return c->simplification();
    }
    throw ComputerException("type inconnu");

}

Nombre& Complexe::operator/(Nombre& a)
{
    Complexe& a1=dynamic_cast<Complexe&>(a);
    if(&a1!=nullptr)
    {
        Complexe* c= new Complexe(((a1.re)->operator/(*re)), (a1.im)->operator/(*im));
        return c->simplification();
    }

    Entier& a2=dynamic_cast<Entier&>(a);
    Reel& a3=dynamic_cast<Reel&>(a);
    Rationnel& a4=dynamic_cast<Rationnel&>(a);
    if (&a2!=nullptr || &a3!=nullptr || &a4!=nullptr)
    {
        Complexe* c= new Complexe((a.operator /(*re)),(*im));
        return c->simplification();
    }

    throw ComputerException("type inconnu");
    //gerer la div par 0 !!!
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

    Rationnel& re3=dynamic_cast<Rationnel&>(*re);
    Rationnel& im3=dynamic_cast<Rationnel&>(*im);
    QString s("");
    if (&re!=nullptr) s+"("+re->toString()+")"; else s+re->toString();
    s+"$";
    if (&im!=nullptr) s+"("+im->toString()+")"; else s+im->toString();
    return s;
}

Complexe::~Complexe()
{
    Entier& re1=dynamic_cast<Entier&>(*re);
    Reel& re2=dynamic_cast<Reel&>(*re);
    Rationnel& re3=dynamic_cast<Rationnel&>(*re);
    if (&re1!=nullptr) delete &re1;
        else if (&re2!=nullptr) delete &re2; else delete &re3;

    Entier& im1=dynamic_cast<Entier&>(*im);
    Reel& im2=dynamic_cast<Reel&>(*im);
    Rationnel& im3=dynamic_cast<Rationnel&>(*im);
    if (&im1!=nullptr) delete &im1;
        else if (&im2!=nullptr) delete &im2; else delete &im3;
}
