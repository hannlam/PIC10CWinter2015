/** @file instructions.h
    @author Hann Lam Woo
    @date March 13, 2015
    @brief This is a header file for the instructions class.
    This file contains the list of functions and variable used in instructions.\n
    The instructions class contains the instructions of the game.\n
*/

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "mainwindow.h"


class MainWindow;

/** @class instructions
    @brief The instructions class contains the instructions of the game.\n
*/

class instructions : public QWidget
{
    Q_OBJECT

public:
    explicit instructions(QWidget *parent = 0);
    ~instructions();

private:
    MainWindow* mw;
};

#endif // INSTRUCTIONS_H
