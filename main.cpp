/** @file main.cpp
    @author Hann Lam Woo
    @brief This is the main source file.
*/

#include "gameboard.h"
#include "mainwindow.h"
#include "instructions.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* mw = new MainWindow;
    gameboard* g = new gameboard;
    instructions* i = new instructions;
    gameover* go = new gameover;
    theend* t = new theend;

    g->setGameover(go);
    mw->setGameBoard(g);
    g->setMainWindow(mw);
    go->setGameboard(g);
    g->setTheend(t);
    t->setGameboard(g);


    mw->setInstructionsWindow(i);

    mw->show();

    return a.exec();
}
