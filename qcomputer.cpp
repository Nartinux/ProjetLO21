#include "qcomputer.h"

QComputer::QComputer(QWidget *parent): QWidget(parent) //constructeur de fenetre
{
    //creer les objets
    pile = new Pile();
    fact = new Factory();
    controleur=new Controleur(/*ExpressionManager::getInstance(),*/*pile,*fact); //ici !!!
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
    submit= new QPushButton("Enter",this);

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

    hori1= new QHBoxLayout;
    hori2= new QHBoxLayout;
    hori3= new QHBoxLayout;
    verti1= new QVBoxLayout;
    verti2= new QVBoxLayout;
    pave= new QHBoxLayout;

    hori1->addWidget(but1);
    hori1->addWidget(but2);
    hori1->addWidget(but3);
    hori2->addWidget(but4);
    hori2->addWidget(but5);
    hori2->addWidget(but6);
    hori3->addWidget(but7);
    hori3->addWidget(but8);
    hori3->addWidget(but9);
    verti1->addLayout(hori1);
    verti1->addLayout(hori2);
    verti1->addLayout(hori3);
    verti1->addWidget(but0);
    verti2->addWidget(butAdd);
    verti2->addWidget(butSub);
    verti2->addWidget(butMult);
    verti2->addWidget(butDiv);
    pave->addLayout(verti1);
    pave->addLayout(verti2);


    // positionner les objets sur la fenetre
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    couche->addLayout(pave);
    couche->addWidget(submit);
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

    connect(submit, SIGNAL(clicked()),this,SLOT(getNextCommande()));


    // titre a la fenetre
    this->setWindowTitle("UTComputer");

    //color
    message->setStyleSheet("background: blue; color: yellow");
    message->setReadOnly(true);
    vuePile->setStyleSheet("background: darkred; color: white");
    vuePile->verticalHeader()->setStyleSheet("color: black");

    // donne la bonne apparence a vuePile
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
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



void QComputer::getNextCommande()
{
    pile->setMessage("");

    //recupration du texte de la ligne de commande
    QString c = commande->text();

    // extraction de chaque élément de la ligne
    QTextStream stream(&c);
    QString com;
    do
    {
        stream >> com; // extraction d'un element -> un elem c'est une suite de char sans espace
        // envoyer la commande au controleur
        if (com!="") controleur->commande(com);
    } while (com!="");

    // ligne commande a zero
    commande->clear();
}














