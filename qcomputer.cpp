#include "qcomputer.h"

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
    butSin= new QPushButton("SIN", this);
    butCos= new QPushButton("COS", this);
    butTan= new QPushButton("TAN", this);
    butNum= new QPushButton("NUM", this);
    butDen= new QPushButton("DEN", this);
    but$  = new QPushButton("$", this);
    butRe = new QPushButton("RE", this);
    butIm= new QPushButton("IM", this);
    submit= new QPushButton("Enter",this);
    vueatm= new QPushButton("Variables stokées",this);

    but0->setCursor(Qt::PointingHandCursor);
    but1->setCursor(Qt::PointingHandCursor);
    but2->setCursor(Qt::PointingHandCursor);
    but3->setCursor(Qt::PointingHandCursor);
    but4->setCursor(Qt::PointingHandCursor);
    but5->setCursor(Qt::PointingHandCursor);
    but6->setCursor(Qt::PointingHandCursor);
    but7->setCursor(Qt::PointingHandCursor);
    but8->setCursor(Qt::PointingHandCursor);
    but9->setCursor(Qt::PointingHandCursor);
    butAdd->setCursor(Qt::PointingHandCursor);
    butMult->setCursor(Qt::PointingHandCursor);
    butDiv->setCursor(Qt::PointingHandCursor);
    butSub->setCursor(Qt::PointingHandCursor);

    hori1 = new QHBoxLayout;
    hori2 = new QHBoxLayout;
    hori3 = new QHBoxLayout;
    hori4 = new QHBoxLayout;
    hori5 = new QHBoxLayout;
    hori6 = new QHBoxLayout;
    hori7 = new QHBoxLayout;
    hori8 = new QHBoxLayout;    // pour enter et vue atm
    verti1= new QVBoxLayout;
    verti2= new QVBoxLayout;
    verti3= new QVBoxLayout;
    pave= new QHBoxLayout;
    verti4= new QVBoxLayout;// ...

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
    hori5->addWidget(butTan);
    hori5->addWidget(butSin);
    hori5->addWidget(butCos);
    hori6->addWidget(butNeg);
    hori6->addWidget(butNum);
    hori6->addWidget(butDen);
    hori7->addWidget(but$);
    hori7->addWidget(butRe);
    hori7->addWidget(butIm);
    hori8->addWidget(submit);   // enter 
    hori8->addWidget(vueatm);   // vue atm
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
    pave->addLayout(verti1);
    pave->addLayout(verti2);
    pave->addLayout(verti3);
    verti4->addLayout(pave);
    verti4->addLayout(hori8);   // ici
        // la


    // positionner les objets sur la fenetre
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    couche->addLayout(verti4);  // remplace le pave !
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


    connect(vueatm, SIGNAL(clicked()), this, SLOT(ouvrirFenVar()));

    connect(submit, SIGNAL(clicked()),this,SLOT(getNextCommande()));


    // titre a la fenetre
    this->setWindowTitle("UTComputer");

    //color
    message->setStyleSheet("background: blue; color: yellow");
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

    // focus à la barre de commande
    commande->setFocus();
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
		vuePile->item(pile->getNbItemsToAffiche()-1-nb,0)->setText((*it).toString());
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
    corps->addWidget(tabvar);
    setLayout(corps);

    connect(refresh, SIGNAL(clicked()), this, SLOT(afficherAtm()));

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
    // effacer tout
    for (unsigned int i=0; i<atm.getNb();i++)
    {
        tabvar->item(i-1,0)->setText("");
        tabvar->item(i-1,1)->setText("");
    }
    // mettre à jour
    unsigned int nb = 0;
    for (AtomeManager::iterator it=atm.begin(); it!=atm.end() && nb < atm.getNb(); ++it,++nb)
    {
        tabvar->item(nb,0)->setText((*it).toString());
        tabvar->item(nb,1)->setText((*it).getVal()->toString());
    }  
}

/*
    for (unsigned int i=atm.getNb(); i>0; i--)
    {
        tabvar->setItem(i-1,0,new QTableWidgetItem(""));
    }
for (AtomeManager::iterator it=atm.begin(); it!=atm.end() && nb < atm.getNb(); ++it,++nb)
    {
        tabvar->setItem(i-1,0,new QTableWidgetItem((*it).toString()));
        tabvar->setItem(i-1,1,new QTableWidgetItem((*it).getVal()->toString()));
    }
    */
