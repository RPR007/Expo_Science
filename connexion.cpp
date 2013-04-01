/* connexion.cpp
 *
 * Creer par Rafael Prevost
 *
 * Role : Coder les methodes de la classe connexion
 *
 */

#include "connexion.h"
#include "ui_connexion.h"
#include <iostream>

using namespace std;

connexion::connexion(uart *rs232, int cTab[], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connexion)
{
    ui->setupUi(this);
	setQCombo();

	config = rs232; // config pointe sur rs232
	_cTab = cTab; //_cTab pointe sur cTab

	/***** Initialisation *****/
	for(int i = 0; i < 4; i++)
		qcombo[i]->setCurrentIndex(cTab[i]);
    
    ports = enumerateur.getPorts();//on met ces infos dans une liste
        
    for(int j=0; j<ports.size(); j++)
        ui->name->addItem(ports.at(j).physName);

	// connexion des signaux
	QObject::connect(ui->_connexion, SIGNAL(clicked()), this, SLOT(saved()));
	QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(hide()));

}

void connexion::setQCombo(){
  /* 
  * Tout les qcombo dans un tableau pour pouvoir
  * les manipuler plus efficacement
  * */

  qcombo.push_back(ui->baud);
  qcombo.push_back(ui->donnees);
  qcombo.push_back(ui->parity);
  qcombo.push_back(ui->stop);
}

void connexion::saved() {
  /***** Sauvegard *****/
  for(int i = 0; i < 4; i++)
  	_cTab[i] = qcombo[i]->currentIndex();

  config->_setName(ui->name->currentText());
  config->_setBaud(ui->baud->currentIndex());
  config->_setDataBits(ui->donnees->currentIndex());
  config->_setParity(ui->parity->currentIndex());
  config->_setStopBits(ui->stop->currentIndex());

  // fermeture du dialogue
  hide();
}

connexion::~connexion()
{
    delete ui;
}
