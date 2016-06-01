#include "verifregex.h"


//----------------- CLASS VERIFREGEX ------------------------------------------------------------------------------------------------------------------------------------------------


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
    if (s=="$") return true;
    if (s=="MOD") return true;
    if (s=="DIV") return true;
    return false;
}

bool VerifRegex::verifOperateurSimple(const QChar& c)
{
    if (c=='+') return true;
    if (c=='-') return true;
    if (c=='*') return true;
    if (c=='/') return true;
    if (c=='$') return true;
    return false;
}
// verifier que soit un nb est avant ou apres soit dans le cas de moins... soit que y'a un espace avant et apres

// verifie les operateurs definis pas une chaine de char (et des parenthèses avec des args dedans... separés par des virgules !)
bool VerifRegex::verifOperateurAvance(QString s)
{
    int i=0;
    while(i<s.length() && (s[i]>'A' && s[i]<'Z')) i++;
    if(i==s.length()) return false;
    if(s[i]=='(')
    {
        int j=i+1;
        while(i<s.length() && s[i]!=',') i++;
        if(i==s.length()) return false;
        if(verifNombre(s.mid(j, j-i)) || verifAtomeExistant(s.mid(j, j-i)) || verifOperateurAvance(s.mid(j, j-i)))
        {
            j=i+1;
            while(i<s.length() && s[i]!=')') i++;
            if(i==s.length()) return false;
            if(i!=(s.length()-1)) return false; // on ne gere pas les expressions avec des parentheses a l'intérieur d'un perateur avancé, la parenthese doit se trouver a la fin
            if(verifNombre(s.mid(j, j-i)) || verifAtomeExistant(s.mid(j, j-i)) || verifOperateurAvance(s.mid(j, j-i))) return true;
            return false;

        }
        return false;
    }
    else return false;
}


bool VerifRegex::verifAtome(QString s) // verifie que le string est un candidat pour devenir un atome
{
    bool ok=false;
    if (s[0]>'A' && s[0]<'Z')
    {
        for (int i = 1; i < s.length(); ++i)
        {
            if ((s[i]>'A' && s[i]<'Z') || (s[i]>'0' && s[i]<'9')) ok=true;
            if(!ok) break;
        }
    }
    return ok;
}


bool VerifRegex::verifAtomeExistant(QString s)   // verifie que c'est un atome déjà defini
{
    return Atm.existAt(s);
}

// ATTENTION : avec les strings .lenght revoie la longueure totale de la chaine ne comptant pas '\0' le denier char de la chaine (excepté \0) est donc longueure -1 !!
// on ne check pas si y'a des quotes dans la fonction pour pouvoir l'appeler récursivement sur des sous chaines sans avoir a concaténer des quotes ! ce check doit etre fait avant l'appel

bool VerifRegex::verifExpression(QString s)
{
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
}
// on passe un sting sans espaces, modifié ppur qu'il n'y ait pas le pb du -préfixé
//on fait pour chaque opérateur.


//bool VerifRegex::verifProgramme(QString& s);

