/** @file instructions.cpp
    @author Hann Lam Woo
    @brief This is the main source file for the instructions class.
*/

#include "instructions.h"
#include "ui_instructions.h"

instructions::instructions(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(650,920);

    QPixmap* pokeball = new QPixmap(":/images/icons/pokeball.png");
    QPixmap* chansey = new QPixmap(":/images/icons/chansey.png");
    QPixmap* stone = new QPixmap(":/images/icons/thunderstone.png");
    QPixmap* bolt = new QPixmap(":/images/icons/thunderbolt.png");
    QPixmap* ulti = new QPixmap(":/images/icons/progress_bar.png");
    QPixmap* unicorn = new QPixmap(":/images/icons/unicorn.png");
    QPixmap* rainbow = new QPixmap(":/images/icons/rainbow_stone.png");


    QLabel* p = new QLabel;
    p->setPixmap(*pokeball);
    p->setScaledContents(true);
    p->setFixedSize(80, 80);

    QLabel* c = new QLabel;
    c->setPixmap(*chansey);
    c->setScaledContents(true);
    c->setFixedSize(80, 80);

    QLabel* s = new QLabel;
    s->setPixmap(*stone);
    s->setScaledContents(true);
    s->setFixedSize(80, 80);

    QLabel* b = new QLabel;
    b->setPixmap(*bolt);
    b->setScaledContents(true);
    b->setFixedSize(80, 80);

    QLabel* bar = new QLabel;
    bar->setPixmap(*ulti);
    bar->setScaledContents(true);
    bar->setFixedSize(120, 60);

    QLabel* u = new QLabel;
    u->setPixmap(*unicorn);
    u->setScaledContents(true);
    u->setFixedSize(80, 80);

    QLabel* r = new QLabel;
    r->setPixmap(*rainbow);
    r->setScaledContents(true);
    r->setFixedSize(80, 80);

    QHBoxLayout* first = new QHBoxLayout;
    first->addWidget(p);
    first->addWidget(new QLabel("Encountering the pokeball will reduce life by one"));

    QHBoxLayout* second = new QHBoxLayout;
    second->addWidget(c);
    second->addWidget(new QLabel("Encountering Chansey will heal your life by one"));

    QHBoxLayout* third = new QHBoxLayout;
    third->addWidget(s);
    third->addWidget(new QLabel("Encountering a stone will earn:\n- 10 points for easy\n- 20 points for medium\n- 40 points for hard\n- 80 points for ninja"));

    QHBoxLayout* fourth = new QHBoxLayout;
    fourth->addWidget(b);
    fourth->addWidget(new QLabel("Encountering an item will allow you to use a skill.\nPress SPACEBAR to activate the skill."));

    QHBoxLayout* fifth = new QHBoxLayout;
    fifth->addWidget(bar);
    fifth->addWidget(new QLabel("When the bar is fully loaded, press the Z key to activate your ultimate attack.\nThe label will show READY when the bar is fully loaded."));

    QHBoxLayout* sixth = new QHBoxLayout;
    sixth->addWidget(u);
    sixth->addWidget(new QLabel("You have to EVADE THE UNICORNS or else it will take one health from you.\nDo not be fooled by it's cuteness."));

    QHBoxLayout* seventh = new QHBoxLayout;
    seventh->addWidget(r);
    seventh->addWidget(new QLabel("Encountering a rainbow will DOUBLE the points that you will receive."));


    setStyleSheet("background-color:#AA1919; color : white; font-weight: bold");
    QFont f( "Verdana", 12);
    QFont t( "Verdana", 24, QFont::Bold);
    QFont ul( "Verdana", 20, QFont::Bold);

    /// Labels for welcome and categories
    QLabel* title = new QLabel ("Instructions");
    title->setFont(t);

    QLabel* unicorn_level = new QLabel ("Unicorn Level");
    unicorn_level->setFont(ul);

    QLabel* welcome = new QLabel("The goal of this game is to achieve the highest number of points possible. You will navigate Pikachu on the gameboard using your keypad. You will have 5 lives and 2 minutes and 30 seconds to play the game.\n\nWhen you reach the 1 minute mark, you will be transported to Unicorn land and your game speed will increase. It is awesome.\n\nEach character will have a specific stone and skill. The game will end when the time is up or when you have lost all your lives. ");
    welcome->setWordWrap(true);
    welcome->setFont(f);
    welcome->setStyleSheet("QLabel { background-color : #83D6FF; color : black; border: 4px solid black; padding : 10px; }");
    QVBoxLayout* middle = new QVBoxLayout;
    middle->addWidget(title);
    middle->addWidget(welcome);
    middle->addLayout(first);
    middle->addLayout(second);
    middle->addLayout(third);
    middle->addLayout(fourth);
    middle->addLayout(fifth);
    middle->addWidget(unicorn_level);
    middle->setAlignment(unicorn_level,Qt::AlignCenter);
    middle->addLayout(sixth);
    middle->addLayout(seventh);
    setLayout(middle);

}

instructions::~instructions()
{

}
