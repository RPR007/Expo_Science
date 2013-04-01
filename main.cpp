/* main.cpp
 *
 * Creer par Rafael Prevost
 *
 * Role : afficher la fenetre principal
 *
 */

#include <QApplication>
#include <QtGui>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    window __window;
    __window.show();

    return app.exec();
}

