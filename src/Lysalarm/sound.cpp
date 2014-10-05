/*! \file sound.cpp
 *
 *  \brief Controls the sound card. 
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */
 

#include "sound.h"

#define PLAY_PIN 10
#define RESET_PIN 11 
 
 enum state_t {
S_ON,
S_OFF};

static enum state_t State = S_OFF;
 
static void changeState(enum state_t newState){
  //Serial.println("State --> %d", (int)newState);
  State = newState;
}


void sound_init(void){
 
  /* Set pin to tristate input. To pull pins low set pinMode to output.
  * DO NOT write HIGH to pins. Soundcard does not work on 5V.
  */

  pinMode(PLAY_PIN, INPUT); 
  pinMode(RESET_PIN, INPUT); 
  digitalWrite(PLAY_PIN, LOW);
  digitalWrite(RESET_PIN, LOW);
}
 

 
void sound_play(void){
  /* Tristate RESET_PIN and pull PLAY_PIN low */

  
  switch(State){
    case S_ON:
   
    break;
    
    case S_OFF: 
      pinMode(PLAY_PIN, OUTPUT);  
      delay(100);
      pinMode(PLAY_PIN, INPUT); 
      changeState(S_ON);
    break;
  }
}
 
 
 
void sound_reset(void){
  /* Tristate PLAY_PIN and pull RESET_PIN low */

  switch(State){
    case S_ON:
      pinMode(PLAY_PIN, OUTPUT);  
      delay(100);
      pinMode(PLAY_PIN, INPUT); 
      changeState(S_OFF);   
    break;
    
    case S_OFF: 

    break;
  }
}
