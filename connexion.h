/* connexion.h
 *
 * Creer par Rafael Prevost
 *
 * Role : Definire la classe connexion, les methodes de
 * la classe connexion et les attributs de la classe connexion
 *
 */


#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDialog>
#include <QComboBox>
#include "uart.h"

namespace Ui {
    class connexion;
}

class connexion : public QDialog
{
    Q_OBJECT

public:
    explicit connexion(uart *rs232, int cTab[],  QWidget *parent = 0);
    ~connexion();
    void setQCombo();

public slots:
	void saved();

private:
    Ui::connexion *ui;
    QVector<QComboBox*> qcombo; // Tableau dinamique des qcombo
    uart *config; // pointeur de l'attribut rs232
    int *_cTab; // pointeur de cTabe
    int saveTab[4]; // tableau de sauvegarde
    QextSerialEnumerator enumerateur;
    QList<QextPortInfo> ports;
};

#endif // CONNECTION_H
