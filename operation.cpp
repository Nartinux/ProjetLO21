#include"operation.h"

//------------------------------------------- CLASS OPERATEURAVANCE  ---------------------------------------------------------------------------------------------------

OperateurAvance::~OperateurAvance() {}




//------------------------------------------- CLASS EVAL ---------------------------------------------------------------------------------------------------


Eval::~Eval(){}

ObjectPile& Eval::operation()
{

    ObjectPile& obp=getPile().top();
    getPile().pop();
    return obp;
   /* QString exp=obp.getExp();
    // Prioités -> operateursAvances, parentheses, mul/div, add/sub
    // bien faire gaffe aux nombres negatifs ! c'est pas des soustractions

    if( (s.indexOf("+")==-1) && (s.indexOf("-")==-1) && (s.indexOf("*")==-1) && (s.indexOf("/")==-1))    // on check si y'a pas d'operateurs -> juste un atome ou un operateur Avance.
    // toutes les divisions dans les expressions sont gérées a ce niveau comme des operateurs et non des signes représentant un rationnel
    {
        if ( (s[1]=='(') && (s[s.length()-3]==')') )   // cas ou on a 1 layer de parethèses et pas d'operations simples dedans, type: '(TOTO)'
        {
            if(verifNombre(s.mid(2, (s.length()-4))) || verifAtomeExistant(s.mid(2, (s.length()-4))) || verifOperateurAvance(s.mid(2,(s.length()-4)))) return true;
            return false;
        }
        if(verifNombre(s.mid(1, s.length()-2)) || verifAtomeExistant(s.mid(1, s.length()-2)) || verifOperateurAvance(s.mid(1, s.length()-2))) return true;
        return false;
    }

    int i=1, j=1;
    bool ok=true;
    while (i<(s.length()-1))
    {
        if (verifOperateurSimple(s.at(1)))
        {
            if( (s[j]=='(') && (s[i]=='-') && (j==i-1)) // cas type: (-987)
            {
                j++;
                while(s[i]!=')' && i<s.length()) i++;
                if (i==s.length()) return false; // pas de fin de parenthèse !! -> illegal
                ok=verifNombre(s.mid(j,j-i));
                if(!ok) break; else j=i+1;

            }
            if (s[j]=='(' && s[i-1]==')')   // cas ou on a 1 layer de parethèses et pas d'operations simples dedans, type: '44*(X)/7'
            {
                ok=verifExpression(s.mid(j+1, i-j-2)); // on rappelle la fonction qui s'arretera au premier if
            }
            if (s[j]=='(' && s[i-1]!=')') // cas d'operations dans les paretheses
            {
                int countpo=1; // nb de parentheses ouvrantes decouvertes jusqu'alors
                int countpf=0; // nb de parentheses fermantes decouvertes jusqu'alors
                while(countpf!=countpo && i<s.length())
                {
                    i++;
                    if (s[i]==')') countpf++;
                    if (s[i]=='(') countpo++;
                }
                if (i==s.length()) return false; // pas de fin de parenthèse !! -> illegal
                else
                {
                    ok=verifExpression(s.mid(j, i-j-1)); // on verifie ce qu'il y a dedans recursivement
                    if(!ok) break; else j=i+1;
                }
            }
            if(s[j]!='(') ok=verifExpression(s.mid(j, i-j)); // on rappelle la fonction qui s'arretera au premier if
            if(!ok) break; else j=i+1;
        }
        i++;
    }
    return ok;
    */
}



















Entier& modulo(Entier& a,Entier& b){
    Entier* ent=new Entier(a.getInt()%b.getInt());
    return *ent;
}

Entier& diveucli(Entier& a,Entier& b){
    Entier* ent=new Entier(a.getInt()/b.getInt());
    return *ent;
}
