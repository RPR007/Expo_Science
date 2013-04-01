#include "icons.h"

icons::icons()
{
}

icons::icons(QVector<QPushButton*> qicons, QSignalMapper *signal_icons) : QWidget()
{
  QString str[10] = {"11,0 20,0 30,0 40,0 51,0 ", "11,0 21,0 31,0 40,1 51,0 ", "11,0 21,0 30,0 41,0 51,0 ", "11,0 21,0 30,0 40,0 51,0 ", "11,0 21,0 31,0 40,0 50,0 ", "10,0 20,0 30,0 40,0 50,0 ", "11,0 21,0 31,0 41,0 51,0 ", "11,0 21,0 31,0 41,0 50,0 ", "10,0 21,0 31,0 41,0 50,0 ", "11,750 10,750 21,750 20,750 31,750 30,750 41,750 40,750 51,750 50,750 "};
  	/***** CONSTRUCTEUR *****/
	
	 // connexion des slider et initialisation
  // du tableau de sauvegarde	

  _qicons = qicons;
  _signal_icons = signal_icons;

  for (int i = 0; i < 10; i++) {
  	SignalIcons(str[i], i);
  }
}

void icons::SignalIcons(QString str, int i) {

  // On connecte chaque Slider a une fonction pour pouvoir les  annalisers
  QObject::connect(_qicons[i], SIGNAL(clicked()), _signal_icons, SLOT(map()));
  _signal_icons->setMapping(_qicons[i], str);
}

