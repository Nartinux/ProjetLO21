#include "verifregex.h"


//----------------- CLASS VERIFREGEX ------------------------------------------------------------------------------------------------------------------------------------------------

VerifRegex::~VerifRegex() {}

VerifRegex::Handler VerifRegex::handler=VerifRegex::Handler();

VerifRegex& VerifRegex::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new VerifRegex;}
    return *handler.instance;
}

void VerifRegex::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("impossible to destruct an instance which haven't been created");
    delete handler.instance;
    handler.instance=nullptr;
}



bool VerifRegex::verifEntier(QString s)
{
    bool ok=false;
    s.toInt(&ok);
    return ok;
}


bool VerifRegex::verifReel(QString s)
{
    bool ok=false;
    s.toDouble(&ok);
    return ok;
}

bool VerifRegex::verifRationnel(QString s)
{
    int i;
    if((i=s.indexOf('/'))!=-1)
    {
        QString lp=s.left(i);
        QString rp=s.right(s.length()-(i+1));
        if(verifEntier(lp) && verifEntier(rp)) return true;
    }
    return false;
}

bool VerifRegex::verifComplexe(QString s)
{
    int i;
    if(((i=s.indexOf('$'))!=-1))
    {
        QString lp=s.left(i);
        QString rp=s.right(s.length()-(i+1));
        if(verifNombre(lp) && !verifComplexe(lp) && verifNombre(rp) && !verifComplexe(rp)) return true;
    }
    return false;
}


bool VerifRegex::verifNombre(QString s)
{
    if(verifEntier(s) || verifReel(s) || verifRationnel(s) || verifComplexe(s)) return true;
    return false;
}

bool VerifRegex::verifOperateurSimple(QString s)
{
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*") return true;
    if (s=="/") return true;
    return false;
}



bool VerifRegex::verifOperateurAvance(QString s)
{
    // --- op sur les nb
    if (s=="DIV") return true;
    if (s=="MOD") return true;
    if (s=="NEG") return true;
    if (s=="NUM") return true;
    if (s=="DEN") return true;
    if (s=="$") return true;    // sure about that ? 
    if (s=="RE") return true;
    if (s=="IM") return true;

    // --- op logiques
    if (s=="AND") return true;
    if (s=="OR") return true;
    if (s=="NOT") return true;
    if (s=="<") return true;
    if (s==">") return true;
    if (s=="=<") return true;
    if (s==">=") return true;
    if (s=="!=") return true;
    if (s=="=") return true;

    // --- op de manip de progr et exp
    if (s=="EVAL") return true;

    // --- op de manip d'atomes
    if (s=="STO") return true;
    if (s=="FORGET") return true;

    // --- op de manip de pile
    if (s=="DUP") return true;
    if (s=="DROP") return true;
    if (s=="SWAP") return true;
    if (s=="LASTOP") return true;
    if (s=="LASTARGS") return true;
    if (s=="UNDO") return true;
    if (s=="REDO") return true;
    if (s=="CLEAR") return true;
    return false;
}





// verifier que soit un nb est avant ou apres soit dans le cas de moins... soit que y'a un espace avant et apres
// verifie les operateurs definis pas une chaine de char (et des parenthèses avec des args dedans... separés par des virgules !)
bool VerifRegex::verifOperateurAvanceExp(QString s)
{
    int i=0;
    while (i<s.length() && (s[i]>='A') && (s[i]<='Z')) i++;
    if(i==s.length()) return false; 
    if(s[i]=='(')
    {
        if (!verifOperateurAvance(s.mid(0,i))) return false;
        int j=i+1;
        while(i<s.length() && s[i]!=',') i++;
        if(i!=s.length())
        {
            if (!verifNombre(s.mid(j, i-j)) && !verifAtomeExistant(s.mid(j, i-j))) return false;
            else
            {
                j=i+1;
                while(i<s.length() && s[i]!=')') i++;
                if((i==s.length()-1) && (verifNombre(s.mid(j, i-j)) || verifAtomeExistant(s.mid(j, i-j)))) return true; else return false;
            }
        }
        else if (s[i-1]==')' && (verifNombre(s.mid(j, ((i-1)-j) )) || verifAtomeExistant(s.mid(j, ((i-1)-j) )) )) return true; else return false;
    }
    else return false;
}


bool VerifRegex::verifAtome(QString s) // verifie que le string est un candidat pour devenir un atome
{
    bool ok=true;
    if (s[0]>='A' && s[0]<='Z')
    {
        for (int i = 1; i < s.length(); ++i)
        {
            if ((s[i]>='A' && s[i]<='Z') ) {}
            else if (s[i]>='0' && s[i]<='9') {}
                else {ok=false; break;}
        }
    }
    else return false;
    return ok;
}


bool VerifRegex::verifAtomeExistant(QString s)   // verifie que c'est un atome déjà defini
{
    return Atm.existAt(s);
}



bool VerifRegex::verifExpression(QString s)
{
    if( (s.indexOf("+")==-1) && (s.indexOf("-")==-1) && (s.indexOf("*")==-1) && (s.indexOf("/")==-1))    // on check si y'a pas d'operateurs -> juste un atome ou un operateur Avance.
    // toutes les divisions dans les expressions sont gérées a ce niveau comme des operateurs et non des signes représentant un rationnel
    {
        if ( (s[1]=='(') && (s[s.length()-2]==')') )   // cas ou on a 1 layer de parethèses et pas d'operations simples dedans, type: '(TOTO)'
        {
            if(verifNombre(s.mid(2, (s.length()-4))) || verifAtomeExistant(s.mid(2, (s.length()-4))) || verifOperateurAvanceExp(s.mid(2,(s.length()-4)))) return true;
            return false;
        }
        if(verifNombre(s.mid(1, s.length()-2))  || verifAtome(s.mid(1, (s.length()-2))) || verifOperateurAvanceExp(s.mid(1, (s.length()-2)))) return true;
        return false;
    }

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
        if (i==s.length() || (i==s.length()-2)) return false; // pas de fin de parenthèse ou un unique caractere apresla fin des parentheses qui est juste avant le ' final
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
    return false;
}

// on passe un sting sans espaces, modifié ppur qu'il n'y ait pas le pb du -préfixé
//on fait pour chaque opérateur.


bool VerifRegex::verifProgramme(QString s)
{
    if(s.indexOf("[")==0 && s.indexOf(" ")==1 && s.lastIndexOf(" ")==(s.length()-2) && s.lastIndexOf("]")==(s.length()-1))
    {
        int i=2;
        if(s.length()-2==1) return true; // on accepte [ ] pour la recursivite.
        if(s[2]=='[')
        {
            while(s[i]!=']' && i<s.length()-1) i++;
            if(i==s.length()-1) return false;
            i++;
            QString s2=s.mid(2,i-2);
            if(!verifProgramme(s2)) return false;
            QString s3=("["+s.right(s.length()-i));
            return verifProgramme(s3);
        }
        else
        {
            while(s[i]!=' ' && i<s.length()-1) i++;
            if(i==s.length()-1) return false;
            QString s2=s.mid(2,i-2);
            if (!verifNombre(s2)&&(!verifOperateurSimple(s2))&&(!verifOperateurAvance(s2))&&(!verifAtomeExistant(s2))) return false;
            else 
            {
                QString s3=("["+s.right(s.length()-i));
                return verifProgramme(s3);
            }
        }
    }return false;
}

