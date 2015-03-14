/** @file LCDNumber.h
    @author Hann Lam Woo
    @date March 13, 2015
    @brief This is a header file for the LCDNumber class. The class is defined within this header file.
    This file contains the list of functions and variable used in LCDNumber.\n
    The LCDNumber class contains the timer for the game. It keeps track of the game time.\n
*/

#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QLabel>
#include <QTimer>
#include <QTime>
#include <iostream>


/** @class LCDNumber
    @brief The LCDNumber class contains the timer for the game. It keeps track of the game time.\n
*/

class LCDNumber: public QLabel
{
  Q_OBJECT

  public:
  QTimer* timer_lcd;
  QTime*  timeValue;
  int sec;
  int set_min;
  int set_sec;

  public:

  /** This function initializes the LCDNumber object.
      @param parentWidget is the QWidget set to this LCDNumber object
      @param minutes is the minutes set in the LCDNumber object
      @param seconds is the seconds set in the LCDNumber object
     */
    LCDNumber(QWidget * parentWidget,int minutes,int seconds)
    {
        set_min = minutes;
        set_sec = seconds;
        timer_lcd = new QTimer();
        timeValue = new QTime(0,minutes,seconds);
        sec = minutes*60 +seconds;
        this->setParent(parentWidget);
        this->setText(timeValue->toString());

        QObject::connect(timer_lcd,SIGNAL(timeout()),this,SLOT(setDisplay()));
    };
    ~ LCDNumber(){};

    /** This returns the seconds left in the timer
        @returns seconds left
        */
    int getSeconds() { return sec;}

    /// Stops the clock
    void stop() { timer_lcd->stop();}

    /// Starts the clock
    void start() { timer_lcd->start();}

    /// Restarts the timer
    void restart()
    {
        timeValue->setHMS(0,set_min,set_sec,0);
        sec = set_min*60 +set_sec;
    }

   public slots:

    /// Sets the display in the gameboard object
    void setDisplay()
    {
      this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
       sec--;
      this->setText(this->timeValue->toString());
    };
};
#endif
