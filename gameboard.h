/** @file gameboard.h
    @author Hann Lam Woo
    @date March 13, 2015
    @brief This is a header file for the gameboard class.
    This file contains the list of functions and variable used in gameboard.\n
    This gameboard is where the game is played.\n
*/


#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <chrono>
#include <random>
#include <iostream>
#include <QTimer>
#include <QKeyEvent>
#include <QHBoxLayout>
#include "LCDnumber.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "gameover.h"
#include <QProgressBar>
#include "theend.h"

class MainWindow;
class gameboard;
class gameover;
class theend;

/** @class gameboard
    @brief This is game board class containing the play area, timer, health bar and score board is.
*/
class gameboard : public QWidget
{
    Q_OBJECT

public slots:
    void updateObjects();
    void startGame();
    void after_thunder();
    void restart();
    void updateBar();
    void renew_powerup();

public:
    explicit gameboard(QWidget *parent = 0);
    ~gameboard();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void updatePokemon(int px, int py, int nx, int ny);
    void gamedone();
    void setMainWindow(MainWindow* main_window);

    void thunder(int px, int py);
    void setGameover(gameover* g);
    void setTheend(theend* e);
    void unicorn_level();
    void ulti();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;



private:
    ///Setting mainWindow
    MainWindow* mw;
    gameover* end;
    theend* congrats;

    ///Setting the game
    QTimer *timer;
    bool game_over = false;
    int c = 0;

    ///Board Size
    int x_axis;
    int y_axis;

    /** Board features */
    QWidget* board;
    QLabel** labels;
    int* values;
    int pokeballs;
    int stones;
    int chanseys;
    int items;
    int special;


    /// Icons
    QPixmap* pokemon;
    QPixmap* pokeball;
    QPixmap* stone;
    QPixmap* chansey;

    ///Item
    QPixmap* item;
    QPixmap* impact;
    int t_x;
    int t_y;
    QLabel* powerup;


    /// Pokemon's position
    QPoint* p_position;

    /// Pokeball and Stone positions
    QPoint* pokeball_positions;
    QPoint* stone_positions;
    QPoint* chansey_positions;
    QPoint* item_positions;

    /// Health bar
    QLabel** lives;
    QLabel* life;
    QPixmap* heart_img;
    int max_life;
    int lives_left;

    ///Scoreboard and Timer
    QProgressBar* progress;
    QTimer* prog_time;
    int prog;
    bool active = false;
    QLabel* ready;

    QLabel* timer_lcd;
    LCDNumber *clock;
    QLabel* score_lcd;
    int points = 0;
    int multiplier = 1;
};

#endif // GAMEBOARD_H
