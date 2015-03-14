/** @file mainwindow.cpp
    @author Hann Lam Woo
    @brief This is the main source file for the MainWindow class.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/** This function initializes the MainWindow object.
    @param parent is the QWidget object assigned to the MainWindow object
    @param start_button is the QPushButton to start the game
    @param difficulty is the QButtonGroup object holding the difficulty options
    @param reasy is the QRadioButton set for easy
    @param rmedium is the QRadioButton set for medium
    @param rhard is the QRadioButton set for hard
    @param rninja is the QRadioButton set for ninja mode
    @param characters is the QButtonGroup object holding the character options
    @param pikachu is the QRadioButton set for pikachu
    @param charmander is the QRadioButton set for charmander
    @param squirtle is the QRadioButton set for squirtle
    @param bulbasaur is the QRadioButton set for bulbasaur
    @param board is the gameboard object in the MainWindow object
    @param in is the instruction object in the MainWindow object
    @param welcome is the label for "Pokemon Ninja"
    @param diff is the QGroupBox for difficulty options
    @param poke is the QGroupBox for pokemon options
    @param diffs is the layout holding the difficulty options
    @param pokemons is the layout holding the pokemon options
    @param final_layout is the final layout for MainWindow
    @param instruction is the QPushButton to evoke the instructions window
    @param central is the main Widget set for the Main Window object
    */


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setStyleSheet("background-color:#AA1919; color : white; font-weight:bold;");
    setFixedSize(570,500);

    /// Labels for welcome and categories
    welcome = new QLabel();
    QPixmap* title = new QPixmap(":/images/icons/title.png");
    welcome->setPixmap(*title);
    welcome->setScaledContents(true);
    welcome->setFixedSize(500,105);

    /// RadioButtons for the difficulties
    reasy = new QRadioButton("Easy");
    rmedium = new QRadioButton("Medium");
    rhard = new QRadioButton("Hard");
    rninja = new QRadioButton("Ninja");

    /// Adding buttons to ButtonGroup
    difficulty = new QButtonGroup();
    difficulty->addButton(reasy);
    difficulty->addButton(rmedium);
    difficulty->addButton(rhard);
    difficulty->addButton(rninja);

    /// Layout to make the difficulties line up
    diffs = new QVBoxLayout;
    diffs->addWidget(reasy);
    diffs->addWidget(rmedium);
    diffs->addWidget(rhard);
    diffs->addWidget(rninja);

    /// Setting up ButtonGroup
    diff = new QGroupBox(tr("Difficulty:"));
    diff->setLayout(diffs);

    instruction = new QPushButton("Instructions");
    instruction->setFixedSize(300,100);
    instruction->setStyleSheet("background-color : #83D6FF; color : black; border: 4px solid black;");
    QFont f( "Verdana", 40, QFont::Bold);
    instruction->setFont(f);
    QHBoxLayout* diff_instr = new QHBoxLayout();
    diff_instr->addWidget(diff);
    diff_instr->addWidget(instruction);


    /// Setting Pokemon selection

    characters = new QButtonGroup();
    pikachu = new QRadioButton();
    charmander = new QRadioButton();
    squirtle = new QRadioButton();
    bulbasaur = new QRadioButton();

    QIcon* p = new QIcon(":/images/icons/pika.png");
    pikachu->setIcon(*p);
    pikachu->setIconSize(QSize(100,100));

    QIcon* c = new QIcon(":/images/icons/char.png");
    charmander->setIcon(*c);
    charmander->setIconSize(QSize(100,100));

    QIcon* s = new QIcon(":/images/icons/squirt.png");
    squirtle->setIcon(*s);
    squirtle->setIconSize(QSize(100,100));

    QIcon* b = new QIcon(":/images/icons/bulb.png");
    bulbasaur->setIcon(*b);
    bulbasaur->setIconSize(QSize(100,100));



    characters->addButton(pikachu);
    characters->addButton(charmander);
    characters->addButton(squirtle);
    characters->addButton(bulbasaur);

    pokemons = new QHBoxLayout();
    pokemons->addWidget(pikachu);
    pokemons->addWidget(charmander);
    pokemons->addWidget(squirtle);
    pokemons->addWidget(bulbasaur);

    poke = new QGroupBox(tr("Pokemon:"));
    poke->setLayout(pokemons);



    ///Initializing start button
    start_button = new QPushButton("START");
    start_button->setFixedSize(200,70);
    start_button->setFont(f);
    start_button->setStyleSheet("background-color : #83D6FF; color : black; border: 4px solid black;");


    /// Piece together the welcome message and two columns together
    final_layout = new QVBoxLayout;

    final_layout->addWidget(welcome);
    final_layout->addLayout(diff_instr);
    final_layout->addWidget(poke);
    final_layout->addWidget(start_button);
    final_layout->setAlignment(welcome, Qt::AlignCenter);
    final_layout->setAlignment(start_button, Qt::AlignCenter);

    central = new QWidget;
    central->setLayout(final_layout);

    this->setCentralWidget(central);

}

/** This is a destructor for MainWindow object */
MainWindow::~MainWindow()
{

}

/** This function sets the gameboard object in the MainWindow object
    @param game_board is set to the gameboard object in MainWindow
    */
void MainWindow::setGameBoard(gameboard* game_board)
{
    board = game_board;

    QObject::connect(start_button, SIGNAL(clicked()), board, SLOT(startGame()));


}

/** This function sets the instructions object in MainWindow
    @param i is set to the instructions object in MainWindow
 */
void MainWindow::setInstructionsWindow(instructions* i)
{
    in = i;
    QObject::connect(instruction, SIGNAL(clicked()), in, SLOT(show()));
}

/** This function is evoked when the window is closed
    @param event is called when the close button is clicked
   */

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Application"),
                 tr("Are you sure you want to quit?"),
                 QMessageBox::No | QMessageBox::Yes);
    if(ret == QMessageBox::No) event->ignore();
    else this->close();
}
