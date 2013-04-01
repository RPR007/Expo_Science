/* uart.cpp
 *
 * Creer par Rafael Prevost
 *
 * Role : Gerer la connexion uart
 *
 */

#include "uart.h"

uart::uart() {
  /***** Constructeur *****/
}

bool uart::openPort() {
  /***** Ouvrir la connexion *****/

  serialport = new QextSerialPort();
  serialport->setPortName(_name);
  serialport->setBaudRate((BaudRateType)_baud);
  serialport->setDataBits((DataBitsType)_dataBits);
  serialport->setStopBits((StopBitsType)_stopBits);
  serialport->setFlowControl(FLOW_OFF);
  serialport->setParity((ParityType)_parity);

  if (serialport->open(QIODevice::ReadWrite))
	return true;
  else
	return false;
}

void uart::closePort() {
  // fermeture de la connexion
  serialport->close();
}

void uart::putMsg(string msg) {
  /***** Envoi du message *****/

 int i;
 for (i = 0; msg[i] != '\0'; i++)
	serialport->putChar(msg[i]);
}

void uart::_setName(QString name) {
  _name = name;
}

void uart::_setBaud(int baud) {
  _baud = baud;
}

void uart::_setParity(int parity) {
  _parity = parity;
}

void uart::_setDataBits(int dataBits) {
  _dataBits = dataBits;
}

void uart::_setStopBits(int stopBits) {
	_stopBits = stopBits;
}


