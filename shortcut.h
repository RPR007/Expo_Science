/* shortcut.h
 *
 * Creer par Rafael Prevost
 *
 * Role : Definire la classe shortcut, les methodes de
 * la classe shortcut et les attributs de la classe shortcut
 *
 */

#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <QApplication>
#include <QtGui>
#include <QDialog>
#include <iostream>
#include <QString>

using namespace std;

namespace Ui {
    class shortcut;
}

class shortcut : public QDialog
{
    Q_OBJECT

public:
    explicit shortcut(vector<int > KeyTab[8], QString keyStr[], QWidget *parent = 0);
    ~shortcut();
	bool eventFilter(QObject *object, QEvent *event); 
	bool _isSelected();
	void setShortcut(int row, int colum);
	void init();


public slots:
  	void saved();

private:
    Ui::shortcut *ui;
	int selectedRow; // ligne de tableau
	int selectedColum; // colone de tableau
	QString s; // chaine de caractere des raccourcis claviers
	vector<int> *_KeyTab; // pointeur qui poite sur KeyTab
	vector<int> savedKey[8]; // Tableau de sauvegarde
	QString *_keyStr; // pointeur qui pointe sur KeyStr
	QString savedStr[8]; // Tableau de sauvegarde
	bool release; // boolean
};
  
#endif // SHORTCUT_H
