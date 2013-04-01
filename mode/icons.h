/* icons.h
 *
 * Creer par Rafael Prevost
 *
 * Role : Definire la classe icons, les methodes de
 * la classe icons et les attributs de la classe icons
 *
 */

#ifndef ICONS_H
#define ICONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <QtGui>
#include <QPushButton>

using namespace std;

class icons :  public QWidget
{
  	
 // 	 Q_OBJECT

public:
	/* Mes Methode publique */
  icons();
  icons(QVector<QPushButton*> qicons, QSignalMapper *signal_icons);
  void SignalIcons(QString str, int i);

private:
  QSignalMapper *_signal_icons;
  QVector<QPushButton*> _qicons; // Tableau dinamique des sliders
};

#endif // ICONS_H
