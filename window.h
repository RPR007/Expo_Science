/* window.h
 *
 * Creer par Rafael Prevost
 *
 * Role : Definire la classe window, les methodes de
 * la classe window et les attributs de la classe window
 *
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QChar>

#include "shortcut.h"
#include "connexion.h"
#include "uart.h"
#include "mode/slider.h"
#include "mode/icons.h"

using namespace std;

namespace Ui {
    class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
	/* Mes Methode publique */
    explicit window(QWidget *parent = 0);
    ~window();
	void init();
	bool eventFilter(QObject *object, QEvent *event);
	int Sleep( unsigned int timeout_ms);
	void setMsg(int val, int i);
	string convertInt(int val);

public slots:
  	/* Mes Slots publique */
	void ui_raccourcis();
	void ui_Connexion();
	void Connexion();
	void Deconnexion();
	void Slider(int);
	void Icons(const QString c);

private:
	/* Mes variable privees */
	Ui::window *ui;
	uart rs232; // Variable pour gerer la connexion
	int cTab[4]; // Tableu des parametre de connexion 
	vector<int > KeyTab[8]; // Tableau des raccourcis clavier
	QString keyStr[8]; // Tableu de chaine de caractere
	QSignalMapper *signal_slider;
	QSignalMapper *signal_icons;
	bool _connecter;
	bool tabKey[7]; // Tableau de boolean pour les raccourcis clavier
	QVector<QSlider*> qslider; // Tableau dinamique des sliders
	QVector<QPushButton*> qicons;
	slider *_slider;
	icons *_icons;

};

#endif // WINDOW_H
