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
  pinMode(PLAY_PIN, OUTPUT); 
  digitalWrite(PLAY_PIN, LOW);
}
 

 
void sound_play(void){
  
  switch(State){
    case S_ON:
   
    break;
    
    case S_OFF: 
    digitalWrite(PLAY_PIN, HIGH);
    changeState(S_ON);
    break;
  }
}
 
 
 
void sound_reset(void){

  switch(State){
    case S_ON:
    digitalWrite(PLAY_PIN, LOW);
    changeState(S_OFF); 
    break;
    
    case S_OFF: 

    break;
  }
}
