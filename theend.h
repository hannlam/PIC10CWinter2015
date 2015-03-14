/** @file theend.h
    @author Hann Lam Woo
    @date March 13, 2015
    @brief This is a header file for the theend class.
    This file contains the list of functions and variable used in theend.\n
    The gameover class is evoked when the player survives the whole game.\n
    This class allows players to play again or end game.\n
*/

#ifndef THEEND_H
#define THEEND_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"

class theend;
class gameboard;

/** @class theend
    @brief The gameover class is evoked when the player survives the whole game.\n
    This class allows players to play again or end game.\n
*/

class theend : public QWidget
{
    Q_OBJECT

public:
    explicit theend(QWidget *parent = 0);
    ~theend();
   void setGameboard(gameboard* b);

private:
   QLabel* message;
   QPushButton* retry;
   QPushButton* no;
   gameboard* board;
};

#endif // THEEND_H
