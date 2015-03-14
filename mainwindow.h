/** @file mainwindow.h
    @author Hann Lam Woo
    @date March 13, 2015
    @brief This is a header file for the MainWindow class.
    This file contains the list of functions and variable used in MainWindow.\n
    The MainWindow class is the first window of the game. It allows players to choose their level of difficulty and their Pokemon character.\n
    There is also an Instructions button for players does not know how the game is played. The start button is also in this MainWindow class.\n
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "gameboard.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <iostream>
#include <QRadioButton>
#include "instructions.h"
#include <QGroupBox>


class gameboard;
class instructions;

/** @class MainWindow
    @brief The MainWindow class is the first window of the game. It allows players to choose their level of difficulty and their Pokemon character.\n
    There is also an Instructions button for players does not know how the game is played. The start button is also in this MainWindow class.\n
*/


class MainWindow : public QMainWindow
{
    Q_OBJECT

 public slots:

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton* start_button;

    ~MainWindow();

    void setGameBoard(gameboard* game_board);
    void setInstructionsWindow(instructions* i);

    QButtonGroup* difficulty;
    QRadioButton* reasy;
    QRadioButton* rmedium;
    QRadioButton* rhard;
    QRadioButton* rninja;

    QButtonGroup* characters;
    QRadioButton* pikachu;
    QRadioButton* charmander;
    QRadioButton* squirtle;
    QRadioButton* bulbasaur;



protected:
    void closeEvent(QCloseEvent *event);



private:
    gameboard* board;
    instructions* in;

    QLabel* welcome;

    QGroupBox* diff;
    QGroupBox* poke;


    QVBoxLayout* diffs;
    QHBoxLayout* pokemons;
    QVBoxLayout* final_layout;


    QPushButton* instruction;
    QWidget* central;

};

#endif // MAINWINDOW_H
