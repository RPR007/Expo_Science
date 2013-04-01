/* shortcut.cpp
 *
 * Creer par Rafael Prevost
 *
 * Role : Coder les methodes de la classe shortcut
 *
 */

#include "shortcut.h"
#include "ui_shortcut.h"

shortcut::shortcut(vector<int > KeyTab[8], QString keyStr[], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shortcut)
{
  /***** Constructeur *****/

  ui->setupUi(this);
  ui->tableWidget->installEventFilter(this);

  _KeyTab = KeyTab; // _KeyTab pointe sur KeyTab
  _keyStr = keyStr; // _KeyStr pointe sur KeyStr

  init();
	
  // Connexion en signaux
  QObject::connect(ui->ok, SIGNAL(clicked()), this, SLOT(saved()));
  QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(hide()));
}

void shortcut::init() {
  /****** Initialisation *****/

  vector<int>::iterator it;
  int i;
	
  release = true;
  for(i = 0; i < 8; i++) {
  	for(it = _KeyTab[i].begin(); it!=_KeyTab[i].end(); it++) {
  		savedKey[i].push_back(*it);
  	}
  	s = savedStr[i] = _keyStr[i];
  	setShortcut(i, 1);
  }
}

void shortcut::saved() {
  /****** Sauvegarde des raccourcis claviers ******/

    vector<int>::iterator it;
    
	for(int i = 0; i < 8; i++) {
		_KeyTab[i].clear();
    	for(it = savedKey[i].begin(); it!=savedKey[i].end(); ++it)
    	{
			_KeyTab[i].push_back(*it);
    	}
		_keyStr[i] = savedStr[i];
	}

  // Fermeture du dialogue
  hide();
}

void shortcut::setShortcut(int row, int colum) {
  /***** Raccourcis clavier dans le tableau *****/

  ui->tableWidget->item(row,colum)->setText(s);
}

bool shortcut::eventFilter(QObject *object, QEvent *event) {
  /***** Gestion des evenements *****/
  int i;
  
  struct {
	QString s;
	int val;
  } _key[] = {
	{"Meta", Qt::Key_Meta},
	{"Shift", Qt::Key_Shift},
	{"Ctrl", Qt::Key_Control},
	{"Alt", Qt::Key_Alt},
	{"Q", Qt::Key_Q},
	{"W", Qt::Key_W},
	{"E", Qt::Key_E},
	{"R", Qt::Key_R},
	{"T", Qt::Key_T},
	{"Y", Qt::Key_Y},
	{"U", Qt::Key_U},
	{"I", Qt::Key_I},
	{"O", Qt::Key_O},
	{"P", Qt::Key_P},
	{"A", Qt::Key_A},
	{"S", Qt::Key_S},
	{"D", Qt::Key_D},
	{"F", Qt::Key_F},
	{"G", Qt::Key_G},
	{"H", Qt::Key_H},
	{"J", Qt::Key_J},
	{"K", Qt::Key_K},
	{"L", Qt::Key_L},
	{"Z", Qt::Key_Z},
	{"X", Qt::Key_X},
	{"C", Qt::Key_C},
	{"V", Qt::Key_V},
	{"B", Qt::Key_B},
	{"N", Qt::Key_N},
	{"M", Qt::Key_M},
	{"1", Qt::Key_1},
	{"2", Qt::Key_2},
	{"3", Qt::Key_3},
	{"4", Qt::Key_4},
	{"5", Qt::Key_5},
	{"6", Qt::Key_6},
	{"7", Qt::Key_7},
	{"8", Qt::Key_8},
	{"9", Qt::Key_9},
	{"0", Qt::Key_0},
  };


  if(event->type() == QEvent::KeyPress) { 
 	QKeyEvent *c = dynamic_cast<QKeyEvent *>(event);
  	if(_isSelected()) {
	  for (i = 0; i < 40; i++) {
		if(c && c->key() == _key[i].val) {
			if(!release) {
				s += "+" + _key[i].s;
				savedKey[selectedRow].push_back(_key[i].val);
			}
			else {
				savedKey[selectedRow].clear();
				savedKey[selectedRow].push_back(_key[i].val);
				s = _key[i].s;
				release = false;
			}
			savedStr[selectedRow] = s; 
		  	setShortcut(selectedRow, selectedColum);
  	  	}
 	  }
  	}
  }
  else if(event->type() == QEvent::KeyRelease) {
	QKeyEvent *c = dynamic_cast<QKeyEvent *>(event);
	if(c && !c->isAutoRepeat())
		release = true;
  }

  return false;
}

bool shortcut::_isSelected() {
  /***** Quel colone et quel ligne a ete selectionne *****/

  for ( int i = 0; i < 8; i ++) {
	if(ui->tableWidget->item(i,1)->isSelected()) {
		selectedRow = i;
		selectedColum = 1;
		return true;
	}
  }

  return false;
}

shortcut::~shortcut()
{
  /****** destructeur *****/

  delete ui;
}
