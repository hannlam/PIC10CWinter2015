/** @file gameover.cpp
    @author Hann Lam Woo
    @brief This is the main source file for the gameover class.
*/

#include "gameover.h"
#include "ui_gameover.h"

/** This function initializes the gameover object
    @param parent sets the QWidget object in the gameover object
    @param message stores the gameover message
    @param retry is the retry QPushButton
    @param no is the no QPushButton
    @param board is the gameboard object in the gameover object
   */
gameover::gameover(QWidget *parent):
    QWidget(parent)
{
    QPixmap* sad = new QPixmap(":/images/icons/sad.jpg");


    QLabel* c = new QLabel;
    c->setPixmap(*sad);
    c->setScaledContents(true);
    c->setFixedSize(200, 150);

    QFont t( "Verdana", 15, QFont::Bold);
    message = new QLabel("Game Over. Retry?");
    message->setFont(t);
    retry = new QPushButton("Retry");
    no = new QPushButton("No");

    QHBoxLayout* overall = new QHBoxLayout();
    QVBoxLayout* right = new QVBoxLayout;
    QHBoxLayout* buttons =  new QHBoxLayout();
    buttons->addWidget(retry);
    buttons->addWidget(no);

    right->addWidget(message);
    right->addLayout(buttons);

    overall->addWidget(c);
    overall->addLayout(right);
    setLayout(overall);
}

/** This function sets the gameboard object in the gameover object
    @param b sets the board in the gameover object
    */

void gameover::setGameboard(gameboard * b)
{
    board = b;

    QObject::connect(retry,SIGNAL(clicked()), board,SLOT(restart()));
    QObject::connect(no,SIGNAL(clicked()), this,SLOT(close()));

}

/** This destructs the gameover object */
gameover::~gameover()
{

}
