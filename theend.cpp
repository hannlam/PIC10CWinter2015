/** @file theend.cpp
    @author Hann Lam Woo
    @brief This is the main source file for the theend class.
*/

#include "theend.h"
#include "ui_theend.h"

/** This function initializes the theend object
    @param parent sets the QWidget object in the theend object
    @param message stores the theend message
    @param retry is the retry QPushButton
    @param no is the no QPushButton
    @param board is the gameboard object in the theend object
   */

theend::theend(QWidget *parent) :
    QWidget(parent)
{
    QPixmap* togepi = new QPixmap(":/images/icons/togepi.png");


    QLabel* c = new QLabel;
    c->setPixmap(*togepi);
    c->setScaledContents(true);
    c->setFixedSize(200, 200);

    QFont t( "Verdana", 15, QFont::Bold);
    message = new QLabel("Congratulations! You survived this game!\nRetry?");
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

/** This function sets the gameboard object in the theend object
    @param b sets the board in the theend object
    */

void theend::setGameboard(gameboard * b)
{
    board = b;

    QObject::connect(retry,SIGNAL(clicked()), board,SLOT(restart()));
    QObject::connect(no,SIGNAL(clicked()), this,SLOT(close()));

}

theend::~theend()
{

}
