/* window.cpp
 *
 * Creer par Rafael Prevost
 *
 * Role : Coder les methodes de la classe window
 * Fenetre Principal
 * Code central
 *
 */

#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window)
{
  	/***** CONSTRUCTEUR *****/ 	
    ui->setupUi(this);

   	ui->centralwidget->installEventFilter(this);
	
	// initialisation des attribut
	init();

	_slider = new slider(qslider, signal_slider);
	connect(signal_slider, SIGNAL(mapped(int)), this, SLOT(Slider(int)));

	_icons = new icons(qicons, signal_icons);
	connect(signal_icons, SIGNAL(mapped(const QString &)), this, SLOT(Icons(const QString &)));

	// connexion des signaux
	QObject::connect(ui->actionQuiter, SIGNAL(triggered()), qApp, SLOT(quit()));
	QObject::connect(ui->actionConfigurer_les_raccourcis_clavier, SIGNAL(triggered()), this, SLOT(ui_raccourcis()));
	QObject::connect(ui->actionConfigurer_la_connexion, SIGNAL(triggered()), this, SLOT(ui_Connexion()));
	QObject::connect(ui->actionConnexion, SIGNAL(triggered()), this , SLOT(Connexion()));
	QObject::connect(ui->actionDeconnexion, SIGNAL(triggered()), this, SLOT(Deconnexion()));
}


void window::init() {
  /***** INITIALISATION *****/

  signal_slider = new QSignalMapper(this);
  signal_icons = new QSignalMapper(this);

  qslider.push_back(ui->qslider0);
  qslider.push_back(ui->qslider1);
  qslider.push_back(ui->qslider2);
  qslider.push_back(ui->qslider3);
  qslider.push_back(ui->qslider4);

  qicons.push_back(ui->icons0);
  qicons.push_back(ui->icons1);
  qicons.push_back(ui->icons2);
  qicons.push_back(ui->icons3);
  qicons.push_back(ui->icons4);
  qicons.push_back(ui->icons5);
  qicons.push_back(ui->icons6);
  qicons.push_back(ui->icons7);
  qicons.push_back(ui->icons8);
  qicons.push_back(ui->fonction1);
  

  // initialisation du tableau de boolean des raccourcis clavier
  for (int i = 0; i < 7; i++)
    tabKey[i] = false;

  // initialisation des parametres de connexion
  
  cTab[0] = 12;
  cTab[1] = 3;
  cTab[2] = 0;
  cTab[3] = 0;

  rs232._setBaud(cTab[0]);
  rs232._setDataBits(cTab[1]);
  rs232._setParity(cTab[2]);
  rs232._setStopBits(cTab[3]);
  _connecter = false;


  // initialisation des raccourcis clavier
  KeyTab[0].push_back(Qt::Key_1);
  KeyTab[1].push_back(Qt::Key_2);
  KeyTab[2].push_back(Qt::Key_3);
  KeyTab[3].push_back(Qt::Key_4);
  KeyTab[4].push_back(Qt::Key_5);
  KeyTab[5].push_back(Qt::Key_Control);
  KeyTab[6].push_back(Qt::Key_0);
  KeyTab[7].push_back(Qt::Key_Control);
  KeyTab[7].push_back(Qt::Key_Q);

  keyStr[0] = "1";
  keyStr[1] = "2";
  keyStr[2] = "3";
  keyStr[3] = "4";
  keyStr[4] = "5";
  keyStr[5] = "Ctrl";
  keyStr[6] = "0";
  keyStr[7] = "Ctrl+Q";

  /* on desactive la deconnection puisqu'on est
   *pas connecter */
  ui->actionDeconnexion->setEnabled (false);
}

void window::ui_raccourcis() {
  /***** BOITE DE DIALOGUE DES RACCOURCIS CLAVIER *****/

  shortcut *_shortcut = new shortcut(KeyTab, keyStr);
  _shortcut->exec();

  //ont recupere le Raccourcis clavier pour Quiter
  ui->actionQuiter->setShortcut(QKeySequence(keyStr[7]));	
}

void window::ui_Connexion() {
  /***** BOITE DE DIALOGUE DES PARAMETRE DE LA CONNEXION *****/

  connexion *_connexion = new connexion(&rs232, cTab);
  _connexion->exec();
}

void window::Connexion() {
  /***** Connexion *****/

  if(rs232.openPort()) {
	/* La connexion a reussi.
	 * On Desactive la connexion et On active la deconnexion.
	 * On mets l'attribut _connecter a true.
	 * puis on averti l'utilisateur que la connexion a reussi. */

	ui->actionConnexion->setEnabled(false);
	ui->actionDeconnexion->setEnabled(true);
	_connecter = true;
	QMessageBox::information(this, "Connexion", "Connexion Reussi");
  }
  else {
	/* la connexion n'a pas reussi.
	 * on envoie un message d'erreur a l'utilisateur */

	QMessageBox::critical(this, "Connexion", "Impossible de se connecter");	
  }
}

void window::Deconnexion() {
  /***** Deconnexion *****/

  // Le contraire de la connexion
  rs232.closePort();
  ui->actionConnexion->setEnabled(true);
  ui->actionDeconnexion->setEnabled(false);
  _connecter = false;
  QMessageBox::information(this, "Deconnexion", "Vous etes deconnecte");
}


void window::Slider(int i) {
  /***** Signals que un des slider a change de valeur *****/
  int j;
  int value = qslider[i]->value(); 
  // difference entre l'ancience et la nouvelle valeur du slider
  int diff = _slider->setDiff(value, i);
  if(_connecter)
	setMsg(value, i);

  // on regarde si un des raccourcis clavier est actif
  if(tabKey[5] == true) {
	for(j = 0; j < 5; j++)
	  if(j != i) {
		value = _slider->setTab(j, diff);
	  if(_connecter)
		setMsg(value, j);
	  }
  }
  else {
  	for(j = 0; j < 5; j++) {
		if(tabKey[j] == true && j != i) {
		 value = _slider->setTab(j, diff);
		  if(_connecter)
			setMsg(value, j);
		}
  	}
  }

}

void window::Icons(const QString c) {
  char sec[100];
  char indice[100];
  int s, j;

  for(int i = 0;c[i].toLatin1() != '\0' ; i++) {
	if(_connecter) {
	  for(j = 0; j < 100; j++)
		sec[j] = 0,indice[j] = 0;
	
	  indice[0] = c[i].toLatin1();
	  i++;

	  if(c[i].toLatin1() == '0') {
		setMsg(0,atoi(indice)-1);
	  }
	  else if(c[i].toLatin1() == '1') {
		setMsg(99,atoi(indice)-1);
	  }

	  i += 2;
	  for(j = 0;  c[i].toLatin1() != ' '; i++, j++)
	  	  sec[j] =  c[i].toLatin1();
	  s = atoi(sec);
	  Sleep(s);
	}
  }
}

int window::Sleep( unsigned int timeout_ms )
{
        struct timeval tv;
        tv.tv_sec = timeout_ms/1000;
        tv.tv_usec = (timeout_ms%1000) * 1000;
        select(0, NULL, NULL, NULL, &tv);
        return 0;
}

void window::setMsg(int val, int i) {
  /***** Envoit du Message *****/

  // On convertie la valeur en micro seconde
  val = (230-52)*val/99+52;
  
  // on converti la valeur en chaine de caractere
  string sVal = convertInt(val);

  // on converti l'indice en chaine de caractere 
  string sI = convertInt(i);

  // on concatene l'indice et la valeur
  string msg = sI + "," + sVal + '\n';

  // on envoie la chaine de caractere
  rs232.putMsg(msg);
}

string window::convertInt(int val) {
  /***** Convertion des entiers en chaine de caractere *****/

  // creer un flux de sortie
  std::ostringstream oss;
  // ecrire un nombre dans le flux
  oss << val;
  // recuperer une chaine de caracteres
  return oss.str();
}

bool window::eventFilter(QObject *object, QEvent *event) {
  /***** Gestion des evennements *****/

  static vector<int>::iterator it[7] = 
  {KeyTab[0].begin(), KeyTab[1].begin(),
   KeyTab[2].begin(), KeyTab[3].begin(),
   KeyTab[4].begin(), KeyTab[5].begin(),
   KeyTab[6].begin()};

    QString str[7] = {"11,0 20,0 30,0 40,0 50,0 ", "10,0 21,0 30,0 40,0 50,0 ", "10,0 20,0 31,0 40,0 50,0 ", "10,0 20,0 30,0 41,0 50,0 ",
	  				"10,0 20,0 30,0 40,0 51,0 ", "11,0 21,0 31,0 41,0 51,0 ", "10,0 20,0 30,0 40,0 50,0 "};

  if(event->type() == QEvent::KeyPress) { 
 	QKeyEvent *c = dynamic_cast<QKeyEvent *>(event);
	  for (int i = 0; i < 7; i++) {
     	if (c && c->key() == *it[i]) {
			it[i]++;
			if(it[i] == KeyTab[i].end()) {
				it[i] = KeyTab[i].begin();
				if(ui->tabWidget->currentIndex() == 1) { 
				  tabKey[i] = true;
				  if(i == 6)
					_slider->setZero();
				}
				else
					Icons(str[i]);
	  		}
		}
	  }
  }
  else if(event->type() == QEvent::KeyRelease) {
	QKeyEvent *c = dynamic_cast<QKeyEvent *>(event);
	if(c && !c->isAutoRepeat()) {
	  	for (int i = 0; i < 7; i++) {
		  it[i] = KeyTab[i].begin();
	  tabKey[i] = false;
		}
	}
  }
  return false;
}

window::~window()
{
  /***** destructeur *****/
  delete ui;
}
