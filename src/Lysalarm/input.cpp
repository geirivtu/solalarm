/*! \file input.cpp
 *
 *  \brief Functions for reading button, switch and encoder.  
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */



#include "input.h"

#define BUTTON_PIN 6 //Other button pin to GND
#define ALARM_SWITCH_PIN 7 //Other button pin to GND

#define ROTARY_ENC_A 8
#define ROTARY_ENC_B 9

boolean Alarm_button_status = 0; /* Used by input_get_alarm_button_status()  */

void input_init(){

  pinMode(BUTTON_PIN, INPUT); 
  /* Set PULLUP on BUTTON_PIN */
  digitalWrite(BUTTON_PIN, HIGH);

  pinMode(ALARM_SWITCH_PIN, INPUT); 
  /* Set PULLUP on ALARM_SWITCH_PIN */
  digitalWrite(ALARM_SWITCH_PIN, HIGH);
  Alarm_button_status = digitalRead(ALARM_SWITCH_PIN);
  
  /* Set rotary encoder pins as INPUT with PULLUP */
  pinMode(ROTARY_ENC_A, INPUT); 
  pinMode(ROTARY_ENC_B, INPUT); 
  digitalWrite(ROTARY_ENC_A, HIGH);
  digitalWrite(ROTARY_ENC_B, HIGH);
}

int8_t input_read_encoder(void){
  static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t old_AB = 0;
  static int8_t counter = 0;
  
  old_AB <<= 2;                   //remember previous state
  old_AB |= (digitalRead(ROTARY_ENC_A)<<1) | digitalRead(ROTARY_ENC_B);
  
  counter += enc_states[( old_AB & 0x0f )];
  
  if(counter > 4){
    counter = 0;
    return 1;
  }else if(counter < -4){
    counter = 0;
    return -1;
  }else return 0;
}

/* Returns true when button has been pressed */
boolean input_select_button(){
  boolean return_value = false;
  static char prev_button_status = HIGH;
  char button_status = digitalRead(BUTTON_PIN);

  /* If BUTTON_PIN is pressed AND was previously not pressed */
  if(button_status == 0 && prev_button_status == 1){
    //delay(15);
    return_value = true;
  }
  prev_button_status = button_status;
  return return_value;
}

/* Returns true when alarm button status has changed */
boolean input_alarm_button(){

  boolean return_value = false;
  static char prev_button_status = HIGH;
  char button_status = digitalRead(ALARM_SWITCH_PIN);

  /* If BUTTON_PIN is pressed AND was previously not pressed */
  if(button_status == !prev_button_status){
    //delay(15);
    Alarm_button_status = button_status; /* Used by input_get_alarm_button_status()  */
    return_value = true;
  }

  prev_button_status = button_status;
  return return_value;
}

boolean input_get_alarm_button_status(){
  return Alarm_button_status;
}


