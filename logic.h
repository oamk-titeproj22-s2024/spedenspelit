#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <leds.h>

extern int randcount;
extern int randomNumbers[100];
extern int numero;
extern int tickcount;
extern bool started;

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
  
*/
void initializeTimer();
// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.
/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame();
/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void checkGame();
/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame();

ISR(TIMER4_COMPA_vect);
#endif
