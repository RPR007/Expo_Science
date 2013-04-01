/* uart.h
 *
 * Creer par Rafael Prevost
 *
 * Role : Definire la classe uart, les methodes de
 * la classe uart et les attributs de la classe uart
 *
 */

#ifndef UART_H
#define UART_H

#include <iostream>
#include <string>
#include <QtGui>
#include "qextserialport.h"
#include "qextserialenumerator.h"

using namespace std;


class uart : public QextSerialPort
{

public:
    uart();
	bool openPort();
	void closePort();
	void putMsg(string msg);
	void _setName(QString name);
	void _setBaud(int baud);
	void _setParity(int parity);
	void _setDataBits(int dataBits);
	void _setStopBits(int stopBits);

private:
	QextSerialPort *serialport; // creation de la connexion
	QString _name; // Le nom du peripherique
	int _baud; // La vitesse de connexion
	int _parity; // Bits de parite
	int _dataBits; // le nombre de bits
	int _stopBits;
};

#endif // UART_H
