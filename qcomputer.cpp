#include "qcomputer.h"

 
using namespace std;


QComputer::QComputer(QWidget *parent): QWidget(parent) //constructeur de fenetre
{
    //creer les objets
    pile = new Pile();
    factg = &FactoryG::getInstance();
    factp = &FactoryP::getInstance();
    facte = &FactoryE::getInstance();
    factn = &FactoryN::getInstance();
    vrx = &VerifRegex::getInstance();
    factoop = FactoryOperateur::getInstance(*pile);     // la pile est pas en singleton, et il faut qu'ils aient la meme
    controleur=new Controleur(*pile, *vrx, *factoop, *factg, *factp, *facte, *factn);
    message=new QLineEdit(this);
    vuePile=new QTableWidget(pile->getNbItemsToAffiche(),1,this);
    commande = new QLineEditable(this);
    couche=new QVBoxLayout(this);

    //on met l'interface a coté

    but1 =new QPushButton("1", this);
    but2= new QPushButton("2", this);
    but3= new QPushButton("3", this);
    but4= new QPushButton("4", this);
    but5= new QPushButton("5", this);
    but6= new QPushButton("6", this);
    but7= new QPushButton("7", this);
    but8= new QPushButton("8", this);
    but9= new QPushButton("9", this);
    but0= new QPushButton("0", this);
    butMult= new QPushButton("*", this);
    butAdd= new QPushButton("+", this);
    butDiv= new QPushButton("/", this);
    butSub= new QPushButton("-", this);
    butDivEnt= new QPushButton("DIV", this);
    butMod= new QPushButton("MOD", this);
    butPow= new QPushButton("POW", this);
    butNeg= new QPushButton("NEG", this);
    butAnd= new QPushButton("AND", this);
    butOr= new QPushButton("OR", this);
    butNot= new QPushButton("NOT", this);
    butNum= new QPushButton("NUM", this);
    butDen= new QPushButton("DEN", this);
    but$  = new QPushButton("$", this);
    butRe = new QPushButton("RE", this);
    butIm= new QPushButton("IM", this);
    submit= new QPushButton("Enter",this);
    vueatm= new QPushButton("Variables stokées",this);
    vueatm->setFixedWidth(200);
    vueatm->setStyleSheet("background-color: #0866B9; color: white");
    butEgal= new QPushButton("==", this);
    butDiff = new QPushButton("!=", this);
    butSupEg= new QPushButton(">=", this);
    butInfEg= new QPushButton("=<", this);
    butSup= new QPushButton(">", this);
    butInf= new QPushButton("<", this);
    butSto= new QPushButton("STO", this);
    butDup  = new QPushButton("DUP", this);
    butDrop = new QPushButton("DROP", this);
    butSwap= new QPushButton("SWAP", this);
    butClear= new QPushButton("CLEAR",this);
    butForget= new QPushButton("FORGET",this);
    point= new QPushButton(".",this);
    point->setFixedWidth(60);




    hori1 = new QHBoxLayout;
    hori2 = new QHBoxLayout;
    hori3 = new QHBoxLayout;
    hori4 = new QHBoxLayout;
    hori5 = new QHBoxLayout;
    hori6 = new QHBoxLayout;
    hori7 = new QHBoxLayout;
    hori8 = new QHBoxLayout;    // pour enter et vue atm
    hori9 = new QHBoxLayout;
    verti1= new QVBoxLayout;
    verti2= new QVBoxLayout;
    verti3= new QVBoxLayout;
    pave = new QHBoxLayout;
    verti4 = new QVBoxLayout;
    verti5 = new QVBoxLayout;
    pileEdit = new QHBoxLayout;

    hori1->addWidget(but1);
    hori1->addWidget(but2);
    hori1->addWidget(but3);
    hori2->addWidget(but4);
    hori2->addWidget(but5);
    hori2->addWidget(but6);
    hori3->addWidget(but7);
    hori3->addWidget(but8);
    hori3->addWidget(but9);
    hori4->addWidget(butDivEnt);
    hori4->addWidget(butMod);
    hori4->addWidget(butPow);
    hori5->addWidget(butAnd);
    hori5->addWidget(butOr);
    hori5->addWidget(butNot);
    hori6->addWidget(butNeg);
    hori6->addWidget(butNum);
    hori6->addWidget(butDen);
    hori7->addWidget(but$);
    hori7->addWidget(butRe);
    hori7->addWidget(butIm);
    hori8->addWidget(submit);   // enter
    hori8->addWidget(point);
    hori8->addWidget(vueatm);   // vue atm
    hori9->addWidget(butEgal);
    hori9->addWidget(butInf);
    hori9->addWidget(butSup);
    hori9->addWidget(butInfEg);
    hori9->addWidget(butSupEg);
    hori9->addWidget(butDiff);
    hori9->addWidget(butSto);
    verti1->addLayout(hori1);
    verti1->addLayout(hori2);
    verti1->addLayout(hori3);
    verti1->addWidget(but0);
    verti2->addWidget(butAdd);
    verti2->addWidget(butSub);
    verti2->addWidget(butMult);
    verti2->addWidget(butDiv);
    verti3->addLayout(hori4);
    verti3->addLayout(hori5);
    verti3->addLayout(hori6);
    verti3->addLayout(hori7);
    verti4->addWidget(butDup);
    verti4->addWidget(butDrop);
    verti4->addWidget(butSwap);
    verti4->addWidget(butClear);
    verti4->addWidget(butForget);
    verti5->addWidget(vuePile);
    verti5->addWidget(commande);
    pave->addLayout(verti1);
    pave->addLayout(verti2);
    pave->addLayout(verti3);
    pileEdit->addLayout(verti5);
    pileEdit->addLayout(verti4);



    // positionner les objets sur la fenetre
    couche->addWidget(message);
    couche->addLayout(pileEdit);
    couche->addLayout(pave);
    couche->addLayout(hori9);
    couche->addLayout(hori8);
    setLayout(couche);



    //connecter les boutons à la commande
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(const QString&)), commande, SLOT(addText(const QString&)));

    connect(but0, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but0, "0");
    connect(but1, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but1, "1");
    connect(but2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but2, "2");
    connect(but3, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but3, "3");
    connect(but4, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but4, "4");
    connect(but5, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but5, "5");
    connect(but6, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but6, "6");
    connect(but7, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but7, "7");
    connect(but8, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but8, "8");
    connect(but9, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but9, "9");
    connect(butAdd, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butAdd, "+");
    connect(butSub, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butSub, "-");
    connect(butMult, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butMult, "*");
    connect(butDiv, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butDiv, "/");
    connect(butMod, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butMod, "MOD");
    connect(butDivEnt, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butDivEnt, "DIV");
    connect(butEgal, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butEgal, "=");
    connect(butInf, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butInf, "<");
    connect(butSup, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butSup, ">");
    connect(butInfEg, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butInfEg, "<=");
    connect(butSupEg, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butSupEg, ">=");
    connect(butDiff, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butDiff, "!=");
    connect(butSto, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butSto, "STO");
    connect(butDup, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butDup, "DUP");
    connect(butDrop, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butDrop, "DROP");
    connect(butSwap, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butSwap, "SWAP");
    connect(butClear, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butClear, "CLEAR");
    connect(butForget, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butForget, "FORGET");
    connect(butPow, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butPow, "POW");
    connect(butAnd, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butAnd, "AND");
    connect(butOr, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butOr, "OR");
    connect(butNot, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butNot, "NOT");
    connect(butNeg, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butNeg, "NEG");
    connect(butNum, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butNum, "NUM");
    connect(butDen, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butDen, "DEN");
    connect(butRe, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butRe, "RE");
    connect(butIm, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(butIm, "IM");
    connect(but$, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but$, "$");
    connect(point, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(point, ".");






    connect(vueatm, SIGNAL(clicked()), this, SLOT(ouvrirFenVar()));

    connect(submit, SIGNAL(clicked()),this,SLOT(getNextCommande()));


    // titre a la fenetre
    this->setWindowTitle("UTComputer");

    //color
    message->setStyleSheet("background: #0866B9; color: white");
    message->setReadOnly(true);
    vuePile->setStyleSheet("background: darkred; color: white");
    vuePile->verticalHeader()->setStyleSheet("color: black");

    // donne la bonne apparence a vuePile
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);    //decrit la fancon d'écrire dans l'item (ici le QTableWidget) ici on peut pas ecrire dedans (manuellement)
    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);

    // creer une liste de labels
    QStringList numberList;
    for (unsigned int i=pile->getNbItemsToAffiche();i>0;i--)
    {
        QString str = QString::number(i);
        str += ":";
        numberList << str;
        vuePile->setItem(i-1,0,new QTableWidgetItem(""));
    }

    // affectation de la liste de labels au header vertical
    vuePile->setVerticalHeaderLabels(numberList);
    vuePile->setFixedHeight(pile->getNbItemsToAffiche()*vuePile->rowHeight(0)+2);

    // connection signaux-slots
    connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));
    connect(commande, SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    QString s = "0";

    // message de bienvenue
    pile->setMessage("Bienvenue");


    // lecture du fichier de sauvegardes des variables (atomes)
    QFile save("save_var.txt");
    if(save.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
        while(!save.atEnd())
        {
            line=save.readLine();
            getNextCommande(line);
        }
        save.close();
    }

    // focus à la barre de commande
    commande->setFocus();
}




QComputer::~QComputer()
{
    QFile save("save_var.txt");
    if(save.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream flux(&save);
        AtomeManager& atm=AtomeManager::getInstance();

        for (AtomeManager::iterator it=atm.begin(); it!=atm.end(); ++it)
        {
            flux<<(*it).toString()<<" "<<(*it).getVal()->toString()<<" STO \n";
        }
        save.close();
    }
}








void QLineEditable::addText(const QString& s) //slot "addtext" de commande. Prend en argument le texte du bouton cliqué et l'écrit dans la commande
{
    QString c = this->text();
    QString res = c + s;
    this->setText(res);
}


void QComputer::refresh()
{
    // le message
    message->setText(pile->getMessage());
    // effacer tout
    for (unsigned int i=0; i<pile->getNbItemsToAffiche();i++)
        vuePile->item(i,0)->setText("");

    // mettre à jour
    unsigned int nb = 0;
    for (Pile::iterator it=pile->begin(); it!=pile->end() && nb<pile->getNbItemsToAffiche();++it,++nb)
        vuePile->item(4,0)->setText((*it).toString());
}

void QComputer::envoiCmd(QString s)
{
    // si c'est une expression on ne check pas si y'a des espaces, ca sera fait apres !
    if(s[0]=='\'' && s[s.length()-1]=='\'') controleur->sentCommande(s); // donc on envoi tout
    else if(s[0]=='[' && s[s.length()-1]==']') controleur->sentCommande(s);
    else
    {
        // extraction de chaque élément de la ligne
        QTextStream stream(&s);
        QString com;
        do
        {
            stream >> com; // extraction d'un element -> un elem c'est une suite de char sans espace
            // envoyer la commande au controleur
            if (com!="") controleur->sentCommande(com);
        } while (com!="");
    }
}


void QComputer::getNextCommande(QString s)
{
    pile->setMessage("");

    int i=0,a,b;
    while(i<s.length())
    {
        a=s.indexOf('\'');
        b=s.indexOf('[');
        if(a<b || (b==-1 && a==-1))
        {
            while(s[i]!='\'' && i<s.length()) i++;
            if(i!=s.length())
            {
                envoiCmd(s.left(i));
                s=s.right(s.length()-i);
                i=1;
                while(s[i]!='\'' && i<s.length()) i++;
                if(i!=s.length())
                {
                    envoiCmd(s.left(i+1));
                    s=s.right(s.length()-(i+1));
                    i=0;
                }else {envoiCmd(s); break;}

            }
            else {envoiCmd(s); break;}
        }
        else
        {
            while(s[i]!='[' && i<s.length()) i++;
            if(i!=s.length())
            {
                envoiCmd(s.left(i));
                s=s.right(s.length()-i);
                i=1;
                while(s[i]!=']' && i<s.length()) i++;
                if(i!=s.length())
                {
                    envoiCmd(s.left(i+1));
                    s=s.right(s.length()-(i+1));
                    i=0;
                }else {envoiCmd(s); break;}

            }
            else {envoiCmd(s); break;}
        }
    }
    commande->clear();
}




void QComputer::getNextCommande()
{
    pile->setMessage("");

    //recupration du texte de la ligne de commande
    QString s = commande->text();



    int i=0,a,b;
    while(i<s.length())
    {
        a=s.indexOf('\'');
        b=s.indexOf('[');
        if(a<b || (b==-1 && a==-1))
        {
            while(s[i]!='\'' && i<s.length()) i++;
            if(i!=s.length())
            {
                envoiCmd(s.left(i));
                s=s.right(s.length()-i);
                i=1;
                while(s[i]!='\'' && i<s.length()) i++;
                if(i!=s.length())
                {
                    envoiCmd(s.left(i+1));
                    s=s.right(s.length()-(i+1));
                    i=0;
                }else {envoiCmd(s); break;}

            }
            else {envoiCmd(s); break;}
        }
        else
        {
            while(s[i]!='[' && i<s.length()) i++;
            if(i!=s.length())
            {
                envoiCmd(s.left(i));
                s=s.right(s.length()-i);
                i=1;
                while(s[i]!=']' && i<s.length()) i++;
                if(i!=s.length())
                {
                    envoiCmd(s.left(i+1));
                    s=s.right(s.length()-(i+1));
                    i=0;
                }else {envoiCmd(s); break;}

            }
            else {envoiCmd(s); break;}
        }
    }
    commande->clear();
}


void QComputer::ouvrirFenVar()
{
    FenVar& fv= FenVar::getInstance();
    fv.show();
}



//----------------------------------------------------------- CLASS FENVAR --------------------------------------------------------------------------------------

FenVar::~FenVar() {}

FenVar::Handler FenVar::handler=FenVar::Handler();

FenVar& FenVar::getInstance()
{
    if(handler.instance==nullptr){handler.instance= new FenVar();}
    return *handler.instance;
}

void FenVar::libereInstance()
{
    if (handler.instance == nullptr) throw ComputerException("on peut pas liberer une instance si elle est pas cree");
    delete handler.instance;
    handler.instance=nullptr;
}

FenVar::FenVar(): atm(AtomeManager::getInstance())
{
    corps=new QVBoxLayout(this);
    tabvar=new QTableWidget(atm.getNb(),2,this);
    refresh =new QPushButton("Refresh", this);
    verti= new QVBoxLayout;
    hori1 = new QHBoxLayout;
    hori2 = new QHBoxLayout;

    hori1->addWidget(refresh);
    hori2->addWidget(tabvar);
    verti->addLayout(hori1);
    verti->addLayout(hori2);
    corps->addLayout(verti);
    setLayout(corps);

    connect(refresh, SIGNAL(clicked()), this, SLOT(afficherAtm()));
    //connect(tabvar, SIGNAL(cellPressed(int row, int column)), this, SLOT(modifAtm(int r, int c)));

    this->setWindowTitle("UTComputer - Vue variables");
    this->setMinimumSize(400,120);

    unsigned int nb = 0;
    for (AtomeManager::iterator it=atm.begin(); it!=atm.end() && nb < atm.getNb(); ++it,++nb)
    {
        tabvar->setItem(nb,0,new QTableWidgetItem((*it).toString()));
        tabvar->setItem(nb,1,new QTableWidgetItem((*it).getVal()->toString()));
    }
    tabvar->setStyleSheet("background: pink; color: green");
    tabvar->verticalHeader()->setStyleSheet("color: green");
}


void FenVar::afficherAtm()
{
    int nbRow=tabvar->rowCount();
    tabvar->setRowCount(atm.getNb());

    // ajout des QTableWidgetItem manquant
    unsigned int i = nbRow;

    // effacer tout(atm.getNb()-nbRow)
    for (unsigned int i=0; i<atm.getNb();i++)
    {
        delete tabvar->item(i,0); //->setText("");
        delete tabvar->item(i,1); //)->setText("");
    }
    i=0;
    for (AtomeManager::iterator it=(atm.begin()/*+(nbRow-1)*/); it!=atm.end() && i < (atm.getNb()/*-nbRow*/); ++it,++i)
    {
        tabvar->setItem(i,0,new QTableWidgetItem((*it).toString()));
        tabvar->setItem(i,1,new QTableWidgetItem((*it).getVal()->toString()));
    }

/*
    // mettre à jour
    unsigned int nb = 0;
    for (AtomeManager::iterator it=atm.begin(); it!=atm.end() && nb < atm.getNb(); ++it,++nb)
    {
        tabvar->item(nb,0)->setText((*it).toString());
        tabvar->item(nb,1)->setText((*it).getVal()->toString());
    }
*/

}

void FenVar::modifAtm(int r, int c)
{
    throw("lol");
    if (c==1)
    {
        QString s=tabvar->item(r,c)->text();
        FactoryG& fG = FactoryG::getInstance();
        ObjectPile* obp=nullptr;

        if ((obp=fG.Product("35"))!=nullptr)  // si c'est un objectPile autre que atome
        {
            QString idAt=tabvar->item(r,0)->text();
            Atome* at=atm.findAt(idAt);
            at->setVal(obp);
        }
    }
    /*else    // donc c==0
    {
        QString s=tabvar->item(r,c)->text();
        VerifRegex& vrx = VerifRegex::getInstance();

        if (vrx.verifAtome(s) && !(vrx.verifAtomeExistant(s)))  // si c'est un nouvel identifiant d'atome non existant
        {
            QString idAt=tabvar->item(r,c)->text();
            Atome* at=atm.findAt(idAt);
            at->setID(s);
        }
    }*/
}
