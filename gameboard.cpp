/** @file gameboard.cpp
    @author Hann Lam Woo
    @brief This is the main source file for the gameboard class.
*/

#include "gameboard.h"
#include "ui_gameboard.h"

/************* Random number generator for positions of pokeballs ************/
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> p(-80,0);
std::uniform_int_distribution<int> l(-1500,-300);
std::uniform_int_distribution<int> t(-200,-10);

/** Creates a gameboard object based on the paramenters which are set
    @param parent is the Qwidget object
    @param x_axis is the size of the board on the x_axis
    @param y_axis is the size of the board on the y_axis
    @param max_life is the maximum life set for the gameboard
    @param mw is the MainWindow object attached to this gameboard
    @param end is the gameover object attached to this gameboard
    @param congrats is the theend object attached to this gameboard
    @param timer is the timer set for updateObject()
    @param game_over checks whether the game is over or not
    @param c stores information on the type of character
    @param board is the widget storing the labels of the board
    @param labels is an array of all QLabels for the board
    @param values is an array of int containing all the values on the board
    @param pokeballs is the number of pokeball objects in the board
    @param stones is the number of stone objects in the board
    @param chanseys is the number of chansey objects in the board
    @param items is the number of item objects in the board
    @param special checks whether there is a powerup available
    @param pokemon is the pokemon image
    @param pokeball is the pokeball image
    @param stone is the stone image
    @param chansey is the chansey image
    @param item is the item image
    @param impact is the impact image
    @param t_x is the x position of the pokemon when calling the thunder() function
    @param t_y is the y position of the pokemon when calling the thunder() function
    @param power is the label indicating the powerup
    @param p_position is the position of the pokemon
    @param pokeball_positions is the array storing pokeball positions
    @param stone_positions is the array storing stone positions
    @param chansey_positions is the array storing chansey positions
    @param item_positions is the array storing item positions
    @param lives stores the icons of all the hearts
    @param life is the image to store the lives
    @param heart_img is the heart image
    @param lives_left keeps track of the user's health
    @param progress tracks the time until the player can use his ultimate move
    @param prog_time is the timer keeping incrementing the progress bar
    @param prog is the value in the progress bar
    @param active checks if the ultimate move is ready
    @param ready shows the user when the ultimate move is ready
    @param timer_lcd is the timer object on the board
    @param clock keeps track of time
    @param score_lcd displays the score
    @param points keeps track of the player's points
    @param multiplier sets the points multiplier

 */
gameboard::gameboard(QWidget *parent) :
    QWidget(parent), x_axis(10), y_axis(15), max_life(5)
{
    /**************************** Setting up the layout of the board *********************/
    /// Setting color of the board
    setStyleSheet("background-color:#AA1919;");

    board = new QWidget;
    labels = new QLabel*[x_axis*y_axis];
    QGridLayout *SquareGrid = new QGridLayout(board);
    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);
    values = new int[x_axis*y_axis];

    /// Assigning all the values on the board to be 0
    for(int i=0;i<y_axis;i++) {
            for(int j=0;j<x_axis;j++) {

                /// Assigning all the values to 0
                values[i*x_axis+j] = 0;

                /// Create label and set properties.
                labels[i*x_axis+j] = new QLabel;
                //labels[i*x_axis+j]->setText(QString::number( values[i*x_axis+j]));
                labels[i*x_axis+j]->setMinimumSize(40,40);
                labels[i*x_axis+j]->setMaximumSize(40,40);
                //labels[i*x_axis+j]->setStyleSheet("QLabel { background-color : black; color : white; }");
                labels[i*x_axis+j]->setStyleSheet("QLabel { background-color : black; }");
                labels[i*x_axis+j]->setFrameStyle(3);
                labels[i*x_axis+j]->setAlignment(Qt::AlignCenter);

                /// Add label to the layout
                SquareGrid -> addWidget(labels[i*x_axis+j] ,i,j);

            }
        }

    /******************************  Setting elements on the board **********************/

    pokeballs = x_axis;
    stones = x_axis;
    chanseys = x_axis;
    items = x_axis;

    /************** Icon images **************/

    QString filename_pika(":/images/icons/pikachu.png");
    pokemon = new QPixmap(filename_pika);

    /// Pokeball image
    QString filename_poke(":/images/icons/pokeball.png");
    pokeball = new QPixmap(filename_poke);

    /// Stone image
    QString filename_stone(":/images/icons/thunderstone.png");
    stone = new QPixmap(filename_stone);

    /// Chansey image
    QString filename_chansey(":/images/icons/chansey.png");
    chansey = new QPixmap(filename_chansey);

    /// Item image
    QString filename_item(":/images/icons/thunderbolt.png");
    item = new QPixmap(filename_item);

    /// Impact image
    QString filename_impact(":/images/icons/bolt.png");
    impact = new QPixmap(filename_impact);

    /** Pikachu */

    ///Setting Pikachu's position
    p_position = new QPoint(5,14);
    values[p_position->ry()*x_axis+p_position->rx()] = -12345;


    /** Pokeballs */

    /// Creating an array of Pokeballs
     pokeball_positions = new QPoint[pokeballs];

     /// Creating pokeball objects and setting their value to -1
     for (int i = 0; i < pokeballs; i++)
     {
         std::cout<< "Pokeball: " << i << ": ";
         pokeball_positions[i].setX(i);
         pokeball_positions[i].setY(p(generator));
         std:: cout << "(" << pokeball_positions[i].rx() << ", " << pokeball_positions[i].ry() << ")" << std::endl;
         if (pokeball_positions[i].ry() >= 0) values[pokeball_positions[i].ry()*x_axis+pokeball_positions[i].rx()] = -1;

     }

     /** Stones */

     /// Creating an array of stones
     stone_positions = new QPoint[stones];

     /// Creating stone objects and setting their value to 1
     for (int i = 0; i < stones; i++)
     {
         std::cout<< "Stone: " << i << ": ";
         stone_positions[i].setX(i);
         stone_positions[i].setY(p(generator));
         std:: cout << "(" << stone_positions[i].rx() << ", " << stone_positions[i].ry() << ")" << std::endl;
         if (stone_positions[i].ry() >= 0) values[stone_positions[i].ry()*x_axis+stone_positions[i].rx()] = 1;

     }

     /** Chansey */

     /// Creating an array of chanseys
     chansey_positions = new QPoint[chanseys];

     /// Creating chansey objects and setting their value to 2
     for (int i = 0; i < chanseys; i++)
     {
         std::cout<< "Chansey: " << i << ": ";
         chansey_positions[i].setX(i);
         chansey_positions[i].setY(l(generator));
         std:: cout << "(" << chansey_positions[i].rx() << ", " << chansey_positions[i].ry() << ")" << std::endl;
         if (chansey_positions[i].ry() >= 0) values[chansey_positions[i].ry()*x_axis+chansey_positions[i].rx()] = 2;

     }

     /** Item */

     /// Creating an array of items
     item_positions = new QPoint[items];

     /// Creating item objects and setting their value to 2
     for (int i = 0; i < items; i++)
     {
         std::cout<< "Item: " << i << ": ";
         item_positions[i].setX(i);
         item_positions[i].setY(t(generator));
         std:: cout << "(" << item_positions[i].rx() << ", " << item_positions[i].ry() << ")" << std::endl;
         if (item_positions[i].ry() >= 0) values[item_positions[i].ry()*x_axis+item_positions[i].rx()] = 2;

     }


     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateObjects()));

     board->setFixedSize(400,600);
     setFixedSize(720,720);

     /** Creating a progress bar */

     progress = new QProgressBar;
     prog_time = new QTimer(this);
     connect(prog_time,SIGNAL(timeout()), this, SLOT(updateBar()));
     ready = new QLabel;
     QFont r( "Callibri", 20, QFont::Bold);
     ready->setFont(r);
     ready->setAlignment(Qt::AlignCenter);
     ready->setStyleSheet("QLabel { background-color : #83D6FF; color : black; border: 4px solid black; padding : 10 px }");

     /** Creating life bar */

     /// Background health
     QLabel* back = new QLabel();
     back->setFixedSize(280,55);
     back->setStyleSheet("QLabel {  background-color : black; }");

     /// Health bar
     QString filename_life(":/images/icons/heart.png");
     heart_img = new QPixmap(filename_life);
     QHBoxLayout* health = new QHBoxLayout;
     lives = new QLabel*[max_life];
     lives_left = max_life;

     for (int i = 0; i < max_life; i++)
     {
         lives[i] = new QLabel;
         lives[i]->setFixedSize(33,33);
         lives[i]->setAlignment(Qt::AlignCenter);
         lives[i]->setPixmap(*heart_img);
         lives[i] ->setScaledContents(true);
         health->addWidget(lives[i]);
         health->setAlignment(lives[i],Qt::AlignCenter);
     }

     back->setLayout(health);


     /** Creating a Timer */

     /// Timer
     timer_lcd = new QLabel;
     clock = new LCDNumber(timer_lcd,2,30);
     clock->setFixedSize(280, 150);
     QFont f( "Callibri", 60, QFont::Bold);
     clock->setFont(f);
     clock->setAlignment(Qt::AlignCenter);
     clock->setStyleSheet("QLabel { background-color : #83D6FF; color : black; border: 4px solid black; padding : 10 px }");


     /** Creating Power up label */
     QFont p( "Callibri", 30, QFont::Bold);
     powerup = new QLabel;
     powerup->setFont(p);
     powerup->setWordWrap(true);
     powerup->setFixedSize(280,280);
     powerup->setStyleSheet("QLabel { background-color : #83D6FF; color : black; border: 4px solid black; padding : 15px;}");

     /** Creating a score board */

     score_lcd = new QLabel;
     score_lcd->setNum(points);
     score_lcd->setFixedSize(280,100);
     score_lcd->setFont(f);
     score_lcd->setAlignment(Qt::AlignCenter);
     score_lcd->setStyleSheet("QLabel { background-color : #83D6FF; color : black; border: 4px solid black; }");


    /** Setting layout for the widget */

    QLabel* lights = new QLabel;
    QPixmap* l = new QPixmap(":/images/icons/pokedex_lights.png");
    lights->setPixmap(*l);
    lights->setScaledContents(true);
    lights->setFixedSize(200,73);

    QVBoxLayout* p_bar = new QVBoxLayout;
    p_bar->addWidget(ready);
    p_bar->addWidget(progress);

    QHBoxLayout* top_left = new QHBoxLayout;
    top_left->addWidget(lights);
    top_left->setAlignment(lights,Qt::AlignLeft);
    top_left->addLayout(p_bar);

    QVBoxLayout* left = new QVBoxLayout;
    left->addLayout(top_left);
    left->addWidget(board);

    QVBoxLayout* right = new QVBoxLayout;
    right->addWidget(back);
    right->addWidget(clock);
    right->addWidget(powerup);
    right->addWidget(score_lcd);

    QHBoxLayout* whole = new QHBoxLayout;
    whole->addLayout(left);
    whole->addLayout(right);
    setLayout(whole);




}

/** This is the paint function
    @param e is the QPaintEvent function
 */

void gameboard:: paintEvent(QPaintEvent *e)
{
    if(!game_over){
    //std::cout<< "Paint is happening" << std::endl;

    /// If time runs out
    if(clock->getSeconds() == 0) gamedone();
    else if(clock->getSeconds() == 60) unicorn_level();


    /**  Painting Pikachu */
    int x = p_position->rx();
    int y = p_position->ry();

    labels[y*x_axis+x]->setPixmap(*pokemon);
    labels[y*x_axis+x]->setScaledContents(true);

    /**  Painting Pokeballs */
    for(int i=0;i<pokeballs;i++) {
        int px = pokeball_positions[i].rx();
        int py = pokeball_positions[i].ry();

        if(x== px && y == py)
        {
            /// Reset the pokeball
            py=p(generator);
            pokeball_positions[i].setY(py);
            lives_left--;
        }

        if(px >= 0 && py >= 0 && px < x_axis && py < y_axis) {
            labels[py*x_axis+px]->setPixmap(*pokeball);
            labels[py*x_axis+px]->setScaledContents(true);

        }
    }

    /**  Painting Stones */
    for(int i=0;i<stones;i++) {
        int px = stone_positions[i].rx();
        int py = stone_positions[i].ry();


        if(x== px && y == py)
        {
            /// Reset the stone
            py=p(generator);
            stone_positions[i].setY(py);
            points+=10*multiplier;
        }

        if(px >= 0 && py >= 0 && px < x_axis && py < y_axis) {
            labels[py*x_axis+px]->setPixmap(*stone);
            labels[py*x_axis+px]->setScaledContents(true);
        }
    }

    /** Painting Chanseys */
    for(int i=0;i< chanseys;i++) {
        int px = chansey_positions[i].rx();
        int py = chansey_positions[i].ry();

        if(x== px && y == py)
        {
            /// Reset the pokeball
            py=l(generator);
            chansey_positions[i].setY(py);
            if (lives_left < max_life)lives_left++;
        }

        if(px >= 0 && py >= 0 && px < x_axis && py < y_axis) {
            labels[py*x_axis+px]->setPixmap(*chansey);
            labels[py*x_axis+px]->setScaledContents(true);

        }
    }

    /**  Painting Items */
    for(int i=0;i< items;i++) {
        int px = item_positions[i].rx();
        int py = item_positions[i].ry();

        if(x== px && y == py)
        {
            /// Reset the pokeball
            py=t(generator);
            item_positions[i].setY(py);
            special = 1;
            powerup->setPixmap(*item);
            powerup->setScaledContents(true);
        }

        if(px >= 0 && py >= 0 && px < x_axis && py < y_axis) {
            labels[py*x_axis+px]->setPixmap(*item);
            labels[py*x_axis+px]->setScaledContents(true);
        }
    }

    /**  Painting Health Bar */
    for (int i = 0; i < max_life; i++)
    {
        if(i < lives_left){
            lives[i]->setPixmap(*heart_img);
            lives[i]->setScaledContents(true);
        }

        else lives[i]->clear();
    }
    if(lives_left == 0) gamedone();

    /**  Painting Score */
    score_lcd->setNum(points);



}
    game_over= true;

}

/** This function responds to the even when a button is pressed.
 */


void gameboard::keyPressEvent(QKeyEvent *event){

    int x = p_position->rx();
    int y = p_position->ry();

    switch (event->key()) {
    case Qt::Key_Left:
        if(p_position->rx() != 0)
            updatePokemon(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(p_position->rx() != x_axis-1)
            updatePokemon(x,y,x+1,y);

        break;
    case Qt::Key_Up:
        if(p_position->ry() != 0)
            updatePokemon(x,y,x,y-1);

        break;
    case Qt::Key_Down:
        if(p_position->ry() != y_axis-1)
            updatePokemon(x,y,x,y+1);

        break;

    case Qt::Key_Space:
        if(special == 1)
            thunder(x,y);
        special = 0;

        break;

    case Qt::Key_Z:
        if(active)
            ulti();

        break;

    case Qt::Key_X:
        unicorn_level();

        break;

    default:
        QWidget::keyPressEvent(event);
    }

     game_over= false;
     QCoreApplication::processEvents();
     update();
    return;
}

/** This function updates the position of the pokemon.
    @param px is the initial x position of the pokemon
    @param py is the initial y position of the pokemon
    @param nx is the new x position of the pokemon
    @param ny is the new y position of the pokemon
  */

void gameboard::updatePokemon(int px, int py, int nx, int ny) {
    labels[py*x_axis+px]->clear();
    values[py*x_axis+px] = 0;

    p_position->setX(nx);
    p_position->setY(ny);
    values[ny*x_axis+nx] = -12345;


}

/** This function updates the objects on the gameboard
 */


void gameboard::updateObjects()
{

    /** Update Pokeball */
     for(int i=0;i<pokeballs;i++) {
         int px = pokeball_positions[i].rx();
         int py = pokeball_positions[i].ry();


     if(px>=0 && py >= 0 && px<x_axis && py<y_axis) {
        if(values[py*x_axis+px] == -12345)
        {
            //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
        }
        else {
            labels[py*x_axis+px]->clear();
            values[py*x_axis+px] = 0;
            //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
        }
     }

     int ny = py;

     if (py == 14||values[py*x_axis+px] == -12345) ny = p(generator);
     else ny = py + 1;

     pokeball_positions[i].setY(ny);

      /// Changing current point to -1
      if(pokeball_positions[i].ry() >= 0)
      {
         if(pokeball_positions[i].rx() == p_position->rx() && pokeball_positions[i].ry() == p_position->ry() ) values[pokeball_positions[i].ry()*x_axis+pokeball_positions[i].rx()] = -12345;
         else values[pokeball_positions[i].ry()*x_axis+pokeball_positions[i].rx()] = -1;

       }

    }

     /** Update Stone */
      for(int i=0;i<stones;i++) {
          int px = stone_positions[i].rx();
          int py = stone_positions[i].ry();


      if(px>=0 && py >= 0 && px<x_axis && py<y_axis) {
          if(values[py*x_axis+px] == -12345)
          {
              //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
          }
          else {
              labels[py*x_axis+px]->clear();
              values[py*x_axis+px] = 0;
              //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
          }
      }

      int ny = py;

      if (py == 14 || values[py*x_axis+px] == -12345) ny = p(generator);
      else ny = py + 1;

      stone_positions[i].setY(ny);

       /// Changing current point to 1
       if(stone_positions[i].ry() >= 0)
       {
          if(stone_positions[i].rx() == p_position->rx() && stone_positions[i].ry() == p_position->ry() ) values[stone_positions[i].ry()*x_axis+stone_positions[i].rx()] = -12345;
          else values[stone_positions[i].ry()*x_axis+stone_positions[i].rx()] = 1;

        }

     }


      /** Update Chansey */
       for(int i=0;i< chanseys;i++) {
           int px = chansey_positions[i].rx();
           int py = chansey_positions[i].ry();


       if(px>=0 && py >= 0 && px<x_axis && py<y_axis) {
           if(values[py*x_axis+px] == -12345)
           {
               //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
           }
           else {
               labels[py*x_axis+px]->clear();
               values[py*x_axis+px] = 0;
               //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
           }
       }

       int ny = py;

       if (py == 14 || values[py*x_axis+px] == -12345) ny = l(generator);
       else ny = py + 1;

       chansey_positions[i].setY(ny);

        /// Changing current point to 2
        if(chansey_positions[i].ry() >= 0)
        {
           if(chansey_positions[i].rx() == p_position->rx() && chansey_positions[i].ry() == p_position->ry() ) values[chansey_positions[i].ry()*x_axis+chansey_positions[i].rx()] = -12345;
           else values[chansey_positions[i].ry()*x_axis+chansey_positions[i].rx()] = 2;

         }

      }


       /** Update Item */
        for(int i=0;i< items;i++) {
            int px = item_positions[i].rx();
            int py = item_positions[i].ry();


        if(px>=0 && py >= 0 && px<x_axis && py<y_axis) {
            if(values[py*x_axis+px] == -12345)
            {
                //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
            }
            else {
                labels[py*x_axis+px]->clear();
                values[py*x_axis+px] = 0;
                //labels[py*x_axis+px]->setText(QString::number( values[py*x_axis+px]));
            }
        }

        int ny = py;

        if (py == 14 || values[py*x_axis+px] == -12345) ny = t(generator);
        else ny = py + 1;

        item_positions[i].setY(ny);

         /// Changing current point to 2
         if(item_positions[i].ry() >= 0)
         {
            if(item_positions[i].rx() == p_position->rx() && item_positions[i].ry() == p_position->ry() ) values[item_positions[i].ry()*x_axis+item_positions[i].rx()] = -12345;
            else values[item_positions[i].ry()*x_axis+item_positions[i].rx()] = 2;

          }

       }

     game_over= false;
     QCoreApplication::processEvents();
     update();
}

/** This function is evoked when the game is over.
 */

void gameboard::gamedone()
{
    clock->stop();
    timer->stop();
    prog_time->stop();
    game_over = true;
    if(clock->getSeconds() == 0) congrats->show();
    else end->show();

}

/** This function sets the gameover object for the gameboard object.
    @param g is assigned to the end parameter in the gameboard object
   */

void gameboard::setGameover(gameover* g)
{
    end = g;
}

/** This function sets the theend object for the gameboard object.
    @param e is assigned to the congrats parameter in the gameboard object
   */

void gameboard::setTheend(theend* e)
{
    congrats = e;
}

/** This function is called whenever the games start or restarted
 */

void gameboard::startGame()
{
    QPixmap* charmander = new QPixmap(":/images/icons/charmander.gif");
    QPixmap* squirtle = new QPixmap(":/images/icons/squirtle.gif");
    QPixmap* bulbasaur = new QPixmap(":/images/icons/bulbasaur.gif");
    QPixmap* pikachu = new QPixmap(":/images/icons/pikachu.png");

    QPixmap* thunderstone = new QPixmap(":/images/icons/thunderstone.png");
    QPixmap* waterstone = new QPixmap(":/images/icons/waterstone.png");
    QPixmap* firestone = new QPixmap(":/images/icons/firestone.png");
    QPixmap* leafstone = new QPixmap(":/images/icons/leafstone.png");

    QPixmap* fire = new QPixmap(":/images/icons/fire.png");
    QPixmap* water = new QPixmap(":/images/icons/water.png");
    QPixmap* leaf = new QPixmap(":/images/icons/leaf.png");
    QPixmap* thunderbolt = new QPixmap(":/images/icons/thunderbolt.png");

    QPixmap* flame = new QPixmap(":/images/icons/flame.png");
    QPixmap* splash = new QPixmap(":/images/icons/splash.png");
    QPixmap* vine = new QPixmap(":/images/icons/vine.png");
    QPixmap* bolt = new QPixmap(":/images/icons/bolt.png");

    if(mw->charmander->isChecked())
    {
        pokemon->swap(*charmander);
        stone->swap(*firestone);
        item->swap(*fire);
        impact->swap(*flame);
        c = 1;

    }
    else if(mw->squirtle->isChecked())
    {
        pokemon->swap(*squirtle);
        stone->swap(*waterstone);
        item->swap(*water);
        impact->swap(*splash);
        c = 2;
    }
    else if(mw->bulbasaur->isChecked())
    {
        pokemon->swap(*bulbasaur);
        stone->swap(*leafstone);
        item->swap(*leaf);
        impact->swap(*vine);
        c = 3;
    }
    else
    {
        pokemon->swap(*pikachu);
        stone->swap(*thunderstone);
        item->swap(*thunderbolt);
        impact->swap(*bolt);
        c = 0;
    }

    show();
    if(mw->reasy->isChecked())
    {
        timer->start(200);
        multiplier = 1;
    }
    else if(mw->rmedium->isChecked())
    {
        timer->start(100);
        multiplier = 2;
    }
    else if(mw->rhard->isChecked())
    {
        timer->start(80);
        multiplier = 4;
    }
    else if (mw->rninja->isChecked())
    {
        timer->start(50);
        multiplier = 8;
    }
    else timer->start(100);


    restart();
    prog_time->start(200);
    clock->timer_lcd->start(1000);
}

/** This function is evoked when the player has a item and presses the spacebar.
    @param px is the x position of the pokemon when the function is evoked
    @param py is the y position of the pokemon when the function is evoked
 */

void gameboard::thunder(int px, int py)
{
    for (int i = 0; i < py; i++)
    {
        labels[i*x_axis + px]->setPixmap(*impact);
        labels[i*x_axis + px]->setScaledContents(true);
    }

    if(py > pokeball_positions[px].ry())pokeball_positions[px].setY(p(generator));
    if(py > stone_positions[px].ry())stone_positions[px].setY(p(generator));
    if(py > chansey_positions[px].ry())chansey_positions[px].setY(l(generator));
    if(py > item_positions[px].ry())item_positions[px].setY(t(generator));

    t_x = px;
    t_y = py;

    QTimer::singleShot(500, this, SLOT(after_thunder()));

    if(c == 0) powerup->setText("Pikachu uses Thunderbolt!");
    else if(c == 1) powerup->setText("Charmander uses Flamethrower!");
    else if(c == 2) powerup->setText("Squirtle uses Watergun!");
    else if(c == 3) powerup->setText("Bulbasaur uses Razor Leaf!");

}

/** This function clears the thunder after it is casted
 */

void gameboard::after_thunder()
{
    for (int i = 0; i < t_y; i++)
    {
        labels[i*x_axis + t_x]->clear();
    }

    powerup->clear();
}

/** This function restarts the gameboard object
 */


void gameboard::restart()
{
    QPixmap* poke = new QPixmap(":/images/icons/pokeball.png");
    QPixmap* t = new QPixmap(":/images/icons/thunderstone.png");
    QPixmap* f = new QPixmap(":/images/icons/firestone.png");
    QPixmap* w = new QPixmap(":/images/icons/waterstone.png");
    QPixmap* l = new QPixmap(":/images/icons/leafstone.png");

    if (c==0) stone->swap(*t);
    else if (c==1) stone->swap(*f);
    else if (c==2) stone->swap(*w);
    else if (c==3) stone->swap(*l);

    setStyleSheet("background-color:#AA1919;");
    pokeball->swap(*poke);



    lives_left = max_life;
    if(clock->getSeconds()==0) congrats->close();
    else end->close();
    points = 0;
    clock->restart();
    special = 0;
    powerup->clear();
    prog = 0;
    active = false;

    game_over = false;
    clock->start();
    timer->start();
    prog_time->start();
    std::cout << "Restart done" << std::endl;

    QCoreApplication::processEvents();
    update();

}

/** This function is evoked when the close button is clicked
    @param event is the event object when the close button is clicked
    */

void gameboard::closeEvent(QCloseEvent *event)
{
    game_over = true;
    timer->stop();
    clock->stop();
    prog_time->stop();
}

/** This is a gameboard destructor */

gameboard::~gameboard()
{
    delete values;
    delete pokeball_positions;
    delete stone_positions;
    delete chansey_positions;
    delete item_positions;
}

/** This function evokes the special move */

void gameboard::ulti()
{
    QPixmap* flame = new QPixmap(":/images/icons/flame.png");
    QPixmap* splash = new QPixmap(":/images/icons/splash.png");
    QPixmap* vine = new QPixmap(":/images/icons/vine.png");
    QPixmap* bolt = new QPixmap(":/images/icons/bolt.png");

    for (int i = 0; i< x_axis; i++)
    {
        int x = pokeball_positions[i].rx();
        int y = pokeball_positions[i].ry();
        if (y>= 0)
        {
            if(c==0)
            {
                labels[x_axis*y+x]->setPixmap(*bolt);
                labels[x_axis*y+x]->setScaledContents(true);
            }
            else if(c==1)
            {
                labels[x_axis*y+x]->setPixmap(*flame);
                labels[x_axis*y+x]->setScaledContents(true);
            }
            else if(c==2)
            {
                labels[x_axis*y+x]->setPixmap(*splash);
                labels[x_axis*y+x]->setScaledContents(true);
            }
            else if(c==3)
            {
                labels[x_axis*y+x]->setPixmap(*vine);
                labels[x_axis*y+x]->setScaledContents(true);
            }

            QTimer::singleShot(500, labels[x_axis*y+x],SLOT(clear()));
        }
        pokeball_positions[i].setY(p(generator));
    }
    prog = 0;
    ready->clear();
    active= false;
}

/** This function updates the progress bar */
void gameboard:: updateBar()
{
    if(prog<=100) ++prog;
    progress->setValue(prog);
    if(prog == 100)
    {
        active = true;
        ready->setText("READY");
    }
}

/** This function sets the MainWindow object in the gameboard
    @param main_window is assigned to the mw object in the gameboard
 */
void gameboard::setMainWindow(MainWindow* main_window)
{
    mw = main_window;
}

/** This function evokes the unicorn level */

void gameboard:: unicorn_level()
{
    QPixmap* unicorn = new QPixmap(":/images/icons/unicorn.png");
    QPixmap* rainbow_stone = new QPixmap(":/images/icons/rainbow_stone.png");
    timer->stop();
    setStyleSheet("background-color:#FF6CDA;");
    pokeball->swap(*unicorn);
    stone->swap(*rainbow_stone);
    multiplier*=2;

    powerup->clear();
    powerup->setText("UNICORN LEVEL!");
    QTimer::singleShot(1000, this,SLOT(renew_powerup()));

    if(mw->reasy->isChecked()) timer->start(100);
    else if(mw->rmedium->isChecked()) timer->start(80);
    else if(mw->rhard->isChecked()) timer->start(50);
    else if (mw->rninja->isChecked())timer->start(30);

}

/** This function renews the powerup panel if there are any powerups. */
void gameboard::renew_powerup()
{
    if (special == 1)
    {
        powerup->setPixmap(*item);
        powerup->setScaledContents(true);
    }
    else powerup->clear();

}
