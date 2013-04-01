/* slider.h
 *
 * Creer par Rafael Prevost
 *
 * Role : Definire la classe slider, les methodes de
 * la classe slider et les attributs de la classe slider
 *
 */

#ifndef SLIDER_H
#define SLIDER_H

#include <iostream>
#include <string>
#include <sstream>
#include <QtGui>
#include <QSlider>

using namespace std;

class slider : public QWidget
{
	
  	 Q_OBJECT

public:
	/* Mes Methode publique */
  slider();
  slider(QVector<QSlider*> qslider, QSignalMapper *signal_slider);
  int setTab(int i, int diff);
  int setDiff(int value, int i);
  void setZero();
  void SignalSlider(int i, bool c);

private:
  int SaveTab[5]; // Sauvegarde des valeur des sliders
  QSignalMapper *_signal_slider;
  QVector<QSlider*> _qslider; // Tableau dinamique des sliders
};

#endif // SLIDER_H
