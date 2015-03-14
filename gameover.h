/** @file gameover.h
    @author Hann Lam Woo
    @date March 13, 2015
    @brief This is a header file for the gameover class.
    This file contains the list of functions and variable used in gameover.\n
    The gameover class is evoked when the player has no more health before the timer ends.\n
    This class allows players to play again or end game.\n
*/

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QPushButton>
#include "mainwindow.h"


class gameboard;


/** @class gameover
    @brief The gameover class is evoked when the player has no more health before the timer ends.\n
    This class allows players to play again or end game.\n
*/

class gameover : public QWidget
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = 0);
    void setGameboard(gameboard* b);
    ~gameover();

private:
    QLabel* message;
    QPushButton* retry;
    QPushButton* no;
    gameboard* board;

};

#endif // GAMEOVER_H
