#include "qcomputer.h"

QComputer::QComputer(QWidget *parent): QWidget(parent)
{
    //creer les objets
    pile = new Pile;
    controleur=new Controleur(/*ExpressionManager::getInstance(),*/*pile); //ici !!!
    message=new QLineEdit(this);
    vuePile=new QTableWidget(pile->getNbItemsToAffiche(),1,this);
    commande = new QLineEdit(this);
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

    hori1= new QHBoxLayout;
    hori2= new QHBoxLayout;
    hori3= new QHBoxLayout;

    hori1->addWidget(but1);
    hori1->addWidget(but2);
    hori1->addWidget(but3);
    hori2->addWidget(but4);
    hori2->addWidget(but5);
    hori2->addWidget(but6);
    hori3->addWidget(but7);
    hori3->addWidget(but8);
    hori3->addWidget(but9);




    // positionner les objets sur la fenetre
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    couche->addLayout(hori1);
    couche->addLayout(hori2);
    couche->addLayout(hori3);
    setLayout(couche);





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

    // message de bienvenue
    pile->setMessage("Bienvenue");

    // focus à la barre de commande
    commande->setFocus();
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
        stream >> com; // extraction d'un element -> un elem c'est une suite de char ou un espace ?
        // envoyer la commande au controleur
        if (com!="") controleur->commande(com);
    } while (com!="");

    // ligne commande a zero
    commande->clear();
}














