/* slider.cpp
 *
 * Creer par Rafael Prevost
 *
 * Role : Coder les methodes de la classe slider
 * Slider est mode
 *
 */

#include "slider.h"

slider::slider() {

}

slider::slider(QVector<QSlider*> qslider, QSignalMapper *signal_slider) : QWidget()
{
  	/***** CONSTRUCTEUR *****/
	
	 // connexion des slider et initialisation
  // du tableau de sauvegarde	

  _qslider = qslider;
  _signal_slider = signal_slider;

  for (int i = 0; i < 5; i++) {
  	SaveTab[i] = 0;
  	SignalSlider(i, true);
  }
}

void slider::SignalSlider(int i, bool c) {

  // On connecte chaque Slider a une fonction pour pouvoir les  annalisers
  if(c == true) {
	QObject::connect(_qslider[i], SIGNAL(valueChanged(int)), _signal_slider, SLOT(map()));
	_signal_slider->setMapping(_qslider[i], i);
  }
  else
	QObject::disconnect(_qslider[i], 0,0,0); // Deconnecte le slider
}


int slider::setDiff(int value, int i) {
  /***** Difference entre L'anciene et la nouvelle valeur du slider *****/

  int diff = value - SaveTab[i];
  SaveTab[i] = value;

  return diff;
}

void slider::setZero() {
  /***** Fonctionnalite permettant de tout remetre a zero *****/

  for(int i = 0; i < 5; i++) {
	SaveTab[i] = 0;
	_qslider[i]->setValue(SaveTab[i]);
  }
}

int slider::setTab(int i, int diff) {
 /***** Mettre les valeurs des sliders dans des tableau *****/

  // On deconnecte le slider
  SignalSlider(i, false);
 
  /* on test si on peut le modifier
   * si oui on ajoute la difference */
  if(SaveTab[i] >= 0 && SaveTab[i] <= 99) {
	if(SaveTab[i] + diff <= 99 && SaveTab[i] + diff >= 0)
		SaveTab[i] += diff;
		_qslider[i]->setValue(SaveTab[i]);
  }

  // On reconnecte le slider
  SignalSlider(i, true);

  return SaveTab[i];
}

