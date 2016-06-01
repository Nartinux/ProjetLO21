#include"operation.h"

Entier& modulo(Entier& a,Entier& b){
    Entier* ent=new Entier(a.getInt()%b.getInt());
    return *ent;
}

Entier& diveucli(Entier& a,Entier& b){
    Entier* ent=new Entier(a.getInt()/b.getInt());
    return *ent;
}
